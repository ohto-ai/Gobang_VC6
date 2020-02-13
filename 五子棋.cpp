// ������.cpp : Defines the entry point for the application.


#define Typeface "����"
#include "stdafx.h"
#include <easyx.h>
#include "���Ӻ�.h"
Music StartMusic(STARTMUSIC,"STARTMUSIC","TMP_START.MP3");//��ʼ����������
Music BKmusic(BGM,"BGM","TMP_BGM.MP3");//��ʼ����������

HCURSOR Cur_Force;
HCURSOR Cur_Main;
HCURSOR*NowCur;

#define MouseHit() (SetClassLong(hWnd,GCL_HCURSOR,(LONG)*NowCur),MouseHit())

#include "��Ϸ����.h"

int GameMenu(){
	MOUSEMSG Msg;
	WORD i,j;
	BYTE DrawDone=0;
Begin:
	for(i=0;i<MAP_X;i++)
		for(j=0;j<MAP_Y;j++)
			Map[i][j]=0;
	//��ʼ����
	StartMusic.Play();//��������
	DrawStartBG();
	DrawGameStart(false);
	DrawClose();//���ƹر�
	FlushMouseMsgBuffer();
	while(1){
		if(MouseHit()){//��������
			Msg=GetMouseMsg();//��ȡ�����Ϣ
			if(Msg.uMsg==WM_LBUTTONUP)//�������
				if(Belong(Msg.x,Msg.y,GameStartX,GameStartY,GameStartWidth,GameStartHeight)){//��������
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
					DrawGameStart(false);
					Sleep(20);
					break;
				}
				else if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){//��������
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
					if(MessageBox(hWnd,"��ȷ��Ҫ�˳���","�˳�",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						return 0;
				}
			DrawGameStart(Belong(Msg.x,Msg.y,GameStartX,GameStartY,GameStartWidth,GameStartHeight)&&Pgame[0][Msg.x-GameStartX+(Msg.y-GameStartY)*GameStartWidth].A>0X80);
		}
		Sleep(10);
	}

	DrawMenu();//���Ʋ˵�
	DrawClose();//���ƹر�
	DrawCharacter(0);//��������
	DrawCharacter(1);//��������

	FlushMouseMsgBuffer();
	while(1){
		if(MouseHit()){//��������
			Msg=GetMouseMsg();//��ȡ�����Ϣ
			if(Msg.uMsg==WM_LBUTTONUP){//�������
				if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){//��������
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
					if(MessageBox(hWnd,"��ȷ��Ҫ������","����",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						goto Begin;
				}
				else if(Belong(Msg.x,Msg.y,CharacterX[0],CharacterY[0],CharacterWidth[0],CharacterHeight[0])
					&&Pcharacter[0][Msg.x+Msg.y*CharacterWidth[0]].A>0X80){
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
					//StartMusic.Stop();//�ر�����
					GameMultip();//������Ϸ
					goto Begin;
				}
				else if(Belong(Msg.x,Msg.y,CharacterX[1],CharacterY[1],CharacterWidth[1],CharacterHeight[1])
					&&Pcharacter[1][Msg.x+Msg.y*CharacterWidth[1]].A>0X80){
					StartMusic.Stop();//�ر�����
					GameSingle();//������Ϸ
					goto Begin;
				}
			}
			else if(Belong(Msg.x,Msg.y,CharacterX[0],CharacterY[0],CharacterWidth[0],CharacterHeight[0])
				&&Pcharacter[0][Msg.x-CharacterX[0]+(Msg.y-CharacterY[0])*CharacterWidth[0]].A>0X80){//��������0������
					NowCur=&Cur_Force;
					if(DrawDone!=1){
						PlaySound(MAKEINTRESOURCE(ON),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						if(DrawDone==2)
							DrawCharacter(1);//�ػ�1��
						DrawVisualCharacter(0);
						DrawDone=1;
					}
			}
			else if(Belong(Msg.x,Msg.y,CharacterX[1],CharacterY[1],CharacterWidth[1],CharacterHeight[1])
				&&Pcharacter[1][Msg.x-CharacterX[1]+(Msg.y-CharacterY[1])*CharacterWidth[1]].A>0X80){//��������1������
					NowCur=&Cur_Force;
					if(DrawDone!=2){
						PlaySound(MAKEINTRESOURCE(ON),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						if(DrawDone==1)
							DrawCharacter(0);//�ػ�0��
						DrawVisualCharacter(1);
						DrawDone=2;
					}
			}
			else if(DrawDone==1||DrawDone==2){//�����黯����
				NowCur=&Cur_Main;
				//DrawCharacter((DrawDone=0,DrawDone-1));
				DrawCharacter(DrawDone-1);
				DrawDone=0;
			}
		}
		FlushMouseMsgBuffer();
		Sleep(10);
	}

	return 0;//�˳�
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{


	Cur_Force=(HCURSOR)LoadImage(hInstance,MAKEINTRESOURCE(CUR_FORCE),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE);
	Cur_Main =(HCURSOR)LoadImage(hInstance,MAKEINTRESOURCE(CUR_MAIN ),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE);

	NowCur=&Cur_Main;
	Init();


	GameMenu();

	return 0;
}



