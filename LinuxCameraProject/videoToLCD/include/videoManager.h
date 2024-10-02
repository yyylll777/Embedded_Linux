#ifndef _VIDEO_MANAGER_H
#define _VIDEO_MANAGER_H

#include <config.h>
#include "pic_operation.h"
#include <linux/videodev2.h>

#define NB_BUFFER 4

struct VideoDevice;
struct VideoOpr;

typedef struct VideoDevice T_VideoDevice, *PT_VideoDevice;
typedef struct VideoOpr T_VideoOpr, *PT_VideoOpr;

struct VideoDevice{
	int iFd;//文件句柄
	int iPixelFormat;
	int iWidth;
	int iHeight;
	int iVideoBufCount;
	unsigned char *pucVideoBuf[NB_BUFFER];
	int iVideoBufMaxLen;
	int iVideoBufCurIndex;
	
	//函数
	PT_VideoOpr ptOPr;
	
};

typedef struct VideoBuf{
	T_PixelDatas tPixelDatas;
	int iPixelFormat;	
}T_VideoBuf, *PT_VideoBuf;

struct VideoOpr{
	char *name; 
	
	int (*InitDevice) (char *strDeviceName, PT_VideoDevice ptVideoDevice);
	int (*ExitDevice) (PT_VideoDevice ptVideoDevice);
	int (*GetFrame) (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf);
	int (*PutFrame) (PT_VideoDevice ptVideoDevice, PT_VideoBuf ptVideoBuf);
	int (*StartDevice) (PT_VideoDevice ptVideoDevice);
	int (*StopDevice) (PT_VideoDevice ptVideoDevice);
	struct VideoOpr *ptNext;
	
};

int VideoDeviceInit(char *strDevName, PT_VideoDevice ptVideoDevice);
int V4l2Init(void);
int RegisterVideoOpr(PT_VideoOpr ptVideoOpr);
int VideoInit(void);

#endif /* _VIDEO_MANAGER_H* /

