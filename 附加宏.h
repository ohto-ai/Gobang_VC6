#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include "resource.h"
#include "MemMng.h"//���ڷ����ڴ�
#include "EasyX++.h"//���ڻ�ͼ
#include <mmsystem.h>//PlaySound������ͷ�ļ�
#pragma comment(lib,"winmm.lib")//���ӿ⣬PlaySound��������ʹ�� 
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
#define DB_X 17 //��ʼ��ͼ��
#define DB_Y 17 //��ʼ��ͼ��
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

BYTE Map[MAP_X][MAP_Y];//����


bool AutoFlushBatchDraw=true;//�Զ�ˢ��
bool SwitchState=true;
//��Դ�ļ�
IMAGE Board;//����
IMAGE Piece[2];//����
IMAGE Background;//����
IMAGE SignBoard;//��ʶ��
IMAGE BackGround;//��ʶ��
IMAGE Switch[2];//����
IMAGE MusicNote;//����
IMAGE Card;//��Ƭ
IMAGE StartBG;//��ʼ����
IMAGE GameStart[2];//��ʼ��Ϸ��ť
IMAGE Close;//�رհ�ť
IMAGE Menu;//�˵�
IMAGE Character[2];//����
IMAGE CreateServerSign;//����������
IMAGE JoinServerSign;//���������
IMAGE Scroll;//����

COLOR*Pscreen;//��Ļ�ڴ�
COLOR*Pboard ;//�����ڴ�
COLOR*Psign ;//��ʶ���ڴ�
COLOR*Pblack ;//�����ڴ�
COLOR*Pwhite;//�����ڴ�
COLOR*Pback;//�����ڴ�
COLOR*Pswitch[2];//�����ڴ�
COLOR*Pmusic;//�����ڴ�
COLOR*Pcard;//��Ƭ�ڴ�
COLOR*Pstart;//��ʼ�����ڴ�
COLOR*Pgame[2];//��ʼ��Ϸ��ť�ڴ�
COLOR*Pclose;//�رհ�ť�ڴ�
COLOR*Pmenu;//�˵��ڴ�
COLOR*Pcharacter[2];//�����ڴ�
COLOR*Pcresrv;//����������
COLOR*Pjoisrv;//���������
COLOR*Pscroll;//�����ڴ�

WORD CharacterWidth[2]={402,400};
WORD CharacterHeight[2]={500,500};
WORD CharacterX[2]={20,420};
WORD CharacterY[2]={35,10};	

#include "����.h"
HWND hWnd;

#include "��Դ����.h"
#include "DRAW.h"
#include "��Ϸ�㷨.h"
#include "��Ϣ���.h"
#include "SOCKETͨ��.h"

