#include <convert_manager.h>
#include "color.h"
#include <stdlib.h>

//构造结构体
static T_VideoConvert g_tYUV2RGBConvert{
	.name = "YUV2RGB",
	.isSupport   = YUV2RGBisSupport,
	.Convert     = YUV2RGBConvert,
	.ConvertExit = YUV2RGBConvertExit,
};

static int YUV2RGBisSupport (int iPixelFormatIn, int iPixelFormatOut){
	if(iPixelFormatIn != V4L2_PIX_FMT_YUYV){
		return 0;
	}
	if((iPixelFormatOut != V4L2_PIX_FMT_RGB565) && (iPixelFormatOut != V4L2_PIX_FMT_RGB32)){
		return 0;
	}
	return 1;
}
static unsigned int
Pyuv422torgb32(unsigned char * input_ptr, unsigned char * output_ptr, unsigned int image_width, unsigned int image_height)
{
	unsigned int i, size;
	unsigned char Y, Y1, U, V;
	unsigned char *buff = input_ptr;
	unsigned int *output_pt = (unsigned int *)output_ptr;
	unsigned int r, g, b;
	unsigned int color;
	
	size = image_width * image_height /2;
	for (i = size; i > 0; i--) {
		/* bgr instead rgb ?? */
		Y = buff[0] ;
		U = buff[1] ;
		Y1 = buff[2];
		V = buff[3];
		buff += 4;
		r = R_FROMYV(Y,V);
		g = G_FROMYUV(Y,U,V); //b
		b = B_FROMYU(Y,U); //v
		color = (r << 16) | (g << 8) | b;
		*output_pt++ = color;
		
			
		r = R_FROMYV(Y1,V);
		g = G_FROMYUV(Y1,U,V); //b
		b = B_FROMYU(Y1,U); //v
		color = (r << 16) | (g << 8) | b;
		*output_pt++ = color;
	}
	
	return 0;
}

static unsigned int
Pyuv422torgb565(unsigned char * input_ptr, unsigned char * output_ptr, unsigned int image_width, unsigned int image_height)
{
	unsigned int i, size;
	unsigned char Y, Y1, U, V;
	unsigned char *buff = input_ptr;
	unsigned char *output_pt = output_ptr;
	
	unsigned int r, g, b;
	unsigned int color;
	
	size = image_width * image_height /2;
	for (i = size; i > 0; i--) {
		/* bgr instead rgb ?? */
		Y = buff[0] ;
		U = buff[1] ;
		Y1 = buff[2];
		V = buff[3];
		buff += 4;
		r = R_FROMYV(Y,V);
		g = G_FROMYUV(Y,U,V); //b
		b = B_FROMYU(Y,U); //v
		//将rgb三色构造为rgb565的16位值
		r = r >> 3;
		g = g >> 2;
		b = b >> 3;
		color = (r << 11) | (g << 5) | b;
		*output_pt++ = color & 0xff     //得到color 变量的最低8位（即一个字节）
		*output_pt++ = (color >> 8) & 0xff  //将 color 变量右移8位，然后提取最低8位
		
			
		r = R_FROMYV(Y1,V);
		g = G_FROMYUV(Y1,U,V); //b
		b = B_FROMYU(Y1,U); //v
		//将rgb三色构造为rgb565的16位值
		r = r >> 3;
		g = g >> 2;
		b = b >> 3;
		color = (r << 11) | (g << 5) | b;
		*output_pt++ = color & 0xff     //得到color 变量的最低8位（即一个字节）
		*output_pt++ = (color >> 8) & 0xff  //将 color 变量右移8位，然后提取最低8位
	}
	
	return 0;
}  

int YUV2RGBConvert (PT_VideoBuf ptVideoBufIn, PT_VideoBuf ptVideoBufOut){
	PT_PixelDatas ptPixelDatasIn = &ptPixelDatasIn->tPixeldatas;
	PT_PixelDatas ptPixelDatasOut = &ptPixelDatasOut->tPixeldatas;
	
	ptPixelDatasOut->iWidth = ptPixelDatasIn->iWidth;
	ptPixelDatasOut->iHeight = ptPixelDatasIn->iHeight;
	
	if(ptVideoBufOut->iPixelFormatOut == V4L2_PIX_FMT_RGB565){
		ptPixelDatasOut->iBpp = 16;
		ptPixelDatasOut->iLineBytes = ptPixelDatasOut->iWidth * ptPixelDatasOut->iBpp / 8;
		ptPixelDatasOut->iTotalBytes = ptPixelDatasOut->iLineBytes * ptPixelDatasOut->iHeight;
		
		//如果存储数据的内存是空的
		if(!ptPixelDatasOut->aucPixelDatas){
			ptPixelDatasOut->aucPixelDatas = malloc(ptPixelDatasOut->iTotalBytes);
		}
		Pyuv422torgb565(ptPixelDatasIn->aucPixelDatas, ptPixelDatasOut->aucPixelDatas, ptPixelDatasOut->iWidth, ptPixelDatasOut->iHeight);
		return 0;
	}else if(ptVideoBufOut->iPixelFormatOut == V4L2_PIX_FMT_RGB32){
		ptPixelDatasOut->iBpp = 32;
		ptPixelDatasOut->iLineBytes = ptPixelDatasOut->iWidth * ptPixelDatasOut->iBpp / 8;
		ptPixelDatasOut->iTotalBytes = ptPixelDatasOut->iLineBytes * ptPixelDatasOut->iHeight;
		
		//如果存储数据的内存是空的
		if(!ptPixelDatasOut->aucPixelDatas){
			ptPixelDatasOut->aucPixelDatas = malloc(ptPixelDatasOut->iTotalBytes);
		}
		Pyuv422torgb32(ptPixelDatasIn->aucPixelDatas, ptPixelDatasOut->aucPixelDatas, ptPixelDatasOut->iWidth, ptPixelDatasOut->iHeight);
		return 0;
	}
	return -1;
}

int YUV2RGBConvertExit (PT_VideoBuf ptVideoBufOut){
	if(ptPixelDatasOut->aucPixelDatas.aucPixelDatas){
		free(ptPixelDatasOut->tPixeldatas.aucPixelDatas);
		ptPixelDatasOut->tPixeldatas.aucPixelDatas = NULL;
	}
	
	return 0；
}

//注册结构体
extern void initLut(void);

int YUV2RGBInit(void){
	
	initLut()
	return RegisterVideoConvert(&g_tYUV2RGBConvert);
}

