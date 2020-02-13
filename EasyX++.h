#pragma once

/*****************************************************************************************\
*            ����EasyXͼ�ο��ͼ�����㷨  EasyX++                                       *
*    ��ƣ����棨that boy��                                                             *
*       ˵�������ļ�����˶�EasyX��һЩ�Ľ����������������Ҫ��лEasyX������ԱΪ��EasyX�� *
*    ���ľ޴�Ŭ����                                                                       *
*                  [���ļ�������ѧϰ������δ����ɣ�����ת�ء�]                           *
*       ���� EasyX++ ���� ���õ�EasyX��                                                   *
*       EasyX++ ֻ��EasyX  ���ӵĲ��� �� ģ�����Ż�                                       *
*       ���������˲���ѧǳ���㷨�������©���������߲�ʵ��֪ͨ���ˡ�                      *
*                                                                                         *
*    �����EasyX���� http://www.easyx.cn �����                                       *
*                                                                                         *
*    ������ϵ��ʽ��                                                                       *
*           QQ       {512906409}                                                          *
*           Wechat   {zhuguangfeng_at_home}                                               *
*           E-mail   {zhu.guang.feng@foxmail.com}                                         *
*                                                                                         *
*    �ļ����뻷����                                                                       *
*           ����ϵͳ    { Microsoft Windows XP [�汾 5.1.2600] }                          *
*           ���뻷��    { VC++6.0 }                                                       *
*           ͼ�ο�      { EasyX 20170421(beta) }                                          *
*                                                                                         *
*    �ļ�����GRAPHICSͷ�ļ���EasyX��                                                      *
*                                                                                         *
*  ������ ���к��� �� <������> {��������} {�ü���} {�߼�����} �� ��Ӱ�� ������    *
*                                                                                         *
\*****************************************************************************************/

#include <math.h>
#include <graphics.h>

#pragma warning(disable : 4244) //��������ת������
#pragma warning(disable : 4101) //���ñ���δʹ�þ���

/*****************************************************************************************\
*                                                                                         *
*                                   �궨�岿��                                            *
*                                                                                         *
\*****************************************************************************************/

/*//////////ͶӰ�任\\\\\\\\\\\\*/
#define D_UP	0		//����ͶӰ
#define D_DOWN	1		//����ͶӰ
#define D_LEFT	2		//����ͶӰ
#define D_RIGHT 3		//����ͶӰ

/*//////////ͨ����ȡ\\\\\\\\\\\\*/
#define R_CHANNEL 0X08  //Rͨ��
#define G_CHANNEL 0X04  //Gͨ��
#define B_CHANNEL 0X02  //Bͨ��
#define A_CHANNEL 0X01  //Aͨ��

/*//////////λ����\\\\\\\\\\\\*/
#define Bit_ASS		0	//��ֵ
#define Bit_AND		1	//��λ��
#define Bit_XOR		2	//��λ���
#define Bit_OR		3	//��λ��
#define Bit_NOT		4	//��λȡ��
#define Bit_MUL		5	//�˷�
#define Bit_DIV		6	//����
#define Bit_ADD		7	//�ӷ�
#define Bit_SUB		8	//����
#define Bit_MOD		9	//ȡģ
#define Bit_LSFT	10	//����
#define Bit_RSFT	11	//����
#define Bit_SADD	12	//��ȫ�� �ӷ�
#define Bit_SSUB	13	//��ȫ�� ����
#define Bit_TLTA	14	//��͸���ӷ�

#define LITTLE_ENDIAN		//С�˴��


#ifdef LITTLE_ENDIAN 	//С�˴��

typedef union tag_COLOR{//RGBA������ɫ����RGB���ݣ�
    DWORD Color :0X18;
    struct{
        BYTE B;	//��ɫͨ��
        BYTE G;	//��ɫͨ��
        BYTE R;	//��ɫͨ��
        BYTE A;	//͸��ͨ��
    };
}COLOR;//ARGB������ɫ����RGB���ݣ�
#else
typedef union tag_COLOR{//RGBA������ɫ����RGB���ݣ�
    DWORD Color :0X18;
    struct{
        BYTE A;	//͸��ͨ��
        BYTE R;	//��ɫͨ��
        BYTE G;	//��ɫͨ��
        BYTE B;	//��ɫͨ��
    };
}COLOR;//RGBA������ɫ����RGB���ݣ�
#endif


const COLOR C_WHITE={0XFFFFFF};		//��ɫ
const COLOR C_BLACK={0X000000};		//��ɫ
const COLOR C_RED  ={0XFF0000};		//��ɫ
const COLOR C_GREEN={0X00FF00};		//��ɫ
const COLOR C_BLUE ={0X0000FF};		//��ɫ

typedef unsigned short Size;//����
typedef unsigned long  Long;//ͨ����Ϊ����ָ��

/*****************************************************************************************\
*                                                                                         *
*                                 ȫ�ֱ�������                                            *
*                                                                                         *
\*****************************************************************************************/



const COLOR Poster_AND={0XE0E0E0};	//������Ч��
COLOR*PunchMap;						//�����ӡ �˾�
IMAGE PunchImg(16,16);				//�����ӡ ͼƬ

/*****************************************************************************************\
*                                                                                         *
*                                 �������岿��                                            *
*                                                                                         *
\*****************************************************************************************/

IMAGE*CaptureDesktop(IMAGE*img)
{
	WORD Width = GetSystemMetrics(SM_CXSCREEN);// ͨ�� Windows API ��ȡ����Ŀ�
	WORD Height= GetSystemMetrics(SM_CYSCREEN);// ͨ�� Windows API ��ȡ����ĸ�
	Resize(img,Width,Height);// ���� img �Ĵ�С
	HDC dstDC = GetImageHDC(img);// ��ȡ IMAGE ����� DC
	HDC srcDC = GetDC(NULL);// ��ȡ���� DC
	BitBlt(dstDC,0,0,Width,Height,srcDC,0,0, SRCCOPY);// DC����
	return img;
}
IMAGE*CaptureWnd(IMAGE*Img,HWND hwnd){//Ϊ��������
	if(!hwnd)
		hwnd=GetDesktopWindow();
	RECT rect;
	::GetWindowRect(hwnd,&rect);
	WORD Width =rect.right-rect.left;	//��ÿ��
	WORD Height=rect.bottom-rect.top;	//��ø߶�
	Resize(Img,Width,Height);			// ���� img �Ĵ�С
	HDC dstDC = GetImageHDC(Img);		// ��ȡ IMAGE ����� DC
	HDC srcDC = GetDC(hwnd);			// ��ȡ���� DC
	BitBlt(dstDC,0,0,Width,Height,srcDC,0,0, SRCCOPY);// DC����
	return Img;
}
IMAGE*IMAGE_Negative(IMAGE*img=NULL){//��ƬЧ��
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Long p=0,P;
	if(img)//��ͼ��д��
		P=img->getwidth()*img->getheight();	//��ȡ����
	else//����Ļд��
		P=getwidth()*getheight();			//��ȡ����
	while(p<P)
		pBuf[p++].Color=~pBuf[p].Color;
	return img;
}
IMAGE*IMAGE_Exposure(IMAGE*img=NULL){//�ع�
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Long p=0,P;
	if(img)//��ͼ��д��
		P=img->getwidth()*img->getheight();	//��ȡ����
	else//����Ļд��
		P=getwidth()*getheight();			//��ȡ����
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
IMAGE*IMAGE_Gray(IMAGE*img=NULL){//�Ҷ�
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Long p=0,P;
	if(img)//��ͼ��д��
		P=img->getwidth()*img->getheight();	//��ȡ����
	else//����Ļд��
		P=getwidth()*getheight();			//��ȡ����
	while(p<P)
		pBuf[p++].R=pBuf[p].G=pBuf[p].B=(pBuf[p].R*313524+pBuf[p].G*615514+pBuf[p].B*119538)>>20;
	return img;
}
IMAGE*IMAGE_Binarize(IMAGE*img=NULL,BYTE Gray=0X80){//��ֵ��
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Long p=0,P;
	if(img)//��ͼ��д��
		P=img->getwidth()*img->getheight();	//��ȡ����
	else//����Ļд��
		P=getwidth()*getheight();			//��ȡ����
	while(p<P)
		pBuf[p++].Color=(pBuf[p].R*313524+pBuf[p].G*615514+pBuf[p].B*119538)>>20<Gray?BLACK:WHITE;
	return img;
}
IMAGE*IMAGE_BinOutline(IMAGE*img=NULL,BYTE Gray=0X80){//��ֵ������
	BYTE SEED=0X21;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width;
	Long p=0,P;
	if(img){//��ͼ��д��
		Width=img->getwidth();		//��ȡ���
		P=img->getheight()*Width;	//��ȡ�߶�
	}
	else{//����Ļд��
		Width=getwidth();			//��ȡ���
		P=getheight()*Width;		//��ȡ�߶�
	}
	while(p<P)
		pBuf[p++].Color=(pBuf[p].R*313524+pBuf[p].G*615514+pBuf[p].B*119538)>>20<Gray?BLACK:WHITE;
	for(p=Width+1;p<P-Width-1;p++)
		if(pBuf[p].Color==BLACK)//��ɫ
			if((pBuf[p-1].Color==BLACK         ||pBuf[p-1].B==SEED)			//���Ϊ��ɫ
				&&(pBuf[p+1].Color==BLACK	   ||pBuf[p+1].B==SEED)			//�ұ�Ϊ��ɫ
				&&(pBuf[p-Width].Color==BLACK  ||pBuf[p-Width].B==SEED)		//�ϱ�Ϊ��ɫ
				&&(pBuf[p+Width].Color==BLACK  ||pBuf[p+Width].B==SEED)		//�±�Ϊ��ɫ
				&&(pBuf[p-Width-1].Color==BLACK||pBuf[p-Width-1].B==SEED)	//����Ϊ��ɫ
				&&(pBuf[p+Width-1].Color==BLACK||pBuf[p+Width-1].B==SEED)	//����Ϊ��ɫ
				&&(pBuf[p-Width+1].Color==BLACK||pBuf[p-Width+1].B==SEED)	//����Ϊ��ɫ
				&&(pBuf[p+Width+1].Color==BLACK||pBuf[p+Width+1].B==SEED))	//����Ϊ��ɫ
				pBuf[p].Color=SEED;
	for(p=Width+1;p<P-Width-1;p++)
		if(pBuf[p].B==SEED)
			pBuf[p].Color=WHITE;
	return img;
}
IMAGE*IMAGE_Diffuse(IMAGE*img=NULL,BYTE Degree=5){//��ɢЧ��
	if(!Degree)
		return img;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	for(i=0;i<Width;i++)
		for(j=0;j<Height;j++)
			pBuf[i+j*Width].Color=pBuf[(i+rand()%Degree+Width-Degree/2)%Width+(j+rand()%Degree+Height-Degree/2)%Height*Width].Color;
	return img;
}
IMAGE*IMAGE_Blur(IMAGE*img=NULL,BYTE Degree=2){//ģ������
	if(!Degree)
		return img;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
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
IMAGE*IMAGE_Illuminate(IMAGE*img=NULL,Size x=0X40,Size y=0X40,Size Rad=0X40,Size Tlight=0XFF){//������Ч
	if(Rad==0.0f)
		return img;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
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
IMAGE*IMAGE_GetIlluminateIMG(IMAGE*img=NULL,Size Rad=0X40,Size Tlight=0XFF){//���ɹ����˾�ͼ��
	if(!Rad)
		return img;
	Size i,j;
	if(!img)
		return img;
	Size Width=Rad*2,Height=Rad*2;
	Resize(img,Width,Height);
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
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
IMAGE*IMAGE_Light(IMAGE*img=NULL,short light=0X10){//��������
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	if(light>0)//���ӹ���
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[j*Width+i].R=pBuf[j*Width+i].R+light>0XFF?0XFF:pBuf[j*Width+i].R+light;
				pBuf[j*Width+i].G=pBuf[j*Width+i].G+light>0XFF?0XFF:pBuf[j*Width+i].G+light;
				pBuf[j*Width+i].B=pBuf[j*Width+i].B+light>0XFF?0XFF:pBuf[j*Width+i].B+light;
			}
	else if(light<0)//���ٹ���
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[j*Width+i].R=pBuf[j*Width+i].R+light<0?0:pBuf[j*Width+i].R+light;
				pBuf[j*Width+i].G=pBuf[j*Width+i].G+light<0?0:pBuf[j*Width+i].G+light;
				pBuf[j*Width+i].B=pBuf[j*Width+i].B+light<0?0:pBuf[j*Width+i].B+light;
			}
	return img;
}
IMAGE*IMAGE_Emboss(IMAGE*img=NULL,BYTE Degree=3){//����Ч��
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
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

IMAGE*IMAGE_BinProjecte(IMAGE*img=NULL,BYTE Gray=0X80,BYTE Direct=D_DOWN){//��ֵͼ��ͶӰ
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j,Num;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	for(i=0;i<Width;i++)//���ɶ�ֵͼ��
		for(j=0;j<Height;j++)
			pBuf[i+j*Width].Color=(pBuf[i+j*Width].R*313524+pBuf[i+j*Width].G*615514+pBuf[i+j*Width].B*119538)>>20<Gray?BLACK:WHITE;
	if(Direct==D_UP)//����	
		for(i=0;i<Width;i++){
			for(j=Num=0;j<Height;j++)
				if(!pBuf[i+j*Width].Color)
					Num++;
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color=(Num>j)?BLACK:WHITE;
		}
	else if(Direct==D_DOWN)//����	
		for(i=0;i<Width;i++){
			for(j=Num=0;j<Height;j++)
				if(!pBuf[i+j*Width].Color)
					Num++;
			for(j=0;j<Height;j++)
				pBuf[i+(Height-j-1)*Width].Color=(Num>j)?BLACK:WHITE;
		}
	else if(Direct==D_LEFT)//����
		for(j=0;j<Height;j++){
			for(i=Num=0;i<Width;i++)
				if(!pBuf[i+j*Width].Color)
					Num++;
			for(i=0;i<Width;i++)
				pBuf[i+j*Width].Color=(Num>i)?BLACK:WHITE;
		}
	else if(Direct==D_RIGHT)//����
		for(j=0;j<Height;j++){
			for(i=Num=0;i<Width;i++)
				if(!pBuf[i+j*Width].Color)
					Num++;
			for(i=0;i<Width;i++)
				pBuf[Width-i-1+j*Width].Color=(Num>i)?BLACK:WHITE;
		}
	return img;
}
IMAGE*IMAGE_ReserveChannel(IMAGE*img=NULL,BYTE Channel=R_CHANNEL){//��ȡ����������ɫͨ��
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	if(!(Channel&R_CHANNEL))//��� R ͨ��
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].R=0;
	if(!(Channel&G_CHANNEL))//��� G ͨ��
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].G=0;
	if(!(Channel&B_CHANNEL))//��� B ͨ��
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].B=0;
	if(!(Channel&A_CHANNEL))//��� A ͨ��
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].A=0;
	return img;
}
IMAGE*IMAGE_BitOperate(IMAGE*img=NULL,BYTE OP=Bit_ASS,COLOR Data=C_BLACK){//ͼ��λ����
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}

	if(OP==Bit_ASS)//��ֵ
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width]=Data;
	else if(OP==Bit_SADD)//������ӷ�
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R+Data.R>=0XFF?0XFF:pBuf[i+j*Width].R+Data.R;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G+Data.G>=0XFF?0XFF:pBuf[i+j*Width].G+Data.G;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B+Data.B>=0XFF?0XFF:pBuf[i+j*Width].B+Data.B;
			}
	else if(OP==Bit_SSUB)//���������
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R-Data.R<=0?0:pBuf[i+j*Width].R-Data.R;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G-Data.G<=0?0:pBuf[i+j*Width].G-Data.G;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B-Data.B<=0?0:pBuf[i+j*Width].B-Data.B;
			}
	else if(OP==Bit_AND)//��λ��
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color&=Data.Color;
	else if(OP==Bit_XOR)//��λ���
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color^=Data.Color;
	else if(OP==Bit_OR)//��λ���
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color|=Data.Color;
	else if(OP==Bit_NOT)//��λȡ��
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color=~pBuf[i+j*Width].Color;
	else if(OP==Bit_TLTA)//��͸���ӷ�
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R/2+Data.R/2;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G/2+Data.G/2;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B/2+Data.B/2;
			}
	else if(OP==Bit_MUL)//�˷�
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R*=Data.R;
				pBuf[i+j*Width].G*=Data.G;
				pBuf[i+j*Width].B*=Data.B;
			}
	else if(OP==Bit_DIV){//����
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
	else if(OP==Bit_ADD)//�ӷ�
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R+=Data.R;
				pBuf[i+j*Width].G+=Data.G;
				pBuf[i+j*Width].B+=Data.B;
			}
	else if(OP==Bit_SUB)//����
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R-=Data.R;
				pBuf[i+j*Width].G-=Data.G;
				pBuf[i+j*Width].B-=Data.B;
			}
	else if(OP==Bit_MOD){//ȡģ
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
	else if(OP==Bit_LSFT)//����
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color<<=Data.Color;
	else if(OP==Bit_RSFT)//����
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color>>=Data.Color;
	return img;
}
IMAGE*IMAGE_BitOperate(IMAGE*img=NULL,BYTE OP=Bit_ASS,DWORD DATA=BLACK){//ͼ��λ����
	COLOR Data={DATA&0X00FFFFFF};
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}

	if(OP==Bit_ASS)//��ֵ
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width]=Data;
	else if(OP==Bit_SADD)//������ӷ�
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R+Data.R>=0XFF?0XFF:pBuf[i+j*Width].R+Data.R;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G+Data.G>=0XFF?0XFF:pBuf[i+j*Width].G+Data.G;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B+Data.B>=0XFF?0XFF:pBuf[i+j*Width].B+Data.B;
			}
	else if(OP==Bit_SSUB)//���������
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R-Data.R<=0?0:pBuf[i+j*Width].R-Data.R;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G-Data.G<=0?0:pBuf[i+j*Width].G-Data.G;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B-Data.B<=0?0:pBuf[i+j*Width].B-Data.B;
			}
	else if(OP==Bit_AND)//��λ��
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color&=Data.Color;
	else if(OP==Bit_XOR)//��λ���
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color^=Data.Color;
	else if(OP==Bit_OR)//��λ��
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color|=Data.Color;
	else if(OP==Bit_NOT)//��λȡ��
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color=~pBuf[i+j*Width].Color;
	else if(OP==Bit_TLTA)//��͸���ӷ�
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R=pBuf[i+j*Width].R/2+Data.R/2;
				pBuf[i+j*Width].G=pBuf[i+j*Width].G/2+Data.G/2;
				pBuf[i+j*Width].B=pBuf[i+j*Width].B/2+Data.B/2;
			}
	else if(OP==Bit_MUL)//�˷�
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R*=Data.R;
				pBuf[i+j*Width].G*=Data.G;
				pBuf[i+j*Width].B*=Data.B;
			}
	else if(OP==Bit_DIV){//����
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
	else if(OP==Bit_ADD)//�ӷ�
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R+=Data.R;
				pBuf[i+j*Width].G+=Data.G;
				pBuf[i+j*Width].B+=Data.B;
			}
	else if(OP==Bit_SUB)//����
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++){
				pBuf[i+j*Width].R-=Data.R;
				pBuf[i+j*Width].G-=Data.G;
				pBuf[i+j*Width].B-=Data.B;
			}
	else if(OP==Bit_MOD){//ȡģ
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
	else if(OP==Bit_LSFT)//����
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color<<=Data.Color;
	else if(OP==Bit_RSFT)//����
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				pBuf[i+j*Width].Color>>=Data.Color;
	return img;
}
IMAGE*IMAGE_LightMap(IMAGE*img){//����ͼ��
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
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
IMAGE*IMAGE_ImgOperate(IMAGE*SourceImg,IMAGE*ToolImg,BYTE OP,short x,short y){//ͼ�����
	COLOR*pS=(COLOR*)GetImageBuffer(SourceImg);	//��ȡ�ڴ�ָ��
	COLOR*pT=(COLOR*)GetImageBuffer( ToolImg);	//��ȡ�ڴ�ָ��
	Size SWidth,SHeight,TWidth,THeight,i,j;
	if(SourceImg){//��ͼ��д��
		SWidth =SourceImg->getwidth ();			//��ȡ���
		SHeight=SourceImg->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		SWidth =getwidth ();			//��ȡ���
		SHeight=getheight();			//��ȡ�߶�
	}
	TWidth =ToolImg->getwidth();		//��ȡ���
	THeight=ToolImg->getheight();		//��ȡ�߶�
	if(OP==Bit_ASS)//��ֵ����
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_SADD)//������ӷ�
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R=pS[i+j*SWidth].R+pT[i-x+(j-y)*TWidth].R>=0XFF?0XFF:pS[i+j*SWidth].R+pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G=pS[i+j*SWidth].G+pT[i-x+(j-y)*TWidth].G>=0XFF?0XFF:pS[i+j*SWidth].G+pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B=pS[i+j*SWidth].B+pT[i-x+(j-y)*TWidth].B>=0XFF?0XFF:pS[i+j*SWidth].B+pT[i-x+(j-y)*TWidth].B;
			}
	
	else if(OP==Bit_SSUB)//���������
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R=pS[i+j*SWidth].R-pT[i-x+(j-y)*TWidth].R<=0?0:pS[i+j*SWidth].R-pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G=pS[i+j*SWidth].G-pT[i-x+(j-y)*TWidth].G<=0?0:pS[i+j*SWidth].G-pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B=pS[i+j*SWidth].B-pT[i-x+(j-y)*TWidth].B<=0?0:pS[i+j*SWidth].B-pT[i-x+(j-y)*TWidth].B;
			}
	else if(OP==Bit_TLTA)//��͸���ӷ�
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R=pS[i+j*SWidth].R/2+pT[i-x+(j-y)*TWidth].R/2;
				pS[i+j*SWidth].G=pS[i+j*SWidth].G/2+pT[i-x+(j-y)*TWidth].G/2;
				pS[i+j*SWidth].B=pS[i+j*SWidth].B/2+pT[i-x+(j-y)*TWidth].B/2;
			}
	else if(OP==Bit_AND)//��λ��
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color&=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_XOR)//��λ���
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color^=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_OR)//��λ��
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color|=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_NOT)//��λȡ��
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color=~pS[i+j*SWidth].Color;
	else if(OP==Bit_MUL)//�˷�
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R*=pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G*=pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B*=pT[i-x+(j-y)*TWidth].B;
			}
	else if(OP==Bit_DIV){//����
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
	else if(OP==Bit_ADD)//�ӷ�
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R+=pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G+=pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B+=pT[i-x+(j-y)*TWidth].B;
			}
	else if(OP==Bit_SUB)//����
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++){
				pS[i+j*SWidth].R-=pT[i-x+(j-y)*TWidth].R;
				pS[i+j*SWidth].G-=pT[i-x+(j-y)*TWidth].G;
				pS[i+j*SWidth].B-=pT[i-x+(j-y)*TWidth].B;
			}
	else if(OP==Bit_MOD){//ȡģ
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
	else if(OP==Bit_LSFT)//����
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color<<=pT[i-x+(j-y)*TWidth].Color;
	else if(OP==Bit_RSFT)//����
		for(i=x>0?x:0;i<SWidth&&i<TWidth+x;i++)
			for(j=y>0?y:0;j<SHeight&&j<THeight+y;j++)
				pS[i+j*SWidth].Color>>=pT[i-x+(j-y)*TWidth].Color;
	return SourceImg;
}
IMAGE*IMAGE_Mosaic(IMAGE*img=NULL,Size Degree=2){//�����ˣ�DegreeΪ������Ե��
	if(Degree==0||Degree==1)//��������
		return img;
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	//��ȡ�ڴ�ָ��
	Size Width,Height,i,j,x,y,height,width;
	unsigned long MosaicValueR,MosaicValueG,MosaicValueB;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	for(i=0;i<Width/Degree;i++){
		for(j=0;j<Height/Degree;j++){
			MosaicValueR=MosaicValueG=MosaicValueB=0;
			for(x=i*Degree;x<(i+1)*Degree;x++)//ͳ�Ƶ�ǰ������ɫ
				for(y=j*Degree;y<(j+1)*Degree;y++){
					MosaicValueR+=pBuf[x+y*Width].R;
					MosaicValueG+=pBuf[x+y*Width].G;
					MosaicValueB+=pBuf[x+y*Width].B;
				}
			MosaicValueR/=Degree*Degree;
			MosaicValueG/=Degree*Degree;
			MosaicValueB/=Degree*Degree;
			for(x=i*Degree;x<(i+1)*Degree;x++)//Ϊ��ǰ������ɫ
				for(y=j*Degree;y<(j+1)*Degree;y++){
					pBuf[x+y*Width].R=MosaicValueR;
					pBuf[x+y*Width].G=MosaicValueG;
					pBuf[x+y*Width].B=MosaicValueB;
				}
		}
	}
	if(height=Height%Degree)//����δ���
		for(i=0;i<Width/Degree;i++){
			MosaicValueR=MosaicValueG=MosaicValueB=0;
			for(x=i*Degree;x<(i+1)*Degree;x++)//ͳ�Ƶ�ǰ������ɫ
				for(y=Height-height;y<Height;y++){
					MosaicValueR+=pBuf[x+y*Width].R;
					MosaicValueG+=pBuf[x+y*Width].G;
					MosaicValueB+=pBuf[x+y*Width].B;
				}
			MosaicValueR/=Degree*height;
			MosaicValueG/=Degree*height;
			MosaicValueB/=Degree*height;
			for(x=i*Degree;x<(i+1)*Degree;x++)//Ϊ��ǰ������ɫ
				for(y=Height-height;y<Height;y++){
					pBuf[x+y*Width].R=MosaicValueR;
					pBuf[x+y*Width].G=MosaicValueG;
					pBuf[x+y*Width].B=MosaicValueB;
				}
		}
	if(width=Width%Degree)//����δ���
		for(j=0;j<Height/Degree;j++){
			MosaicValueR=MosaicValueG=MosaicValueB=0;
			for(x=Width-width;x<Width;x++)//ͳ�Ƶ�ǰ������ɫ
				for(y=j*Degree;y<(j+1)*Degree;y++){
					MosaicValueR+=pBuf[x+y*Width].R;
					MosaicValueG+=pBuf[x+y*Width].G;
					MosaicValueB+=pBuf[x+y*Width].B;
				}
			MosaicValueR/=Degree*width;
			MosaicValueG/=Degree*width;
			MosaicValueB/=Degree*width;
			for(x=Width-width;x<Width;x++)//Ϊ��ǰ������ɫ
				for(y=j*Degree;y<(j+1)*Degree;y++){
					pBuf[x+y*Width].R=MosaicValueR;
					pBuf[x+y*Width].G=MosaicValueG;
					pBuf[x+y*Width].B=MosaicValueB;
				}
		}
	if(height&&width){//���ݾ�δ���
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
IMAGE*Punch(IMAGE*img){//�����ӡ�˾�
    Size Height = img->getheight();
    Size Width  = img->getwidth ();
    Size gray,value;
	Size i,j;
	short R,G;
	if(!PunchMap){//�˾�δ����
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
COLOR*PreloadPunchMap(){//Ԥ���� �����ӡ �˾�
    Size gray,value;
	Size i;
	short R,G;
	if(!PunchMap){//�˾�δ����
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
IMAGE*PreBuildPunchImg(){//Ԥ���� �����ӡ ͼƬ
    Size gray,value;
	Size i;
	short R,G;
	if(PunchMap){//�˾����ڣ������˾��ڴ�
		COLOR*pBuf=(COLOR*)GetImageBuffer(&PunchImg);
		for(i=0;i<0X100;i++)
			pBuf[i]=PunchMap[i];
		free(PunchMap);
		PunchMap=pBuf;
	}
	else{//�˾�������
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
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	COLOR*pFil=(COLOR*)GetImageBuffer(Filter);//��ȡ�˾��ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
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
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
    for(i = 0;i<Width;i++)
		for(j = 0;j<Height;j++){
            pBuf[i+j*Width].R=pFil[pBuf[i+j*Width].R].R;
			pBuf[i+j*Width].G=pFil[pBuf[i+j*Width].G].G;
            pBuf[i+j*Width].B=pFil[pBuf[i+j*Width].B].B;
        }
	return img;
}
IMAGE*IMAGE_BWComics(IMAGE*img){//�ڰ�����
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	short R,G,B,Gray;
	for(i = 0;i<Width;i++)
		for(j = 0;j<Height;j++){
			//�����µ�RGBֵ
			R=abs(2*pBuf[i+j*Width].G-pBuf[i+j*Width].B+pBuf[i+j*Width].R)*pBuf[i+j*Width].R>>8;
			G=abs(2*pBuf[i+j*Width].B-pBuf[i+j*Width].G+pBuf[i+j*Width].R)*pBuf[i+j*Width].R>>8;
			B=abs(2*pBuf[i+j*Width].B-pBuf[i+j*Width].G+pBuf[i+j*Width].R)*pBuf[i+j*Width].R>>8;
			//��ûҶ�ֵ
			Gray=(R+G+B)/3;
			//�趨�µ�RGBֵ
            pBuf[i+j*Width].R=pBuf[i+j*Width].G=Gray+10>0XFF?0XFF:Gray+10;
            pBuf[i+j*Width].B=Gray>0XFF?0XFF:Gray;
		}
	return img;
}
IMAGE*IMAGE_Neon(IMAGE*img,BYTE Degree){//�޺�Ч��
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
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
IMAGE*IMAGE_Nostalgic(IMAGE*img){//����
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
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
IMAGE*IMAGE_Fuse(IMAGE*SourceImg,IMAGE*ToolImg,short x,short y){//ͼ���ں�
	COLOR*pS=(COLOR*)GetImageBuffer(SourceImg);	//��ȡ�ڴ�ָ��
	COLOR*pT=(COLOR*)GetImageBuffer( ToolImg);	//��ȡ�ڴ�ָ��
	Size SWidth,SHeight,TWidth,THeight,i,j;
	if(SourceImg){//��ͼ��д��
		SWidth =SourceImg->getwidth ();			//��ȡ���
		SHeight=SourceImg->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		SWidth =getwidth ();			//��ȡ���
		SHeight=getheight();			//��ȡ�߶�
	}
	TWidth =ToolImg->getwidth ();		//��ȡ���
	THeight=ToolImg->getheight();		//��ȡ�߶�
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
IMAGE*IMAGE_SetRecA(IMAGE*img,Size left,Size top,Size right,Size bottom,BYTE A){//�趨����͸������
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
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
IMAGE*IMAGE_SetRecA(IMAGE*img,BYTE A){//�趨����͸������
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	for(i = 0;i<Width;i++)
		for(j = 0;j<Height;j++)
			pBuf[i+j*Width].A=A;
	return img;
}
IMAGE*GaussFilter(IMAGE*img){//��˹�˲�
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	Size Width,Height,i,j;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	char x,y;//ģ����������
	//��˹��
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
IMAGE*IMAGE_ColorFilter(IMAGE*SourceImg,IMAGE*ToolImg,short x,short y){//ͼ�����
	COLOR*pS=(COLOR*)GetImageBuffer(SourceImg);	//��ȡ�ڴ�ָ��
	COLOR*pT=(COLOR*)GetImageBuffer( ToolImg);	//��ȡ�ڴ�ָ��
	Size SWidth,SHeight,TWidth,THeight,i,j;
	if(SourceImg){//��ͼ��д��
		SWidth =SourceImg->getwidth ();			//��ȡ���
		SHeight=SourceImg->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		SWidth =getwidth ();			//��ȡ���
		SHeight=getheight();			//��ȡ�߶�
	}
	TWidth =ToolImg->getwidth();		//��ȡ���
	THeight=ToolImg->getheight();		//��ȡ�߶�
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

IMAGE*IMAGE_FloodFill(IMAGE*img,Size x,Size y,COLOR Cfill,Size GrayDiff){//��ˮ���
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	Size Width,Height;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	COLOR Cthis=pBuf[x+y*Width];

	POINT*POS=(POINT*)calloc(Width*Height,sizeof(POINT));//�������
	bool* MASK=(bool*)calloc(Width*Height,sizeof(bool));//�������
	Long pbeg=0;//����ָ��
	Long pend=0;//��βָ��
	POS[0].x=x;
	POS[0].y=y;
	pend++;
	short gray;
	while(pbeg!=pend){//���в�Ϊ��
		x=POS[pbeg].x;//����
		y=POS[pbeg].y;//����
		pbeg++;
		pBuf[x+y*Width].Color=Cfill.Color;//���
		if(x>0)
			if(!MASK[x-1+y*Width]){
				gray=pBuf[x-1+y*Width].R+pBuf[x-1+y*Width].G+pBuf[x-1+y*Width].B
						-Cthis.R-Cthis.G-Cthis.B;
				if(gray>=0&&gray<=GrayDiff){//��������
					MASK[x-1+y*Width]=true;
					POS[pend].x=x-1;
					POS[pend].y=y;
					pend++;//����
				}
				else if(gray<0&&-gray<GrayDiff){//��������
					MASK[x-1+y*Width]=true;
					POS[pend].x=x-1;
					POS[pend].y=y;
					pend++;//����
				}
			}
		if(y>0)
			if(!MASK[x+(y-1)*Width]){
				gray=pBuf[x+(y-1)*Width].R+pBuf[x+(y-1)*Width].G+pBuf[x+(y-1)*Width].B
						-Cthis.R-Cthis.G-Cthis.B;
				if(gray>=0&&gray<=GrayDiff){//��������
					MASK[x+(y-1)*Width]=true;
					POS[pend].x=x;
					POS[pend].y=y-1;
					pend++;//����
				}
				else if(gray<0&&-gray<GrayDiff){//��������
					MASK[x+(y-1)*Width]=true;
					POS[pend].x=x;
					POS[pend].y=y-1;
					pend++;//����
				}
			}
		if(x<Width-1)
			if(!MASK[x+1+y*Width]){
				gray=pBuf[x+1+y*Width].R+pBuf[x+1+y*Width].G+pBuf[x+1+y*Width].B
						-Cthis.R-Cthis.G-Cthis.B;
				if(gray>=0&&gray<=GrayDiff){//��������
					MASK[x+1+y*Width]=true;
					POS[pend].x=x+1;
					POS[pend].y=y;
					pend++;//����
				}
				else if(gray<0&&-gray<GrayDiff){//��������
					MASK[x+1+y*Width]=true;
					POS[pend].x=x+1;
					POS[pend].y=y;
					pend++;//����
				}
			}
		if(y<Height-1)
			if(!MASK[x+(y+1)*Width]){
				gray=pBuf[x+(y+1)*Width].R+pBuf[x+(y+1)*Width].G+pBuf[x+(y+1)*Width].B
						-Cthis.R-Cthis.G-Cthis.B;
				if(gray>=0&&gray<=GrayDiff){//��������
					MASK[x+(y+1)*Width]=true;
					POS[pend].x=x;
					POS[pend].y=y+1;
					pend++;//����
				}
				else if(gray<0&&-gray<GrayDiff){//��������
					MASK[x+(y+1)*Width]=true;
					POS[pend].x=x;
					POS[pend].y=y+1;
					pend++;//����
				}
			}
	}
	free(POS);//�ͷ��ڴ�
	free(MASK);//�ͷ��ڴ�
	return img;
}

IMAGE*IMAGE_StainedGlass(IMAGE*img,IMAGE*mask,Size GrayDiff,COLOR Frame){//Ⱦɫ����Ч��������ͼ������ͼ���С��ͬ��
	COLOR*pBuf=(COLOR*)GetImageBuffer(img);	  //��ȡͼ���ڴ�ָ��
	COLOR*pMask=(COLOR*)GetImageBuffer(mask);//��ȡ����ͼ���ڴ�ָ��
	Size Width,Height;
	if(img){//��ͼ��д��
		Width =img->getwidth ();			//��ȡ���
		Height=img->getheight();			//��ȡ�߶�
	}
	else{//����Ļд��
		Width =getwidth ();			//��ȡ���
		Height=getheight();			//��ȡ�߶�
	}
	Size x,y,i,j;
	COLOR*P=(COLOR*)GetImageBuffer(NULL);
	POINT*POS=(POINT*)calloc(Width*Height,sizeof(POINT));//�������
	bool* MASK=(bool*)calloc(Width*Height,sizeof(bool));//�������
	Long pbeg;//����ָ��
	Long pend;//��βָ��
	Long R,G,B;
	Long Ptraversal;//����ָ��
	Size gray;
	for(x=0;x<Width;x++)
		for(y=0;y<Height;y++)//������ͼ
		{	
			if(MASK[x+y*Width])//�ѻ���
				continue;
			gray=pMask[x+y*Width].R+pMask[x+y*Width].G+pMask[x+y*Width].B;
			if(gray>GrayDiff)//�����ھ�ֵ����
				continue;
			//��ʼ������
			POS[0].x=x;
			POS[0].y=y;
			pbeg=0;
			pend=1;
			//��ʼ��RGB��
			R=G=B=0;
			//���ɵ�ǰ����(�� MASK ͼ�� ӳ�䵽 MASK ���飬ÿ��ӳ�� һ����������)
			MASK[x+y*Width]=true;//����־
			while(pbeg!=pend){//���в�Ϊ��
				i=POS[pbeg].x;//����
				j=POS[pbeg].y;//����
				//ͳ��RGB
				R+=pBuf[i+j*Width].R;
				G+=pBuf[i+j*Width].G;
				B+=pBuf[i+j*Width].B;
				pbeg++;
				if(i>0)
					if(!MASK[i-1+j*Width]){
						gray=pMask[i-1+j*Width].R+pMask[i-1+j*Width].G+pMask[i-1+j*Width].B;//����ҶȲ�
						if(gray<=GrayDiff){//��������
							MASK[i-1+j*Width]=true;
							POS[pend].x=i-1;
							POS[pend].y=j;
							pend++;//����
						}
					}
				if(j>0)
					if(!MASK[i+(j-1)*Width]){
						gray=pMask[i+(j-1)*Width].R+pMask[i+(j-1)*Width].G+pMask[i+(j-1)*Width].B;//����ҶȲ�
						if(gray<=GrayDiff){//��������
							MASK[i+(j-1)*Width]=true;
							POS[pend].x=i;
							POS[pend].y=j-1;
							pend++;//����
						}
					}
				if(i<Width-1)
					if(!MASK[i+1+j*Width]){
						gray=pMask[i+1+j*Width].R+pMask[i+1+j*Width].G+pMask[i+1+j*Width].B;//����ҶȲ�
						if(gray<=GrayDiff){//��������
							MASK[i+1+j*Width]=true;
							POS[pend].x=i+1;
							POS[pend].y=j;
							pend++;//����
						}
					}
				if(j<Height-1)
					if(!MASK[i+(j+1)*Width]){
						gray=pMask[i+(j+1)*Width].R+pMask[i+(j+1)*Width].G+pMask[i+(j+1)*Width].B;//����ҶȲ�
						if(gray<=GrayDiff){//��������
							MASK[i+(j+1)*Width]=true;
							POS[pend].x=i;
							POS[pend].y=j+1;
							pend++;//����
						}
					}
			}
			//�����ֵ
			R/=pend;
			G/=pend;
			B/=pend;
			for(Ptraversal=0;Ptraversal<pbeg;Ptraversal++){//��ֵ
				pBuf[POS[Ptraversal].x+POS[Ptraversal].y*Width].R=R;
				pBuf[POS[Ptraversal].x+POS[Ptraversal].y*Width].G=G;
				pBuf[POS[Ptraversal].x+POS[Ptraversal].y*Width].B=B;
			}
		}
		for(i=0;i<Width;i++)
			for(j=0;j<Height;j++)
				if(!MASK[i+j*Width])
					pBuf[i+j*Width].Color=Frame.Color;
		free(POS);//�ͷ��ڴ�
		free(MASK);//�ͷ��ڴ�
		return img;
}
/*
IMAGE*PutImage(IMAGE*Obj,IMAGE*Src,Size x,Size y){
	Size Width,Height;//Ŀ��ͼ����
	Size width,height;//  Դͼ����
	if(Obj){//��Ĭ�ϻ�ͼ�豸����Ļ���ڣ�
		Width =Obj-> getwidth();
		Height=Obj->getheight();
	}
	else{//Ĭ�ϻ�ͼ�豸
		Width = getwidth();
		Height=getheight();
	}
	if(Src){//��Ĭ�ϻ�ͼ�豸����Ļ���ڣ�
		width =Src-> getwidth();
		height=Src->getheight();
	}
	else{//Ĭ�ϻ�ͼ�豸
		width = getwidth();
		height=getheight();
	}
	DWORD*pObj=GetImageBuffer(Obj);
	DWORD*pSrc=GetImageBuffer(Src);
	Size sx,sy,ex,ey,i,j;//��ֹ�����ѭ������
	if(x<0)
		sx=0;
	else
		sx=x;
	return Obj;
}
*/