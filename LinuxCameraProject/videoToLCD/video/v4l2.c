#include <config.h>
#include <Video_manager.h>

//构造一个VideoOpr结构体
static T_VideoOpr g_tV4L2Video = {
	
	.name = "V4L2"
	.InitDevice  = V4L2InitDevice,
	.ExitDevice  = V4L2ExitDevice,
	.GetFrame    = V4L2GetFrame,
	.PutFrame    = V4L2PutFrame,
	.StartDevice = V4L2StartDevice,
	.StopDevice  = V4L2StopDevice,
};
//函数的实现，参考luvcview
static int V4L2InitDevice (char *strDeviceName, PT_VideoDevice ptVideoDevice){
	return 0;
}
static int V4L2ExitDevice (PT_VideoDevice ptVideoDevice){
	return 0;
}
static int V4L2GetFrame (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf){
	
	return 0;
}
static int V4L2PutFrame (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf){
	return 0;
}
static int V4L2StartDevice (PT_VideoDevice ptVideoDevice){
	return 0;
}
static int V4L2StopDevice (PT_VideoDevice ptVideoDevice){
	return 0;
}

//向video_manager.c的一个链表里程序注册这个结构体(将本程序中的一个结构体放入video_manager.c的一个链表里)

int V4L2Init(void){
	
	return RegisterVideoOpr(g_tV4L2Video);
}




