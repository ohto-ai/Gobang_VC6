// 五子棋.cpp : Defines the entry point for the application.


#define Typeface "楷体"
#include "stdafx.h"
#include <easyx.h>
#include "附加宏.h"
Music StartMusic(STARTMUSIC,"STARTMUSIC","TMP_START.MP3");//初始化背景音乐
Music BKmusic(BGM,"BGM","TMP_BGM.MP3");//初始化背景音乐

HCURSOR Cur_Force;
HCURSOR Cur_Main;
HCURSOR*NowCur;

#define MouseHit() (SetClassLong(hWnd,GCL_HCURSOR,(LONG)*NowCur),MouseHit())

#include "游戏过程.h"

int GameMenu(){
	MOUSEMSG Msg;
	WORD i,j;
	BYTE DrawDone=0;
Begin:
	for(i=0;i<MAP_X;i++)
		for(j=0;j<MAP_Y;j++)
			Map[i][j]=0;
	//开始画面
	StartMusic.Play();//播放音乐
	DrawStartBG();
	DrawGameStart(false);
	DrawClose();//绘制关闭
	FlushMouseMsgBuffer();
	while(1){
		if(MouseHit()){//有鼠标操作
			Msg=GetMouseMsg();//获取鼠标消息
			if(Msg.uMsg==WM_LBUTTONUP)//左键弹起
				if(Belong(Msg.x,Msg.y,GameStartX,GameStartY,GameStartWidth,GameStartHeight)){//属于区域
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
					DrawGameStart(false);
					Sleep(20);
					break;
				}
				else if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){//属于区域
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
					if(MessageBox(hWnd,"你确定要退出吗？","退出",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						return 0;
				}
			DrawGameStart(Belong(Msg.x,Msg.y,GameStartX,GameStartY,GameStartWidth,GameStartHeight)&&Pgame[0][Msg.x-GameStartX+(Msg.y-GameStartY)*GameStartWidth].A>0X80);
		}
		Sleep(10);
	}

	DrawMenu();//绘制菜单
	DrawClose();//绘制关闭
	DrawCharacter(0);//绘制人物
	DrawCharacter(1);//绘制人物

	FlushMouseMsgBuffer();
	while(1){
		if(MouseHit()){//有鼠标操作
			Msg=GetMouseMsg();//获取鼠标消息
			if(Msg.uMsg==WM_LBUTTONUP){//左键弹起
				if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){//属于区域
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
					if(MessageBox(hWnd,"你确定要返回吗？","返回",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						goto Begin;
				}
				else if(Belong(Msg.x,Msg.y,CharacterX[0],CharacterY[0],CharacterWidth[0],CharacterHeight[0])
					&&Pcharacter[0][Msg.x+Msg.y*CharacterWidth[0]].A>0X80){
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
					//StartMusic.Stop();//关闭音乐
					GameMultip();//多人游戏
					goto Begin;
				}
				else if(Belong(Msg.x,Msg.y,CharacterX[1],CharacterY[1],CharacterWidth[1],CharacterHeight[1])
					&&Pcharacter[1][Msg.x+Msg.y*CharacterWidth[1]].A>0X80){
					StartMusic.Stop();//关闭音乐
					GameSingle();//单人游戏
					goto Begin;
				}
			}
			else if(Belong(Msg.x,Msg.y,CharacterX[0],CharacterY[0],CharacterWidth[0],CharacterHeight[0])
				&&Pcharacter[0][Msg.x-CharacterX[0]+(Msg.y-CharacterY[0])*CharacterWidth[0]].A>0X80){//绘制虚拟0号人物
					NowCur=&Cur_Force;
					if(DrawDone!=1){
						PlaySound(MAKEINTRESOURCE(ON),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						if(DrawDone==2)
							DrawCharacter(1);//重绘1号
						DrawVisualCharacter(0);
						DrawDone=1;
					}
			}
			else if(Belong(Msg.x,Msg.y,CharacterX[1],CharacterY[1],CharacterWidth[1],CharacterHeight[1])
				&&Pcharacter[1][Msg.x-CharacterX[1]+(Msg.y-CharacterY[1])*CharacterWidth[1]].A>0X80){//绘制虚拟1号人物
					NowCur=&Cur_Force;
					if(DrawDone!=2){
						PlaySound(MAKEINTRESOURCE(ON),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						if(DrawDone==1)
							DrawCharacter(0);//重绘0号
						DrawVisualCharacter(1);
						DrawDone=2;
					}
			}
			else if(DrawDone==1||DrawDone==2){//存在虚化人物
				NowCur=&Cur_Main;
				//DrawCharacter((DrawDone=0,DrawDone-1));
				DrawCharacter(DrawDone-1);
				DrawDone=0;
			}
		}
		FlushMouseMsgBuffer();
		Sleep(10);
	}

	return 0;//退出
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



