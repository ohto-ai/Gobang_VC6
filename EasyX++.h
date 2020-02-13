#pragma once

/*****************************************************************************************\
*            基于EasyX图形库的图像处理算法  EasyX++                                       *
*    设计：朱广锋（that boy）                                                             *
*       说明：本文件因鄙人对EasyX的一些改进而产生，因此最需要感谢EasyX制作人员为了EasyX做 *
*    出的巨大努力！                                                                       *
*                  [本文件仅用于学习交流，未经许可，不得转载。]                           *
*       但是 EasyX++ 绝非 更好的EasyX。                                                   *
*       EasyX++ 只是EasyX  低劣的补充 与 模糊的优化                                       *
*       不过，鄙人才疏学浅，算法还有许多漏洞，望贤者查实后通知鄙人。                      *
*                                                                                         *
*    ☆☆☆☆EasyX官网 http://www.easyx.cn ☆☆☆☆                                       *
*                                                                                         *
*    鄙人联系方式：                                                                       *
*           QQ       {512906409}                                                          *
*           Wechat   {zhuguangfeng_at_home}                                               *
*           E-mail   {zhu.guang.feng@foxmail.com}                                         *
*                                                                                         *
*    文件编译环境：                                                                       *
*           操作系统    { Microsoft Windows XP [版本 5.1.2600] }                          *
*           编译环境    { VC++6.0 }                                                       *
*           图形库      { EasyX 20170421(beta) }                                          *
*                                                                                         *
*    文件包含GRAPHICS头文件（EasyX）                                                      *
*                                                                                         *
*  ☆★☆★☆ 所有函数 均 <不考虑> {缩放因子} {裁剪区} {逻辑坐标} 等 的影响 ☆★☆★☆    *
*                                                                                         *
\*****************************************************************************************/

#include <math.h>
#include <graphics.h>

#pragma warning(disable : 4244) //禁用类型转换警告
#pragma warning(disable : 4101) //禁用变量未使用警告

/*****************************************************************************************\
*                                                                                         *
*                                   宏定义部分                                            *
*                                                                                         *
\*****************************************************************************************/

/*//////////投影变换\\\\\\\\\\\\*/
#define D_UP	0		//向上投影
#define D_DOWN	1		//向下投影
#define D_LEFT	2		//向左投影
#define D_RIGHT 3		//向右投影

/*//////////通道提取\\\\\\\\\\\\*/
#define R_CHANNEL 0X08  //R通道
#define G_CHANNEL 0X04  //G通道
#define B_CHANNEL 0X02  //B通道
#define A_CHANNEL 0X01  //A通道

/*//////////位操作\\\\\\\\\\\\*/
#define Bit_ASS		0	//赋值
#define Bit_AND		1	//按位与
#define Bit_XOR		2	//按位异或
#define Bit_OR		3	//按位或
#define Bit_NOT		4	//按位取反
#define Bit_MUL		5	//乘法
#define Bit_DIV		6	//除法
#define Bit_ADD		7	//加法
#define Bit_SUB		8	//减法
#define Bit_MOD		9	//取模
#define Bit_LSFT	10	//左移
#define Bit_RSFT	11	//右移
#define Bit_SADD	12	//安全的 加法
#define Bit_SSUB	13	//安全的 减法
#define Bit_TLTA	14	//半透明加法

#define LITTLE_ENDIAN		//小端存放


#ifdef LITTLE_ENDIAN 	//小端存放

typedef union tag_COLOR{//RGBA分量颜色（与RGB兼容）
    DWORD Color :0X18;
    struct{
        BYTE B;	//蓝色通道
        BYTE G;	//绿色通道
        BYTE R;	//红色通道
        BYTE A;	//透明通道
    };
}COLOR;//ARGB分量颜色（与RGB兼容）
#else
typedef union tag_COLOR{//RGBA分量颜色（与RGB兼容）
    DWORD Color :0X18;
    struct{
        BYTE A;	//透明通道
        BYTE R;	//红色通道
        BYTE G;	//绿色通道
        BYTE B;	//蓝色通道
    };
}COLOR;//RGBA分量颜色（与RGB兼容）
#endif


const COLOR C_WHITE={0XFFFFFF};		//白色
const COLOR C_BLACK={0X000000};		//黑色
const COLOR C_RED  ={0XFF0000};		//红色
const COLOR C_GREEN={0X00FF00};		//绿色
const COLOR C_BLUE ={0X0000FF};		//蓝色

typedef unsigned short Size;//长度
typedef unsigned long  Long;//通常作为遍历指针

/*****************************************************************************************\
*                                                                                         *
*                                 全局变量部分                                            *
*                                                                                         *
\*****************************************************************************************/



const COLOR Poster_AND={0XE0E0E0};	//海报化效果
COLOR*PunchMap;						//交叉冲印 滤镜
IMAGE PunchImg(16,16);				//交叉冲印 图片

/*****************************************************************************************\
*                                                                                         *
*                                 函数定义部分                                            *
*                                                                                         *
\*****************************************************************************************/

IMAGE*CaptureDesktop(IMAGE*img)
{
	WORD Width = GetSystemMetrics(SM_CXSCREEN);// 通过 Windows API 获取桌面的宽
	WORD Height= GetSystemMetrics(SM_CYSCREEN);// 通过 Windows API 获取桌面的高
	Resize(img,Width,Height);// 调整 img 的大小
	HDC dstDC = GetImageHDC(img);// 获取 IMAGE 对象的 DC
	HDC srcDC = GetDC(NULL);// 获取桌面 DC
	BitBlt(dstDC,0,0,Width,Height,srcDC,0,0, SRCCOPY);// DC拷贝
	return img;
}
IMAGE*CaptureWnd(IMAGE*Img,HWND hwnd){//为进程拍照
	if(!hwnd)
		hwnd=GetDesktopWindow();
	RECT rect;
	::GetWindowRect(hwnd,&rect);
	WORD Width =rect.right-rect.left;	//获得宽度
	WORD Height=rect.bottom-rect.top;	//获得高度
	Resize(Img,Width,Height);			// 调整 img 的大小
	HDC dstDC = GetImageHDC(Img);		// 获取 IMAGE 对象的 DC
	HDC srcDC = GetDC(hwnd);			// 获取进程 DC
	BitBlt(dstDC,0,0,Width,Height,srcDC,0,0, SRCCOPY);// DC拷贝
	return Img;
}
IMAGE*IMAGE_Negative(IMAGE*img=NULL){//底片效果
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Long p=0,P;
	if(img)//向图像写入
		P=img->getwidth()*img->getheight();	//获取长度
	else//向屏幕写入
		P=getwidth()*getheight();			//获取长度
	while(p<P)
		pBuf[p++].Color=~pBuf[p].Color;
	return img;
}
IMAGE*IMAGE_Exposure(IMAGE*img=NULL){//曝光
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Long p=0,P;
	if(img)//向图像写入
		P=img->getwidth()*img->getheight();	//获取长度
	else//向屏幕写入
		P=getwidth()*getheight();			//获取长度
	while(p<P){
		if(pBuf[p].R>0X80)
			pBuf[p].R=~pBuf[p].R;
		if(pBuf[p].G>0X80)
			pBuf[p].G=~pBuf[p].G;
		if(pBuf[p].B>0X80)
			pBuf[p].B=~pBuf[p].B;
		p++;
	}
	return img;
}
IMAGE*IMAGE_Gray(IMAGE*img=NULL){//灰度
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Long p=0,P;
	if(img)//向图像写入
		P=img->getwidth()*img->getheight();	//获取长度
	else//向屏幕写入
		P=getwidth()*getheight();			//获取长度
	while(p<P)
		pBuf[p++].R=pBuf[p].G=pBuf[p].B=(pBuf[p].R*313524+pBuf[p].G*615514+pBuf[p].B*119538)>>20;
	return img;
}
IMAGE*IMAGE_Binarize(IMAGE*img=NULL,BYTE Gray=0X80){//二值化
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Long p=0,P;
	if(img)//向图像写入
		P=img->getwidth()*img->getheight();	//获取长度
	else//向屏幕写入
		P=getwidth()*getheight();			//获取长度
	while(p<P)
		pBuf[p++].Color=(pBuf[p].R*313524+pBuf[p].G*615514+pBuf[p].B*119538)>>20<Gray?BLACK:WHITE;
	return img;
}
IMAGE*IMAGE_BinOutline(IMAGE*img=NULL,BYTE Gray=0X80){//二值化轮廓
	BYTE SEED=0X21;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width;
	Long p=0,P;
	if(img){//向图像写入
		Width=img->getwidth();		//获取宽度
		P=img->getheight()*Width;	//获取高度
	}
	else{//向屏幕写入
		Width=getwidth();			//获取宽度
		P=getheight()*Width;		//获取高度
	}
	while(p<P)
		pBuf[p++].Color=(pBuf[p].R*313524+pBuf[p].G*615514+pBuf[p].B*119538)>>20<Gray?BLACK:WHITE;
	for(p=Width+1;p<P-Width-1;p++)
		if(pBuf[p].Color==BLACK)//黑色
			if((pBuf[p-1].Color==BLACK         ||pBuf[p-1].B==SEED)			//左边为黑色
				&&(pBuf[p+1].Color==BLACK	   ||pBuf[p+1].B==SEED)			//右边为黑色
				&&(pBuf[p-Width].Color==BLACK  ||pBuf[p-Width].B==SEED)		//上边为黑色
				&&(pBuf[p+Width].Color==BLACK  ||pBuf[p+Width].B==SEED)		//下边为黑色
				&&(pBuf[p-Width-1].Color==BLACK||pBuf[p-Width-1].B==SEED)	//左上为黑色
				&&(pBuf[p+Width-1].Color==BLACK||pBuf[p+Width-1].B==SEED)	//左下为黑色
				&&(pBuf[p-Width+1].Color==BLACK||pBuf[p-Width+1].B==SEED)	//右上为黑色
				&&(pBuf[p+Width+1].Color==BLACK||pBuf[p+Width+1].B==SEED))	//右下为黑色
				pBuf[p].Color=SEED;
	for(p=Width+1;p<P-Width-1;p++)
		if(pBuf[p].B==SEED)
			pBuf[p].Color=WHITE;
	return img;
}
IMAGE*IMAGE_Diffuse(IMAGE*img=NULL,BYTE Degree=5){//扩散效果
	if(!Degree)
		return img;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	for(i=0;i<Width;i++)
		for(j=0;j<Height;j++)
			pBuf[i+j*Width].Color=pBuf[(i+rand()%Degree+Width-Degree/2)%Width+(j+rand()%Degree+Height-Degree/2)%Height*Width].Color;
	return img;
}
IMAGE*IMAGE_Blur(IMAGE*img=NULL,BYTE Degree=2){//模糊处理
	if(!Degree)
		return img;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	Long R,G,B,T;
	char x,y;
	for(i=0;i<Width;i++)
		for(j=0;j<Height;j++){
			R=G=B=0;
			for(x=-Degree;x<=Degree;x++)
				for(y=-Degree;y<=Degree;y++){
					T=(i+x+Width)%Width+((j+y+Height)%Height)*Width;
					R+=pBuf[T].R;
					G+=pBuf[T].G;
					B+=pBuf[T].B;
				}
			R/=(Degree*2+1)*(Degree*2+1);
			G/=(Degree*2+1)*(Degree*2+1);
			B/=(Degree*2+1)*(Degree*2+1);
			pBuf[i+j*Width].R=R>0XFF?0XFF:R;
			pBuf[i+j*Width].G=G>0XFF?0XFF:G;
			pBuf[i+j*Width].B=B>0XFF?0XFF:B;
		}
	return img;
}
IMAGE*IMAGE_Illuminate(IMAGE*img=NULL,Size x=0X40,Size y=0X40,Size Rad=0X40,Size Tlight=0XFF){//光照特效
	if(Rad==0.0f)
		return img;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	float curR;
	Size light;
	for(i=0;i<Width;i++)
		for(j=0;j<Height;j++){
			curR=sqrt(pow(i-x,2)+pow(j-y,2));  
			if(curR<Rad){
				light=Tlight*(1.0f-curR/Rad);
				pBuf[j*Width+i].R=pBuf[j*Width+i].R+light>0XFF?0XFF:pBuf[j*Width+i].R+light;
				pBuf[j*Width+i].G=pBuf[j*Width+i].G+light>0XFF?0XFF:pBuf[j*Width+i].G+light;
				pBuf[j*Width+i].B=pBuf[j*Width+i].B+light>0XFF?0XFF:pBuf[j*Width+i].B+light;
			}
		}
	return img;
}
IMAGE*IMAGE_GetIlluminateIMG(IMAGE*img=NULL,Size Rad=0X40,Size Tlight=0XFF){//生成光照滤镜图像
	if(!Rad)
		return img;
	Size i,j;
	if(!img)
		return img;
	Size Width=Rad*2,Height=Rad*2;
	Resize(img,Width,Height);
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	float curR;
	Size light;
	for(i=0;i<Width;i++)
		for(j=0;j<Height;j++){
			curR=sqrt(pow(i-Rad,2)+pow(j-Rad,2));  
			if(curR<Rad){
				light=Tlight*(1.0f-curR/Rad);
				pBuf[j*Width+i].R=pBuf[j*Width+i].G=pBuf[j*Width+i].B=light>0XFF?0XFF:light;
			}
			else
				pBuf[j*Width+i].Color=BLACK;
		}
	return img;
}
IMAGE*IMAGE_Light(IMAGE*img=NULL,short light=0X10){//调整亮度
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	if(light>0)//增加光照
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[j*Width+i].R=pBuf[j*Width+i].R+light>0XFF?0XFF:pBuf[j*Width+i].R+light;
				pBuf[j*Width+i].G=pBuf[j*Width+i].G+light>0XFF?0XFF:pBuf[j*Width+i].G+light;
				pBuf[j*Width+i].B=pBuf[j*Width+i].B+light>0XFF?0XFF:pBuf[j*Width+i].B+light;
			}
	else if(light<0)//减少光照
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[j*Width+i].R=pBuf[j*Width+i].R+light<0?0:pBuf[j*Width+i].R+light;
				pBuf[j*Width+i].G=pBuf[j*Width+i].G+light<0?0:pBuf[j*Width+i].G+light;
				pBuf[j*Width+i].B=pBuf[j*Width+i].B+light<0?0:pBuf[j*Width+i].B+light;
			}
	return img;
}
IMAGE*IMAGE_Emboss(IMAGE*img=NULL,BYTE Degree=3){//浮雕效果
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	for(i=0;i<Width;i++)
		for(j=0;j<Height;j++){
			pBuf[i+j*Width].R=(pBuf[i+j*Width].R-pBuf[(i+Degree)%Width+((j+Degree)%Height)*Width].R)+128;
			pBuf[i+j*Width].B=(pBuf[i+j*Width].B-pBuf[(i+Degree)%Width+((j+Degree)%Height)*Width].G)+128;
			pBuf[i+j*Width].G=(pBuf[i+j*Width].G-pBuf[(i+Degree)%Width+((j+Degree)%Height)*Width].B)+128;
			pBuf[i+j*Width].R=pBuf[i+j*Width].G=pBuf[i+j*Width].B=(pBuf[i+j*Width].R*313524 + pBuf[i+j*Width].G*615514 + pBuf[i+j*Width].B*119538) >> 20;
		}
	return img;
}

IMAGE*IMAGE_BinProjecte(IMAGE*img=NULL,BYTE Gray=0X80,BYTE Direct=D_DOWN){//二值图像投影
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j,Num;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	for(i=0;i<Width;i++)//生成二值图像
		for(j=0;j<Height;j++)
			pBuf[i+j*Width].Color=(pBuf[i+j*Width].R*313524+pBuf[i+j*Width].G*615514+pBuf[i+j*Width].B*119538)>>20<Gray?BLACK:WHITE;
	if(Direct==D_UP)//向上	
		for(i=0;i<Width;i++){
			for(j=Num=0;j<Height;j++)
				if(!pBuf[i+j*Width].Color)
					Num++;
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color=(Num>j)?BLACK:WHITE;
		}
	else if(Direct==D_DOWN)//向下	
		for(i=0;i<Width;i++){
			for(j=Num=0;j<Height;j++)
				if(!pBuf[i+j*Width].Color)
					Num++;
			for(j=0;j<Height;j++)
				pBuf[i+(Height-j-1)*Width].Color=(Num>j)?BLACK:WHITE;
		}
	else if(Direct==D_LEFT)//向左
		for(j=0;j<Height;j++){
			for(i=Num=0;i<Width;i++)
				if(!pBuf[i+j*Width].Color)
					Num++;
			for(i=0;i<Width;i++)
				pBuf[i+j*Width].Color=(Num>i)?BLACK:WHITE;
		}
	else if(Direct==D_RIGHT)//向右
		for(j=0;j<Height;j++){
			for(i=Num=0;i<Width;i++)
				if(!pBuf[i+j*Width].Color)
					Num++;
			for(i=0;i<Width;i++)
				pBuf[Width-i-1+j*Width].Color=(Num>i)?BLACK:WHITE;
		}
	return img;
}
IMAGE*IMAGE_ReserveChannel(IMAGE*img=NULL,BYTE Channel=R_CHANNEL){//提取（保留）颜色通道
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	if(!(Channel&R_CHANNEL))//清除 R 通道
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].R=0;
	if(!(Channel&G_CHANNEL))//清除 G 通道
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].G=0;
	if(!(Channel&B_CHANNEL))//清除 B 通道
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].B=0;
	if(!(Channel&A_CHANNEL))//清除 A 通道
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].A=0;
	return img;
}
IMAGE*IMAGE_BitOperate(IMAGE*img=NULL,BYTE OP=Bit_ASS,COLOR Data=C_BLACK){//图像位运算
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}

	if(OP==Bit_ASS)//赋值
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width]=Data;
	else if(OP==Bit_SADD)//防溢出加法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R+Data.R>=0XFF?0XFF:pBuf[i+j*Width].R+Data.R;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G+Data.G>=0XFF?0XFF:pBuf[i+j*Width].G+Data.G;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B+Data.B>=0XFF?0XFF:pBuf[i+j*Width].B+Data.B;
			}
	else if(OP==Bit_SSUB)//防溢出减法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R-Data.R<=0?0:pBuf[i+j*Width].R-Data.R;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G-Data.G<=0?0:pBuf[i+j*Width].G-Data.G;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B-Data.B<=0?0:pBuf[i+j*Width].B-Data.B;
			}
	else if(OP==Bit_AND)//按位与
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color&=Data.Color;
	else if(OP==Bit_XOR)//按位异或
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color^=Data.Color;
	else if(OP==Bit_OR)//按位异或
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color|=Data.Color;
	else if(OP==Bit_NOT)//按位取反
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color=~pBuf[i+j*Width].Color;
	else if(OP==Bit_TLTA)//半透明加法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R/2+Data.R/2;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G/2+Data.G/2;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B/2+Data.B/2;
			}
	else if(OP==Bit_MUL)//乘法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R*=Data.R;
				pBuf[i+j*Width].G*=Data.G;
				pBuf[i+j*Width].B*=Data.B;
			}
	else if(OP==Bit_DIV){//除法
		if(Data.R)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].R/=Data.R;
		if(Data.G)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].G/=Data.G;
		if(Data.B)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].B/=Data.B;
	}			
	else if(OP==Bit_ADD)//加法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R+=Data.R;
				pBuf[i+j*Width].G+=Data.G;
				pBuf[i+j*Width].B+=Data.B;
			}
	else if(OP==Bit_SUB)//减法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R-=Data.R;
				pBuf[i+j*Width].G-=Data.G;
				pBuf[i+j*Width].B-=Data.B;
			}
	else if(OP==Bit_MOD){//取模
		if(Data.R)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].R%=Data.R;
		if(Data.R)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].G%=Data.G;
		if(Data.G)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].B%=Data.B;
	}			
	else if(OP==Bit_LSFT)//左移
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color<<=Data.Color;
	else if(OP==Bit_RSFT)//右移
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color>>=Data.Color;
	return img;
}
IMAGE*IMAGE_BitOperate(IMAGE*img=NULL,BYTE OP=Bit_ASS,DWORD DATA=BLACK){//图像位运算
	COLOR Data={DATA&0X00FFFFFF};
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}

	if(OP==Bit_ASS)//赋值
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width]=Data;
	else if(OP==Bit_SADD)//防溢出加法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R+Data.R>=0XFF?0XFF:pBuf[i+j*Width].R+Data.R;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G+Data.G>=0XFF?0XFF:pBuf[i+j*Width].G+Data.G;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B+Data.B>=0XFF?0XFF:pBuf[i+j*Width].B+Data.B;
			}
	else if(OP==Bit_SSUB)//防溢出减法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R-Data.R<=0?0:pBuf[i+j*Width].R-Data.R;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G-Data.G<=0?0:pBuf[i+j*Width].G-Data.G;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B-Data.B<=0?0:pBuf[i+j*Width].B-Data.B;
			}
	else if(OP==Bit_AND)//按位与
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color&=Data.Color;
	else if(OP==Bit_XOR)//按位异或
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color^=Data.Color;
	else if(OP==Bit_OR)//按位或
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color|=Data.Color;
	else if(OP==Bit_NOT)//按位取反
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color=~pBuf[i+j*Width].Color;
	else if(OP==Bit_TLTA)//半透明加法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R/2+Data.R/2;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G/2+Data.G/2;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B/2+Data.B/2;
			}
	else if(OP==Bit_MUL)//乘法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R*=Data.R;
				pBuf[i+j*Width].G*=Data.G;
				pBuf[i+j*Width].B*=Data.B;
			}
	else if(OP==Bit_DIV){//除法
		if(Data.R)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].R/=Data.R;
		if(Data.G)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].G/=Data.G;
		if(Data.B)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].B/=Data.B;
	}			
	else if(OP==Bit_ADD)//加法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R+=Data.R;
				pBuf[i+j*Width].G+=Data.G;
				pBuf[i+j*Width].B+=Data.B;
			}
	else if(OP==Bit_SUB)//减法
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R-=Data.R;
				pBuf[i+j*Width].G-=Data.G;
				pBuf[i+j*Width].B-=Data.B;
			}
	else if(OP==Bit_MOD){//取模
		if(Data.R)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].R%=Data.R;
		if(Data.R)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].G%=Data.G;
		if(Data.G)
			for(i=0;i<Width;i++)
				for(j=0;j<Height;j++)
					pBuf[i+j*Width].B%=Data.B;
	}	
	else if(OP==Bit_LSFT)//左移
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color<<=Data.Color;
	else if(OP==Bit_RSFT)//右移
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color>>=Data.Color;
	return img;
}
IMAGE*IMAGE_LightMap(IMAGE*img){//亮度图像
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	for(i=0;i<Width;i++)
		for(j=0;j<Height;j++)
			pBuf[i+j*Width].R=
			pBuf[i+j*Width].G=
			pBuf[i+j*Width].B=
				pBuf[i+j*Width].R>pBuf[i+j*Width].G?(pBuf[i+j*Width].R>pBuf[i+j*Width].B?pBuf[i+j*Width].R:pBuf[i+j*Width].B):
													(pBuf[i+j*Width].G>pBuf[i+j*Width].B?pBuf[i+j*Width].G:pBuf[i+j*Width].B)+
				pBuf[i+j*Width].R<pBuf[i+j*Width].G?(pBuf[i+j*Width].R<pBuf[i+j*Width].B?pBuf[i+j*Width].R:pBuf[i+j*Width].B):
													(pBuf[i+j*Width].G<pBuf[i+j*Width].B?pBuf[i+j*Width].G:pBuf[i+j*Width].B);
	return img;
}
IMAGE*IMAGE_ImgOperate(IMAGE*SourceImg,IMAGE*ToolImg,BYTE OP,short x,short y){//图像操作
	COLOR*pS=(COLOR*)GetImageBuffer(SourceImg);	//获取内存指针
	COLOR*pT=(COLOR*)GetImageBuffer( ToolImg);	//获取内存指针
	Size SWidth,SHeight,TWidth,THeight,i,j;
	if(SourceImg){//向图像写入
		SWidth =SourceImg->getwidth ();			//获取宽度
		SHeight=SourceImg->getheight();			//获取高度
	}
	else{//向屏幕写入
		SWidth =getwidth ();			//获取宽度
		SHeight=getheight();			//获取高度
	}
	TWidth =ToolImg->getwidth();		//获取宽度
	THeight=ToolImg->getheight();		//获取高度
	if(OP==Bit_ASS)//赋值操作
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_SADD)//防溢出加法
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R=pS[i+j*SWidth].R+pT[i-x+(j-y)*TWidth].R>=0XFF?0XFF:pS[i+j*SWidth].R+pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G=pS[i+j*SWidth].G+pT[i-x+(j-y)*TWidth].G>=0XFF?0XFF:pS[i+j*SWidth].G+pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B=pS[i+j*SWidth].B+pT[i-x+(j-y)*TWidth].B>=0XFF?0XFF:pS[i+j*SWidth].B+pT[i-x+(j-y)*TWidth].B;
			}
	
	else if(OP==Bit_SSUB)//防溢出减法
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R=pS[i+j*SWidth].R-pT[i-x+(j-y)*TWidth].R<=0?0:pS[i+j*SWidth].R-pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G=pS[i+j*SWidth].G-pT[i-x+(j-y)*TWidth].G<=0?0:pS[i+j*SWidth].G-pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B=pS[i+j*SWidth].B-pT[i-x+(j-y)*TWidth].B<=0?0:pS[i+j*SWidth].B-pT[i-x+(j-y)*TWidth].B;
			}
	else if(OP==Bit_TLTA)//半透明加法
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R=pS[i+j*SWidth].R/2+pT[i-x+(j-y)*TWidth].R/2;
				pS[i+j*SWidth].G=pS[i+j*SWidth].G/2+pT[i-x+(j-y)*TWidth].G/2;
				pS[i+j*SWidth].B=pS[i+j*SWidth].B/2+pT[i-x+(j-y)*TWidth].B/2;
			}
	else if(OP==Bit_AND)//按位与
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color&=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_XOR)//按位异或
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color^=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_OR)//按位或
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color|=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_NOT)//按位取反
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color=~pS[i+j*SWidth].Color;
	else if(OP==Bit_MUL)//乘法
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R*=pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G*=pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B*=pT[i-x+(j-y)*TWidth].B;
			}
	else if(OP==Bit_DIV){//除法
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				if(pT[i-x+(j-y)*TWidth].R)
					pS[i+j*SWidth].R/=pT[i-x+(j-y)*TWidth].R;
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				if(pT[i-x+(j-y)*TWidth].G)
					pS[i+j*SWidth].G/=pT[i-x+(j-y)*TWidth].G;
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				if(pT[i-x+(j-y)*TWidth].B)
					pS[i+j*SWidth].B/=pT[i-x+(j-y)*TWidth].B;
	}			
	else if(OP==Bit_ADD)//加法
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R+=pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G+=pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B+=pT[i-x+(j-y)*TWidth].B;
			}
	else if(OP==Bit_SUB)//减法
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R-=pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G-=pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B-=pT[i-x+(j-y)*TWidth].B;
			}
	else if(OP==Bit_MOD){//取模
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				if(pT[i-x+(j-y)*TWidth].R)
					pS[i+j*SWidth].R%=pT[i-x+(j-y)*TWidth].R;
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				if(pT[i-x+(j-y)*TWidth].R)
					pS[i+j*SWidth].G%=pT[i-x+(j-y)*TWidth].G;
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				if(pT[i-x+(j-y)*TWidth].G)
					pS[i+j*SWidth].B%=pT[i-x+(j-y)*TWidth].B;
	}		
	else if(OP==Bit_LSFT)//左移
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color<<=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_RSFT)//右移
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color>>=pT[i-x+(j-y)*TWidth].Color;
	return SourceImg;
}
IMAGE*IMAGE_Mosaic(IMAGE*img=NULL,Size Degree=2){//马赛克（Degree为区域块边缘）
	if(Degree==0||Degree==1)//无需运算
		return img;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//获取内存指针
	Size Width,Height,i,j,x,y,height,width;
	unsigned long MosaicValueR,MosaicValueG,MosaicValueB;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	for(i=0;i<Width/Degree;i++){
		for(j=0;j<Height/Degree;j++){
			MosaicValueR=MosaicValueG=MosaicValueB=0;
			for(x=i*Degree;x<(i+1)*Degree;x++)//统计当前区块颜色
				for(y=j*Degree;y<(j+1)*Degree;y++){
					MosaicValueR+=pBuf[x+y*Width].R;
					MosaicValueG+=pBuf[x+y*Width].G;
					MosaicValueB+=pBuf[x+y*Width].B;
				}
			MosaicValueR/=Degree*Degree;
			MosaicValueG/=Degree*Degree;
			MosaicValueB/=Degree*Degree;
			for(x=i*Degree;x<(i+1)*Degree;x++)//为当前区块着色
				for(y=j*Degree;y<(j+1)*Degree;y++){
					pBuf[x+y*Width].R=MosaicValueR;
					pBuf[x+y*Width].G=MosaicValueG;
					pBuf[x+y*Width].B=MosaicValueB;
				}
		}
	}
	if(height=Height%Degree)//纵向未完成
		for(i=0;i<Width/Degree;i++){
			MosaicValueR=MosaicValueG=MosaicValueB=0;
			for(x=i*Degree;x<(i+1)*Degree;x++)//统计当前区块颜色
				for(y=Height-height;y<Height;y++){
					MosaicValueR+=pBuf[x+y*Width].R;
					MosaicValueG+=pBuf[x+y*Width].G;
					MosaicValueB+=pBuf[x+y*Width].B;
				}
			MosaicValueR/=Degree*height;
			MosaicValueG/=Degree*height;
			MosaicValueB/=Degree*height;
			for(x=i*Degree;x<(i+1)*Degree;x++)//为当前区块着色
				for(y=Height-height;y<Height;y++){
					pBuf[x+y*Width].R=MosaicValueR;
					pBuf[x+y*Width].G=MosaicValueG;
					pBuf[x+y*Width].B=MosaicValueB;
				}
		}
	if(width=Width%Degree)//横向未完成
		for(j=0;j<Height/Degree;j++){
			MosaicValueR=MosaicValueG=MosaicValueB=0;
			for(x=Width-width;x<Width;x++)//统计当前区块颜色
				for(y=j*Degree;y<(j+1)*Degree;y++){
					MosaicValueR+=pBuf[x+y*Width].R;
					MosaicValueG+=pBuf[x+y*Width].G;
					MosaicValueB+=pBuf[x+y*Width].B;
				}
			MosaicValueR/=Degree*width;
			MosaicValueG/=Degree*width;
			MosaicValueB/=Degree*width;
			for(x=Width-width;x<Width;x++)//为当前区块着色
				for(y=j*Degree;y<(j+1)*Degree;y++){
					pBuf[x+y*Width].R=MosaicValueR;
					pBuf[x+y*Width].G=MosaicValueG;
					pBuf[x+y*Width].B=MosaicValueB;
				}
		}
	if(height&&width){//横纵均未完成
		for(x=Width-width;x<Width;x++)
			for(y=Height-height;y<Height;y++){
					MosaicValueR+=pBuf[x+y*Width].R;
					MosaicValueG+=pBuf[x+y*Width].G;
					MosaicValueB+=pBuf[x+y*Width].B;
				}
		MosaicValueR/=width*height;
		MosaicValueG/=width*height;
		MosaicValueB/=width*height;
		for(x=Width-width;x<Width;x++)
			for(y=Height-height;y<Height;y++){
				pBuf[x+y*Width].R=MosaicValueR;
				pBuf[x+y*Width].G=MosaicValueG;
				pBuf[x+y*Width].B=MosaicValueB;
			}
	}
	return img;				
}
IMAGE*Punch(IMAGE*img){//交叉冲印滤镜
    Size Height = img->getheight();
    Size Width  = img->getwidth ();
    Size gray,value;
	Size i,j;
	short R,G;
	if(!PunchMap){//滤镜未生成
		PunchMap=(COLOR*)calloc(0X100,sizeof(COLOR));
		for(i=0;i<0X100;i++){
			value=i<0X80?i:0X100-i;		
			gray=(value*value*value)>>14;
			R=i<0X80?gray:0X100-gray;
			if(R<0)R=0;
			if(R>0XFF)R=0XFF;
			PunchMap[i].R=R;
			gray=(value*value)>>7;
			G=i<0X80?gray:0X100-gray;
			if(G<0)G=0;
			if(G>0XFF)G=0XFF;
			PunchMap[i].G=G;
			PunchMap[i].B=i/2+0x25;
		}
    }
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);
    for(i = 0;i<Width;i++)
		for(j = 0;j<Height;j++){
            pBuf[i+j*Width].R=PunchMap[pBuf[i+j*Width].R].R;
			pBuf[i+j*Width].G=PunchMap[pBuf[i+j*Width].G].G;
            pBuf[i+j*Width].B=PunchMap[pBuf[i+j*Width].B].B;
        }
	return img;
}
COLOR*PreloadPunchMap(){//预加载 交叉冲印 滤镜
    Size gray,value;
	Size i;
	short R,G;
	if(!PunchMap){//滤镜未生成
		PunchMap=(COLOR*)calloc(0X100,sizeof(COLOR));
		for(i=0;i<0X100;i++){
			value=i<0X80?i:0X100-i;
			gray=(value*value*value)>>14;
			R=i<0X80?gray:0X100-gray;
			if(R<0)R=0;
			if(R>0XFF)R=0XFF;
			PunchMap[i].R=R;
			gray=(value*value)>>7;
			G=i<0X80?gray:0X100-gray;
			if(G<0)G=0;
			if(G>0XFF)G=0XFF;
			PunchMap[i].G=G;
			PunchMap[i].B=i/2+0x25;
		}
    }
	return PunchMap;
}
IMAGE*PreBuildPunchImg(){//预生成 交叉冲印 图片
    Size gray,value;
	Size i;
	short R,G;
	if(PunchMap){//滤镜存在，复制滤镜内存
		COLOR*pBuf=(COLOR*)GetImageBuffer(&PunchImg);
		for(i=0;i<0X100;i++)
			pBuf[i]=PunchMap[i];
		free(PunchMap);
		PunchMap=pBuf;
	}
	else{//滤镜不存在
		PunchMap=(COLOR*)GetImageBuffer(&PunchImg);
		for(i=0;i<0X100;i++){
			value=i<0X80?i:0X100-i;
			gray=(value*value*value)>>14;
			R=i<0X80?gray:0X100-gray;
			if(R<0)R=0;
			if(R>0XFF)R=0XFF;
			PunchMap[i].R=R;
			gray=(value*value)>>7;
			G=i<0X80?gray:0X100-gray;
			if(G<0)G=0;
			if(G>0XFF)G=0XFF;
			PunchMap[i].G=G;
			PunchMap[i].B=i/2+0x25;
		}
	}
	return &PunchImg;
}
IMAGE*AddFilter(IMAGE*img,IMAGE*Filter){
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	COLOR*pFil=(COLOR*)GetImageBuffer(Filter);//获取滤镜内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
    for(i = 0;i<Width;i++)
		for(j = 0;j<Height;j++){
            pBuf[i+j*Width].R=pFil[pBuf[i+j*Width].R].R;
			pBuf[i+j*Width].G=pFil[pBuf[i+j*Width].G].G;
            pBuf[i+j*Width].B=pFil[pBuf[i+j*Width].B].B;
        }
	return img;
}
IMAGE*AddFilter(IMAGE*img,COLOR*pFil){
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
    for(i = 0;i<Width;i++)
		for(j = 0;j<Height;j++){
            pBuf[i+j*Width].R=pFil[pBuf[i+j*Width].R].R;
			pBuf[i+j*Width].G=pFil[pBuf[i+j*Width].G].G;
            pBuf[i+j*Width].B=pFil[pBuf[i+j*Width].B].B;
        }
	return img;
}
IMAGE*IMAGE_BWComics(IMAGE*img){//黑白漫画
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	short R,G,B,Gray;
	for(i = 0;i<Width;i++)
		for(j = 0;j<Height;j++){
			//计算新的RGB值
			R=abs(2*pBuf[i+j*Width].G-pBuf[i+j*Width].B+pBuf[i+j*Width].R)*pBuf[i+j*Width].R>>8;
			G=abs(2*pBuf[i+j*Width].B-pBuf[i+j*Width].G+pBuf[i+j*Width].R)*pBuf[i+j*Width].R>>8;
			B=abs(2*pBuf[i+j*Width].B-pBuf[i+j*Width].G+pBuf[i+j*Width].R)*pBuf[i+j*Width].R>>8;
			//获得灰度值
			Gray=(R+G+B)/3;
			//设定新的RGB值
            pBuf[i+j*Width].R=pBuf[i+j*Width].G=Gray+10>0XFF?0XFF:Gray+10;
            pBuf[i+j*Width].B=Gray>0XFF?0XFF:Gray;
		}
	return img;
}
IMAGE*IMAGE_Neon(IMAGE*img,BYTE Degree){//霓虹效果
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	short R,G,B;
	for(i = 0;i<Width-1;i++)
		for(j = 0;j<Height-1;j++){
			R=Degree*sqrt((pBuf[i+j*Width].R-pBuf[i+1+j*Width].R)*(pBuf[i+j*Width].R-pBuf[i+1+j*Width].R)
						 +(pBuf[i+j*Width].R-pBuf[i+(j+1)*Width].R)*(pBuf[i+j*Width].R-pBuf[i+1+(j+1)*Width].R));
			G=Degree*sqrt((pBuf[i+j*Width].G-pBuf[i+1+j*Width].G)*(pBuf[i+j*Width].G-pBuf[i+1+j*Width].G)
						 +(pBuf[i+j*Width].G-pBuf[i+(j+1)*Width].G)*(pBuf[i+j*Width].G-pBuf[i+1+(j+1)*Width].G));
			B=Degree*sqrt((pBuf[i+j*Width].B-pBuf[i+1+j*Width].B)*(pBuf[i+j*Width].B-pBuf[i+1+j*Width].B)
						 +(pBuf[i+j*Width].B-pBuf[i+(j+1)*Width].B)*(pBuf[i+j*Width].B-pBuf[i+1+(j+1)*Width].B));
			if(R>0XFF)R=0XFF;
			if(G>0XFF)G=0XFF;
			if(B>0XFF)B=0XFF;
			pBuf[i+j*Width].R=R;
			pBuf[i+j*Width].G=G;
			pBuf[i+j*Width].B=B;

		}
	return img;
}
IMAGE*IMAGE_Nostalgic(IMAGE*img){//怀旧
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	short R,G,B;
	for(i = 0;i<Width-1;i++)
		for(j = 0;j<Height-1;j++){
			R=0.393*pBuf[i+j*Width].R+0.769*pBuf[i+j*Width].G+0.189*pBuf[i+j*Width].B;
			G=0.349*pBuf[i+j*Width].R+0.686*pBuf[i+j*Width].G+0.168*pBuf[i+j*Width].B;
			B=0.272*pBuf[i+j*Width].R+0.534*pBuf[i+j*Width].G+0.131*pBuf[i+j*Width].B;
			if(R>0XFF)R=0XFF;
			if(G>0XFF)G=0XFF;
			if(B>0XFF)B=0XFF;
			pBuf[i+j*Width].R=R;
			pBuf[i+j*Width].G=G;
			pBuf[i+j*Width].B=B;
		}
	return img;
}
IMAGE*IMAGE_Fuse(IMAGE*SourceImg,IMAGE*ToolImg,short x,short y){//图像融合
	COLOR*pS=(COLOR*)GetImageBuffer(SourceImg);	//获取内存指针
	COLOR*pT=(COLOR*)GetImageBuffer( ToolImg);	//获取内存指针
	Size SWidth,SHeight,TWidth,THeight,i,j;
	if(SourceImg){//向图像写入
		SWidth =SourceImg->getwidth ();			//获取宽度
		SHeight=SourceImg->getheight();			//获取高度
	}
	else{//向屏幕写入
		SWidth =getwidth ();			//获取宽度
		SHeight=getheight();			//获取高度
	}
	TWidth =ToolImg->getwidth ();		//获取宽度
	THeight=ToolImg->getheight();		//获取高度
	Size R,G,B;
	for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
		for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
			R=(pS[i+j*SWidth].R*pT[i-x+(j-y)*TWidth].A+pT[i-x+(j-y)*TWidth].R*(0XFF-pT[i-x+(j-y)*TWidth].A))/0XFF;
			G=(pS[i+j*SWidth].G*pT[i-x+(j-y)*TWidth].A+pT[i-x+(j-y)*TWidth].G*(0XFF-pT[i-x+(j-y)*TWidth].A))/0XFF;
			B=(pS[i+j*SWidth].B*pT[i-x+(j-y)*TWidth].A+pT[i-x+(j-y)*TWidth].B*(0XFF-pT[i-x+(j-y)*TWidth].A))/0XFF;
			if(R>0XFF)R=0XFF;
			if(G>0XFF)G=0XFF;
			if(B>0XFF)B=0XFF;
			pS[i+j*SWidth].R=R;
			pS[i+j*SWidth].G=G;
			pS[i+j*SWidth].B=B;
		}
	return SourceImg;
}
IMAGE*IMAGE_SetRecA(IMAGE*img,Size left,Size top,Size right,Size bottom,BYTE A){//设定矩形透明区域
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	if(right>=Width)
		right=Width-1;
	if(bottom>=Height)
		bottom=Height-1;
	for(i=left;i<=right;i++)
		for(j=top;j<=bottom;j++)
			pBuf[i+j*Width].A=A;
	return img;
}
IMAGE*IMAGE_SetRecA(IMAGE*img,BYTE A){//设定矩形透明区域
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	for(i = 0;i<Width;i++)
		for(j = 0;j<Height;j++)
			pBuf[i+j*Width].A=A;
	return img;
}
IMAGE*GaussFilter(IMAGE*img){//高斯滤波
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	Size Width,Height,i,j;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	char x,y;//模板索引坐标
	//高斯核
	char Gauss_Core[5][5]={ 1, 4, 7, 4, 1, 
							4,16,26,16, 4,
							7,26,41,26, 7,
							4,16,26,16, 4,
							1, 4, 7, 4, 1}; 
	DWORD R,G,B,T;
	for(i=2;i<Width-2;i++)
		for(j=2;j<Height-2;j++){
			R=G=B=0;
			for(x=0;x<=4;x++)
				for(y=0;y<=4;y++){
					T=(i+x-2+Width)%Width+((j+y-2+Height)%Height)*Width;
					R+=pBuf[T].R*Gauss_Core[x][y];
					G+=pBuf[T].G*Gauss_Core[x][y];
					B+=pBuf[T].B*Gauss_Core[x][y];
				}
			R/=273;
			G/=273;
			B/=273;
			if(R>0XFF)R=0XFF;
			if(G>0XFF)G=0XFF;
			if(B>0XFF)B=0XFF;
			pBuf[i+j*Width].R=R;
			pBuf[i+j*Width].G=G;
			pBuf[i+j*Width].B=B;
		}
	return img;
}
IMAGE*IMAGE_ColorFilter(IMAGE*SourceImg,IMAGE*ToolImg,short x,short y){//图像操作
	COLOR*pS=(COLOR*)GetImageBuffer(SourceImg);	//获取内存指针
	COLOR*pT=(COLOR*)GetImageBuffer( ToolImg);	//获取内存指针
	Size SWidth,SHeight,TWidth,THeight,i,j;
	if(SourceImg){//向图像写入
		SWidth =SourceImg->getwidth ();			//获取宽度
		SHeight=SourceImg->getheight();			//获取高度
	}
	else{//向屏幕写入
		SWidth =getwidth ();			//获取宽度
		SHeight=getheight();			//获取高度
	}
	TWidth =ToolImg->getwidth();		//获取宽度
	THeight=ToolImg->getheight();		//获取高度
	short R,G,B;
	for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
		for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
			R=(~pS[i+j*SWidth].R)*(~pT[i-x+(j-y)*TWidth].R)/0XFF;
			G=(~pS[i+j*SWidth].G)*(~pT[i-x+(j-y)*TWidth].G)/0XFF;
			B=(~pS[i+j*SWidth].B)*(~pT[i-x+(j-y)*TWidth].B)/0XFF;
			if(R>0XFF)R=0XFF;
			if(G>0XFF)G=0XFF;
			if(B>0XFF)B=0XFF;
			pS[i+j*SWidth].R=R;
			pS[i+j*SWidth].G=G;
			pS[i+j*SWidth].B=B;
		}
	return SourceImg;
}

IMAGE*IMAGE_FloodFill(IMAGE*img,Size x,Size y,COLOR Cfill,Size GrayDiff){//漫水填充
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	Size Width,Height;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	COLOR Cthis=pBuf[x+y*Width];

	POINT*POS=(POINT*)calloc(Width*Height,sizeof(POINT));//坐标队列
	bool* MASK=(bool*)calloc(Width*Height,sizeof(bool));//掩码队列
	Long pbeg=0;//队首指针
	Long pend=0;//队尾指针
	POS[0].x=x;
	POS[0].y=y;
	pend++;
	short gray;
	while(pbeg!=pend){//队列不为空
		x=POS[pbeg].x;//出列
		y=POS[pbeg].y;//出列
		pbeg++;
		pBuf[x+y*Width].Color=Cfill.Color;//填充
		if(x>0)
			if(!MASK[x-1+y*Width]){
				gray=pBuf[x-1+y*Width].R+pBuf[x-1+y*Width].G+pBuf[x-1+y*Width].B
						-Cthis.R-Cthis.G-Cthis.B;
				if(gray>=0&&gray<=GrayDiff){//符合条件
					MASK[x-1+y*Width]=true;
					POS[pend].x=x-1;
					POS[pend].y=y;
					pend++;//入列
				}
				else if(gray<0&&-gray<GrayDiff){//符合条件
					MASK[x-1+y*Width]=true;
					POS[pend].x=x-1;
					POS[pend].y=y;
					pend++;//入列
				}
			}
		if(y>0)
			if(!MASK[x+(y-1)*Width]){
				gray=pBuf[x+(y-1)*Width].R+pBuf[x+(y-1)*Width].G+pBuf[x+(y-1)*Width].B
						-Cthis.R-Cthis.G-Cthis.B;
				if(gray>=0&&gray<=GrayDiff){//符合条件
					MASK[x+(y-1)*Width]=true;
					POS[pend].x=x;
					POS[pend].y=y-1;
					pend++;//入列
				}
				else if(gray<0&&-gray<GrayDiff){//符合条件
					MASK[x+(y-1)*Width]=true;
					POS[pend].x=x;
					POS[pend].y=y-1;
					pend++;//入列
				}
			}
		if(x<Width-1)
			if(!MASK[x+1+y*Width]){
				gray=pBuf[x+1+y*Width].R+pBuf[x+1+y*Width].G+pBuf[x+1+y*Width].B
						-Cthis.R-Cthis.G-Cthis.B;
				if(gray>=0&&gray<=GrayDiff){//符合条件
					MASK[x+1+y*Width]=true;
					POS[pend].x=x+1;
					POS[pend].y=y;
					pend++;//入列
				}
				else if(gray<0&&-gray<GrayDiff){//符合条件
					MASK[x+1+y*Width]=true;
					POS[pend].x=x+1;
					POS[pend].y=y;
					pend++;//入列
				}
			}
		if(y<Height-1)
			if(!MASK[x+(y+1)*Width]){
				gray=pBuf[x+(y+1)*Width].R+pBuf[x+(y+1)*Width].G+pBuf[x+(y+1)*Width].B
						-Cthis.R-Cthis.G-Cthis.B;
				if(gray>=0&&gray<=GrayDiff){//符合条件
					MASK[x+(y+1)*Width]=true;
					POS[pend].x=x;
					POS[pend].y=y+1;
					pend++;//入列
				}
				else if(gray<0&&-gray<GrayDiff){//符合条件
					MASK[x+(y+1)*Width]=true;
					POS[pend].x=x;
					POS[pend].y=y+1;
					pend++;//入列
				}
			}
	}
	free(POS);//释放内存
	free(MASK);//释放内存
	return img;
}

IMAGE*IMAGE_StainedGlass(IMAGE*img,IMAGE*mask,Size GrayDiff,COLOR Frame){//染色玻璃效果（掩码图必须与图像大小相同）
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //获取图像内存指针
	COLOR*pMask=(COLOR*)GetImageBuffer(mask);//获取掩码图像内存指针
	Size Width,Height;
	if(img){//向图像写入
		Width =img->getwidth ();			//获取宽度
		Height=img->getheight();			//获取高度
	}
	else{//向屏幕写入
		Width =getwidth ();			//获取宽度
		Height=getheight();			//获取高度
	}
	Size x,y,i,j;
	COLOR*P=(COLOR*)GetImageBuffer(NULL);
	POINT*POS=(POINT*)calloc(Width*Height,sizeof(POINT));//坐标队列
	bool* MASK=(bool*)calloc(Width*Height,sizeof(bool));//掩码队列
	Long pbeg;//队首指针
	Long pend;//队尾指针
	Long R,G,B;
	Long Ptraversal;//遍历指针
	Size gray;
	for(x=0;x<Width;x++)
		for(y=0;y<Height;y++)//遍历地图
		{	
			if(MASK[x+y*Width])//已绘制
				continue;
			gray=pMask[x+y*Width].R+pMask[x+y*Width].G+pMask[x+y*Width].B;
			if(gray>GrayDiff)//不属于均值区域
				continue;
			//初始化队列
			POS[0].x=x;
			POS[0].y=y;
			pbeg=0;
			pend=1;
			//初始化RGB和
			R=G=B=0;
			//生成当前掩码(由 MASK 图像 映射到 MASK 数组，每次映射 一个完整区块)
			MASK[x+y*Width]=true;//填充标志
			while(pbeg!=pend){//队列不为空
				i=POS[pbeg].x;//出列
				j=POS[pbeg].y;//出列
				//统计RGB
				R+=pBuf[i+j*Width].R;
				G+=pBuf[i+j*Width].G;
				B+=pBuf[i+j*Width].B;
				pbeg++;
				if(i>0)
					if(!MASK[i-1+j*Width]){
						gray=pMask[i-1+j*Width].R+pMask[i-1+j*Width].G+pMask[i-1+j*Width].B;//计算灰度差
						if(gray<=GrayDiff){//符合条件
							MASK[i-1+j*Width]=true;
							POS[pend].x=i-1;
							POS[pend].y=j;
							pend++;//入列
						}
					}
				if(j>0)
					if(!MASK[i+(j-1)*Width]){
						gray=pMask[i+(j-1)*Width].R+pMask[i+(j-1)*Width].G+pMask[i+(j-1)*Width].B;//计算灰度差
						if(gray<=GrayDiff){//符合条件
							MASK[i+(j-1)*Width]=true;
							POS[pend].x=i;
							POS[pend].y=j-1;
							pend++;//入列
						}
					}
				if(i<Width-1)
					if(!MASK[i+1+j*Width]){
						gray=pMask[i+1+j*Width].R+pMask[i+1+j*Width].G+pMask[i+1+j*Width].B;//计算灰度差
						if(gray<=GrayDiff){//符合条件
							MASK[i+1+j*Width]=true;
							POS[pend].x=i+1;
							POS[pend].y=j;
							pend++;//入列
						}
					}
				if(j<Height-1)
					if(!MASK[i+(j+1)*Width]){
						gray=pMask[i+(j+1)*Width].R+pMask[i+(j+1)*Width].G+pMask[i+(j+1)*Width].B;//计算灰度差
						if(gray<=GrayDiff){//符合条件
							MASK[i+(j+1)*Width]=true;
							POS[pend].x=i;
							POS[pend].y=j+1;
							pend++;//入列
						}
					}
			}
			//计算均值
			R/=pend;
			G/=pend;
			B/=pend;
			for(Ptraversal=0;Ptraversal<pbeg;Ptraversal++){//赋值
				pBuf[POS[Ptraversal].x+POS[Ptraversal].y*Width].R=R;
				pBuf[POS[Ptraversal].x+POS[Ptraversal].y*Width].G=G;
				pBuf[POS[Ptraversal].x+POS[Ptraversal].y*Width].B=B;
			}
		}
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				if(!MASK[i+j*Width])
					pBuf[i+j*Width].Color=Frame.Color;
		free(POS);//释放内存
		free(MASK);//释放内存
		return img;
}
/*
IMAGE*PutImage(IMAGE*Obj,IMAGE*Src,Size x,Size y){
	Size Width,Height;//目标图像宽高
	Size width,height;//  源图像宽高
	if(Obj){//非默认绘图设备（屏幕窗口）
		Width =Obj-> getwidth();
		Height=Obj->getheight();
	}
	else{//默认绘图设备
		Width = getwidth();
		Height=getheight();
	}
	if(Src){//非默认绘图设备（屏幕窗口）
		width =Src-> getwidth();
		height=Src->getheight();
	}
	else{//默认绘图设备
		width = getwidth();
		height=getheight();
	}
	DWORD*pObj=GetImageBuffer(Obj);
	DWORD*pSrc=GetImageBuffer(Src);
	Size sx,sy,ex,ey,i,j;//起止坐标和循环变量
	if(x<0)
		sx=0;
	else
		sx=x;
	return Obj;
}
*/