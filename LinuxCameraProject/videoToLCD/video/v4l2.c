#include <config.h>
#include <Video_manager.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fctnl.h>
#include <sys/mman.h>
#include <poll.h>

/*
1. open文件
2. VIDIOC_QUERYCAP 确定它是否是视频捕捉设备，支持哪种接口(streaming/read write)
3. VIDIOC_ENUM_FMT 查询支持哪种格式
4. VIDIOC_S_FMT    设置摄像头使用哪种格式
5. VIDIOC_REQBUFS  申请缓存(buffers)
对于streaming:
1. VIDIOC_QUERYBUF 确定每一个buffer的信息，并进行mmap
2. VIDIOC_QBUF     放入队列
3. VIDIOC_STREAMON 启动设备
4. poll            等待有效数据
5. VIDIOC_DQBUF    从队列中取出
6. 处理
7. VIDIOC_QBUF     放入队列
8. ...
对于read, write:
1. read
2. 处理




*/

static int g_aiSupportedFormats [] = { V4L2_PIX_FMT_YUYV, V4L2_PIX_FMT_MJPEG, V4L2_PIX_FMT_RGB565, V4L2_PIX_FMT_RGB24,
	V4L2_PIX_FMT_RGB32
}

static int isSupportThisFormat(int iPixelFormat){
	int i;
	for(i = 0; i < sizeof(g_aiSupportedFormats)/sizeof(g_aiSupportedFormats[0]); i++){
		if(g_aiSupportedFormats[i] == iPixelFormat){
			return 1;
		}
	}
	return 0;
}

static int V4L2GetFrameForReadWrite (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf){}

static int V4L2PutFrameForReadWrite (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf){}	
	
//构造一个VideoOpr结构体
static T_VideoOpr g_tV4L2VideoOpr = {
	
	.name = "V4L2"
	.InitDevice  = V4L2InitDevice,
	.ExitDevice  = V4L2ExitDevice,
	.GetFrame    = V4L2GetFrameForStreaming,
	.PutFrame    = V4L2PutFrameForStreaming,
	.StartDevice = V4L2StartDevice,
	.StopDevice  = V4L2StopDevice,
};
//函数的实现，参考luvcview
static int V4L2InitDevice (char *strDeviceName, PT_VideoDevice ptVideoDevice){
	int i;
	int iFd;
	int iError;
	struct v4l2_capability tV4L2cap;
	struct v4l2_fmtdesc tFmtDesc;
	struct v4l2_format tV4L2fmt;
	struct v4l2_requestbuffers tV4L2ReqBuffs;
	struct v4l2_buffer tV4L2Buf;
	
	int iLCDWidth;
	int iLCDHeight;
	int iLCDBpp;
	
	
	iFd = open(strDeviceName, O_RDWR);
	if(iFd < 0){
		DBG_PRINTF("can't open %s\n", strDeviceName);//DBG_PRINTF 是一个宏定义
		return -1;
	}
	ptVideoDevice->iFd = iFd;
	
	//VIDIOC_QUERYCAP确定是否为视频捕捉设备，支持哪种接口(streaming/read Write)
	iError = ioctl(iFd, VIDIOC_QUERYCAP, &tV4L2cap);
	memset(&tV4L2cap, 0, sizeof(struct v4l2_capability));
    iError = ioctl(iFd, VIDIOC_QUERYCAP, &tV4L2cap);
    if (iError < 0) {
		DBG_PRINTF("Error opening device %s: unable to query device.\n", strDeviceName);
		goto err_exit;
    }
	
	//判断是不是摄像头
	if( ! (tV4L2cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)){
		DBG_PRINTF("not a video capture device\n", strDeviceName);
		goto err_exit;
	}
	
	if (tV4L2cap.capabilities & V4L2_CAP_STREAMING)){
	    DBG_PRINTF("%s support streaming i/o\n", strDeviceName);
	}
	if (tV4L2cap.capabilities & V4L2_CAP_READWRITE)) {
	    DBG_PRINTF("%s support read i/o\n", strDeviceName);
	}
	
	memset(&tFmtDesc, 0, sizeof(tFmtDesc));
	tFmtDesc.index = 0;
	tFmtDesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	while ((iError = ioctl(iFd, VIDIOC_ENUM_FMT, &tFmtDesc)) == 0) {
		if(isSupportThisFormat(tFmtDesc.pixelformat)){
			ptVideoDevice->iPixelFormat = tFmtDesc.pixelformat;
			break;
		}
		tFmtDesc.index++;
		// printf("{ pixelformat = '%c%c%c%c', description = '%s' }\n",
				// tFmtDesc.pixelformat & 0xFF, (tFmtDesc.pixelformat >> 8) & 0xFF,
				// (tFmtDesc.pixelformat >> 16) & 0xFF, (tFmtDesc.pixelformat >> 24) & 0xFF,
				// tFmtDesc.description);
		// iError = enum_frame_sizes(iFd, tFmtDesc.pixelformat);
		// if (iError != 0)
			// printf("  Unable to enumerate frame sizes.\n");
	}
	
	if(!ptVideoDevice->iPixelFormat){
		DBG_PRINTF("%s: unable to support this format.\n", strDeviceName);
		goto err_exit;
	}
	

	 /* set format in */
	 //事先读出LCD屏幕的分辨率
	GetDispResolution(&iLCDWidth, &iLCDHeight, &iLCDBpp); 
	memset(&tV4L2fmt, 0, sizeof(struct v4l2_format));
    tV4L2fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tV4L2fmt.fmt.pix.width = iLCDWidth;
    tV4L2fmt.fmt.pix.height = iLCDHeight;
    tV4L2fmt.fmt.pix.pixelformat = ptVideoDevice->iPixelFormat;
    tV4L2fmt.fmt.pix.field = V4L2_FIELD_ANY;
    iError = ioctl(iFd, VIDIOC_S_FMT, &tV4L2fmt);
    if (iError) {
		DBG_PRINTF("unable to set format\n");
		goto err_exit;
    }
	
	ptVideoDevice->iWidth = tV4L2fmt.fmt.pix.width;
	ptVideoDevice->iHeight = tV4L2fmt.fmt.pix.height;
	
	//申请缓存
	memset(&tV4L2ReqBuffs, 0, sizeof(struct v4l2_requestbuffers));
    tV4L2ReqBuffs.count = NB_BUFFER;
    tV4L2ReqBuffs.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tV4L2ReqBuffs.memory = V4L2_MEMORY_MMAP;
	
	iError = ioctl(iFd, VIDIOC_REQBUFS, &tV4L2ReqBuffs);
    if (iError) {
		DBG_PRINTF("unable to allocate buffers\n");
		goto err_exit;
    }
	ptVideoDevice->iVideoBufCount = tV4L2ReqBuffs.count; //实际申请到的缓冲区的个数
	
	if(tV4L2cap.capabilities & V4L2_CAP_STREAMING){
		
		for (i = 0; i < ptVideoDevice->iVideoBufCount; i++) {
			memset(&tV4L2Buf, 0, sizeof(struct v4l2_buffer));
			tV4L2Buf.index = i;
			tV4L2Buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			tV4L2Buf.memory = V4L2_MEMORY_MMAP;
			iError = ioctl(iFd, VIDIOC_QUERYBUF, &tV4L2Buf);
			if (iError) {
				DBG_PRINTF("unable to querry buffers\n");
				goto err_exit;
			}
			ptVideoDevice->iVideoBufMaxLen = tV4L2Buf.length;
			ptVideoDevice->pucVideoBuf[i] = mmap(0 /* start anywhere */ ,
				tV4L2Buf.length, PROT_READ, MAP_SHARED, iFd,
				tV4L2Buf.m.offset);
			if (ptVideoDevice->pucVideoBuf[i] == MAP_FAILED) {
				DBG_PRINTF("unable to mmap\n");
				goto err_exit;
			}
		}
		
		/* Queue the buffers. */
		for (i = 0; i < ptVideoDevice->iVideoBufCount; ++i) {
			memset(&tV4L2Buf, 0, sizeof(struct v4l2_buffer));
			tV4L2Buf.index = i;
			tV4L2Buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			tV4L2Buf.memory = V4L2_MEMORY_MMAP;
			iError = ioctl(iFd, VIDIOC_QBUF, &tV4L2Buf);
				if (iError) {
					DBG_PRINTF("unable to queue\n");
					goto err_exit;
				}
		}	
	}else if(tV4L2cap.capabilities & V4L2_CAP_READWRITE){
		g_tV4L2VideoOpr.GetFrame = V4L2GetFrameForReadWrite;
		g_tV4L2VideoOpr.PutFrame = V4L2PutFrameForReadWrite;
		
		ptVideoDevice->iVideoBufCount = 1;
		ptVideoDevice->iVideoBufMaxLen = ptVideoDevice->iWidth * ptVideoDevice->iHeight * 4;
		ptVideoDevice->pucVideoBuf[0] = malloc(ptVideoDevice->iVideoBufMaxLen);
		
	}
	
	return 0;
	
	err_exit:
	close(iFd);
	return -1;
}
static int V4L2ExitDevice (PT_VideoDevice ptVideoDevice){
	int i;
	for (i = 0; i < ptVideoDevice->iVideoBufCount; ++i) {
		if(ptVideoDevice->pucVideoBuf[i]){
			munmap(ptVideoDevice->pucVideoBuf[i], ptVideoDevice->iVideoBufMaxLen);
			ptVideoDevice->pucVideoBuf[i] = NULL;
		}
	}
	close(ptVideoDevice->iFd);
	
	return 0;
}

//需要分为两种情况：streaming接口/read，write接口
static int V4L2GetFrameForStreaming (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf){
	struct pollfd tFds[1];
	struct v4l2_buffer tV4L2Buf;
	int iRet;
	
	//poll
	tFds[0].fd = ptVideoDevice->iFd;
	tFds[0].events = POLLIN;
	
	iRet = poll(tFds, 1, -1);
	if(iRet <= 0){
		DBG_PRINTF("poll error\n")
		return -1;
	}
	
	memset(&tV4L2Buf, 0, sizeof(struct v4l2_buffer));
    tV4L2Buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tV4L2Buf.memory = V4L2_MEMORY_MMAP;
    iRet = ioctl(ptVideoDevice->iFd, VIDIOC_DQBUF, &tV4L2Buf);
    if (iRet < 0) {
		DBG_PRINTF("Unable to dequeue buffer\n");
		return -1;
    }
	
	ptVideoDevice->iVideoBufCurIndex = tV4L2Buf.index;
	ptVideoBuf->iPixelFormat = ptVideoDevice->iPixelFormat;
	ptVideoBuf->tPixelDatas.iWidth  = ptVideoDevice->iWidth;
	ptVideoBuf->tPixelDatas.iHeight = ptVideoDevice->iHeight;
	ptVideoBuf->tPixelDatas.iBpp    = (ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_YUYV) ? 16 :\
                                       (ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_MJPEG) ? : 0 \	
									   (ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_RGB565) : 16;
	ptVideoBuf->tPixelDatas.iLineBytes = ptVideoDevice->iWidth * ptVideoBuf->tPixelDatas.iBpp / 8;
	ptVideoBuf->tPixelDatas.iTotalBytes = tV4L2Buf.bytesused;
	ptVideoBuf->tPixelDatas.aucPixelDatas = ptVideoDevice->pucVideoBuf[tV4L2Buf.index];
	
	return 0;
}

static int V4L2PutFrameForStreaming (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf){
	int iError;
	struct v4l2_buffer tV4L2Buf;
		
	memset(&tV4L2Buf, 0, sizeof(struct v4l2_buffer));
	tV4L2Buf.index = ptVideoDevice->iVideoBufCurIndex;
	tV4L2Buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tV4L2Buf.memory = V4L2_MEMORY_MMAP;
	iError = ioctl(ptVideoDevice->iFd, VIDIOC_QBUF, &tV4L2Buf);
	if (iError) {
	    DBG_PRINTF("Unable to queue buffer\n");
	    return -1;
	}
	
	return 0;
}

static int V4L2GetFrameForReadWrite (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf){
	int iRet;
	iRet = read(ptVideoDevice->iFd, ptVideoDevice->pucVideoBuf[0], ptVideoDevice->iVideoBufMaxLen);
	if(iRet <= 0){
		return -1;
	}
	ptVideoDevice->iVideoBufCurIndex = tV4L2Buf.index;
	ptVideoBuf->iPixelFormat = ptVideoDevice->iPixelFormat;
	ptVideoBuf->tPixelDatas.iWidth  = ptVideoDevice->iWidth;
	ptVideoBuf->tPixelDatas.iHeight = ptVideoDevice->iHeight;
	ptVideoBuf->tPixelDatas.iBpp    = (ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_YUYV) ? 16 :\
                                       (ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_MJPEG) ? : 0 \	
									   (ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_RGB565) : 16;
	ptVideoBuf->tPixelDatas.iLineBytes = ptVideoDevice->iWidth * ptVideoBuf->tPixelDatas.iBpp / 8;
	ptVideoBuf->tPixelDatas.iTotalBytes = iRet;
	ptVideoBuf->tPixelDatas.aucPixelDatas = ptVideoDevice->pucVideoBuf[0];
	
	return 0;
}

static int V4L2PutFrameForReadWrite (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf){
	
	
	return 0;
}
static int V4L2StartDevice (PT_VideoDevice ptVideoDevice){
	int iType = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int iError;

    iError = ioctl(ptVideoDevice->iFd, VIDIOC_STREAMON, &iType);
    if (iError) {
		DBG_PRINTF("Unable to start capture\n");
		return -1;
    }
	return 0;
}
static int V4L2StopDevice (PT_VideoDevice ptVideoDevice){
	int iType = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int iError;

    iError = ioctl(ptVideoDevice->iFd, VIDIOC_STREAMOFF, &iType);
    if (iError) {
	printf("Unable to stop capture);
	return -1;
    }
	return 0;
}

//向video_manager.c的一个链表里程序注册这个结构体(将本程序中的一个结构体放入video_manager.c的一个链表里)

int V4L2Init(void){
	
	return RegisterVideoOpr(g_tV4L2Video);
}




