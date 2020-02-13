#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include "resource.h"
#include "MemMng.h"//用于分配内存
#include "EasyX++.h"//用于绘图
#include <mmsystem.h>//PlaySound函数的头文件
#pragma comment(lib,"winmm.lib")//链接库，PlaySound函数必须使用 
#pragma   comment(lib,"wsock32.lib")

#define In(x,y,x1,y1,x2,y2) (x>x1&&y>y1&&x<x2&&y<y2)
#define Belong(x,y,X,Y,W,H) (x>X&&y>Y&&x<X+W&&y<Y+H)
#define RandChoose(a,b) (rand()%b<a)

#define MapWidth 610
#define MapHeight MapWidth
#define WinWidth 800
#define WinHeight MapHeight
#define SignWidth 190
#define SignHeight 150
#define BackWidth 190
#define BackHeight MapWidth
#define SwitchWidth 130
#define SwitchHeight 55
#define MusicWidth 190
#define MusicHeight 256
#define CardWidth 190
#define CardHeight 190
#define StartBGWidth WinWidth
#define StartBGHeight WinHeight
#define GameStartWidth 152
#define GameStartHeight 152
#define CloseWidth 40
#define CloseHeight 40
#define MenuWidth WinWidth
#define MenuHeight WinHeight
#define CreSrvWidth 400
#define CreSrvHeight 296
#define JoiSrvWidth 400
#define JoiSrvHeight 260
#define ScrollWidth 400
#define ScrollHeight 190

#define MAP_X 16
#define MAP_Y 16
#define DB_X 17 //起始绘图点
#define DB_Y 17 //起始绘图点
#define SignX 610
#define SignY 0
#define BackX 610
#define BackY 0
#define SwitchX 630
#define SwitchY 200
#define MusicX 610
#define MusicY 300
#define CardX 610
#define CardY 350
#define GameStartX 180
#define GameStartY 70
#define CloseX 760
#define CloseY 0
#define MsgX 643
#define MsgY 76
#define CreSrvX 360
#define CreSrvY 20
#define JoiSrvX 360
#define JoiSrvY 320
#define ScrollX 200
#define ScrollY 200

#define ValueBlack 1
#define ValueWhite 2
#define PieceSize 36

BYTE Map[MAP_X][MAP_Y];//棋盘


bool AutoFlushBatchDraw=true;//自动刷新
bool SwitchState=true;
//资源文件
IMAGE Board;//棋盘
IMAGE Piece[2];//棋子
IMAGE Background;//背景
IMAGE SignBoard;//标识牌
IMAGE BackGround;//标识牌
IMAGE Switch[2];//开关
IMAGE MusicNote;//音符
IMAGE Card;//名片
IMAGE StartBG;//起始画面
IMAGE GameStart[2];//开始游戏按钮
IMAGE Close;//关闭按钮
IMAGE Menu;//菜单
IMAGE Character[2];//人物
IMAGE CreateServerSign;//创建服务器
IMAGE JoinServerSign;//加入服务器
IMAGE Scroll;//卷轴

COLOR*Pscreen;//屏幕内存
COLOR*Pboard ;//棋盘内存
COLOR*Psign ;//标识牌内存
COLOR*Pblack ;//黑棋内存
COLOR*Pwhite;//白棋内存
COLOR*Pback;//背景内存
COLOR*Pswitch[2];//开关内存
COLOR*Pmusic;//音符内存
COLOR*Pcard;//名片内存
COLOR*Pstart;//起始画面内存
COLOR*Pgame[2];//开始游戏按钮内存
COLOR*Pclose;//关闭按钮内存
COLOR*Pmenu;//菜单内存
COLOR*Pcharacter[2];//人物内存
COLOR*Pcresrv;//创建服务器
COLOR*Pjoisrv;//加入服务器
COLOR*Pscroll;//卷轴内存

WORD CharacterWidth[2]={402,400};
WORD CharacterHeight[2]={500,500};
WORD CharacterX[2]={20,420};
WORD CharacterY[2]={35,10};	

#include "音乐.h"
HWND hWnd;

#include "资源处理.h"
#include "DRAW.h"
#include "游戏算法.h"
#include "消息输出.h"
#include "SOCKET通信.h"

