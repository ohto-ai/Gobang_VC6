

void Init(){
	srand(time(NULL));//初始化随机数
	LoadResources();//装载资源文件
 	initgraph(WinWidth,WinHeight);//创建窗口
	hWnd = GetHWnd();
	SetWindowLong(hWnd,GWL_STYLE,GetWindowLong(hWnd,GWL_STYLE)&(~WS_CAPTION));//取消框框
	SetWindowText(hWnd, "五子棋");
	SetWindowPos(hWnd,NULL,100,100,WinWidth,WinHeight,SWP_SHOWWINDOW);
	BeginBatchDraw();//开始批量绘图
	InitResources();//初始化资源文件
	setbkmode(TRANSPARENT);//设置背景透明
}
int GameMultip(){
	//选择创建服务器或者加入服务器
	

	BYTE MyID;
	MOUSEMSG Msg;
	DWORD i,j;
	
	for(i=0;i<MAP_X;i++)
		for(j=0;j<MAP_Y;j++)
			Map[i][j]=0;

	AutoFlushBatchDraw=false;//关闭自动刷新

	DrawMenu();//绘制菜单
	DrawClose();//绘制关闭
	DrawCharacter(0);//绘制人物	
	DrawCreSrvSign();
	DrawJoiSrvSign();

	FlushBatchDraw();//刷新
	AutoFlushBatchDraw=true;//开启自动刷新
	FlushMouseMsgBuffer();

	
	NowCur=&Cur_Main;
	SetClassLong(hWnd,GCL_HCURSOR,(LONG)*NowCur);

	while(1){
		if(MouseHit()){//有鼠标操作
			Msg=GetMouseMsg();//获取鼠标消息
			if(Msg.uMsg==WM_LBUTTONUP)//左键弹起
				if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){//属于区域
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
					if(MessageBox(hWnd,"你确定要返回吗？","返回",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						return 0;
				}
				else if(Belong(Msg.x,Msg.y,CreSrvX,CreSrvY,CreSrvWidth,CreSrvHeight)
					&&Pcresrv[Msg.x-CreSrvX+(Msg.y-CreSrvY)*CreSrvWidth].A>0X80){
					//创建服务器
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐

					AutoFlushBatchDraw=false;//关闭自动刷新
					DrawScroll();
					settextcolor(0X000000);
					settextstyle(50,0,Typeface);
					outtextxy(300,254,"正在拼命");
					outtextxy(280,300,"搭建服务器");
					FlushBatchDraw();

					CreateServer();//创建服务器
					

					DrawScroll();
					outtextxy(300,254,"正在等待");
					outtextxy(280,300,"客户端连接");
					FlushBatchDraw();

					FlushMouseMsgBuffer();
					while(ConnectAttrib==SOCKET_UNCONNECTED){
						if(MouseHit()){
							Msg=GetMouseMsg();//获取鼠标消息
							if(Msg.uMsg==WM_LBUTTONUP&&Belong(Msg.x,Msg.y,ScrollX,ScrollY,ScrollWidth,ScrollHeight))
							{
								PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
								ConnectAttrib=SOCKET_DISCONNECT;//断开连接
								closesocket(SockConnect);//关闭监听
								WSACleanup();
							}
						}
						Sleep(5);
					}

					if(ConnectAttrib==SOCKET_CONNECTED){
						PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						DrawScroll();
						outtextxy(300,254,"连接成功");
						outtextxy(280,300,"客户端连接");
						FlushBatchDraw();
						Sleep(1000);
						StartMusic.Stop();//音乐停止
						MyID=1;
						goto Begin;//开始游戏
					}

					DrawMenu();//绘制菜单
					DrawClose();//绘制关闭
					DrawCharacter(0);//绘制人物
					DrawCreSrvSign();
					DrawJoiSrvSign();
					FlushBatchDraw();
					AutoFlushBatchDraw=true;//开启自动刷新

				}
				else if(Belong(Msg.x,Msg.y,JoiSrvX,JoiSrvY,JoiSrvWidth,JoiSrvHeight)
					&&Pjoisrv[Msg.x-JoiSrvX+(Msg.y-JoiSrvY)*JoiSrvWidth].A>0X80){
					//连接服务器
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐


					AutoFlushBatchDraw=false;//关闭自动刷新

					InputBox(SendBuff,16,"请输入服务器IP","连接服务器","127.0.0.1",0,0,true);

					DrawScroll();
					settextcolor(0X000000);
					settextstyle(50,0,Typeface);
					outtextxy(300,254,"正在努力");
					outtextxy(280,300,"连接服务器");
					FlushBatchDraw();
					CreateClient(SendBuff);
					
					FlushMouseMsgBuffer();
					while(ConnectAttrib==SOCKET_UNCONNECTED){
						if(MouseHit()){
							Msg=GetMouseMsg();//获取鼠标消息
							if(Msg.uMsg==WM_LBUTTONUP&&Belong(Msg.x,Msg.y,ScrollX,ScrollY,ScrollWidth,ScrollHeight))
							{
								PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
								ConnectAttrib=SOCKET_DISCONNECT;//断开连接
								closesocket(SockConnect);//关闭连接
								WSACleanup();
								break;
							}
						}
						Sleep(5);
					}

					if(ConnectAttrib==SOCKET_CONNECTED){
						PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						DrawScroll();
						outtextxy(300,254,"连接成功");
						outtextxy(280,300,"客户端连接");
						FlushBatchDraw();
						Sleep(1000);
						StartMusic.Stop();//音乐停止
						MyID=2;
						goto Begin;//开始游戏
					}

					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
					DrawMenu();//绘制菜单
					DrawClose();//绘制关闭
					DrawCharacter(0);//绘制人物
					DrawCreSrvSign();
					DrawJoiSrvSign();
					FlushBatchDraw();
					AutoFlushBatchDraw=true;//开启自动刷新

				}

		}
		Sleep(10);
	}


Begin://游戏开始
	RenjuMsg SockMsg;

	NowCur=&Cur_Main;
	SetClassLong(hWnd,GCL_HCURSOR,(LONG)*NowCur);

	PlaySound(MAKEINTRESOURCE(START),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
	AutoFlushBatchDraw=false;
	DrawWholeWnd();//绘制全屏
	AutoFlushBatchDraw=true;

	for(i=0;i<WinHeight/2;i++)
	{
		FlushBatchDraw(0,i,WinWidth-1,i);
		FlushBatchDraw(0,WinHeight-i,WinWidth-1,WinHeight-i);
		Sleep(12);
	}
	FlushBatchDraw();
	if(SwitchState)
		BKmusic.Play();//播放背景音乐

//绘制

	FlushMouseMsgBuffer();
	bool SignLposDraw=false;//是否已经绘制
	BYTE Mx,My;//棋盘位置
	BYTE Lx=0,Ly=0;//上一次绘图位置
	BYTE Player=1;
	BYTE SuccessPlayer=0;
	while(!SuccessPlayer){//无人胜利
		if(Player!=MyID)//对方下棋
			if(MsgQueue.IsNewMsg()){//有新的消息
				MsgQueue.Read(SockMsg);//读取消息

				switch(SockMsg.Attrib){
				case A_VisualPiece:
					DrawWholeBoard();//重绘棋盘
					if(!Map[SockMsg.Pos.x][SockMsg.Pos.y])//无子
							DrawVisualPiece(SockMsg.Pos.x,SockMsg.Pos.y,Player);//绘制虚拟棋子
					break;
				case A_PieceDown:
					if(!Map[SockMsg.Pos.x][SockMsg.Pos.y]){//无子
						if(RandChoose(1,3))
							PlaySound(MAKEINTRESOURCE(PIECE0),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						else if(RandChoose(1,2))
							PlaySound(MAKEINTRESOURCE(PIECE1),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						else
							PlaySound(MAKEINTRESOURCE(PIECE2),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						Map[SockMsg.Pos.x][SockMsg.Pos.y]=Player;
						//DrawWholeBoard();//重绘棋盘
						DrawPiece(SockMsg.Pos.x,SockMsg.Pos.y);//绘图
						Player=Player==1?2:1;//交换双方		
						PutMsg("轮到我方");
						SuccessPlayer=Check(SockMsg.Pos.x,SockMsg.Pos.y);//检测胜利者
					}
					break;
				}
			}
		if(MouseHit()){//有鼠标操作
			Msg=GetMouseMsg();//获取鼠标消息

			if(Belong(Msg.x,Msg.y,DB_X,DB_Y,MAP_X*PieceSize,MAP_Y*PieceSize)){//棋盘区
				NowCur=&Cur_Force;
				if(Player==MyID){//轮到自己
					//计算对应棋盘坐标
					Mx=(Msg.x-DB_X)/PieceSize;
					My=(Msg.y-DB_Y)/PieceSize;
					if(Mx!=Lx||My!=Ly){//绘制新棋子
						if(!Map[Lx][Ly])//无子
							DrawVisualPiece(Lx,Ly,0);//擦去虚拟棋子
						Lx=Mx;//更新坐标
						Ly=My;//更新坐标
						if(!Map[Mx][My]){//无子
							sprintf_s(SendBuff,"%c%u %u",A_VisualPiece,Mx,My);
							send(SockConnect,SendBuff,SOCKET_DEF_SENDLEN,0);//发送数据
							DrawVisualPiece(Mx,My,Player);//绘制虚拟棋子
							SignLposDraw=true;
						}
					}
					if(Msg.uMsg==WM_LBUTTONUP){//左键弹起
						if(!Map[Mx][My]){//无子
							sprintf_s(SendBuff,"%c%u %u",A_PieceDown,Mx,My);
							send(SockConnect,SendBuff,SOCKET_DEF_SENDLEN,0);//发送数据
							if(RandChoose(1,3))
								PlaySound(MAKEINTRESOURCE(PIECE0),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
							else if(RandChoose(1,2))
								PlaySound(MAKEINTRESOURCE(PIECE1),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
							else
								PlaySound(MAKEINTRESOURCE(PIECE2),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
							Map[Mx][My]=Player;
							PutMsg("轮到对方");
							Player=Player==1?2:1;//交换双方
							DrawPiece(Mx,My);//绘图
							SuccessPlayer=Check(Mx,My);//检测胜利者
						}
					}
				}
			}
			else{//不属于棋盘区
				NowCur=&Cur_Main;
				if(SignLposDraw){
					if(!Map[Lx][Ly])//无子
						DrawVisualPiece(Mx,My,0);//擦除虚拟棋子
					SignLposDraw=false;//标记当前无虚拟棋子
				}
				if(Msg.uMsg==WM_LBUTTONUP){//左键弹起
					if(Belong(Msg.x,Msg.y,SwitchX,SwitchY,SwitchWidth,SwitchHeight)){//属于开关点
						//切换音乐
						PlaySound(MAKEINTRESOURCE(BUTTON),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						if(SwitchState=!SwitchState){
							BKmusic.Play();//播放背景音乐
							AutoFlushBatchDraw=false;
							DrawBackGround();
							DrawSign();//绘制标识牌
							DrawMusicNote();//绘制音符
							DrawClose();//重绘关闭按钮
							FlushBatchDraw();//刷新显示
							AutoFlushBatchDraw=true;
						}
						else{
							BKmusic.Pause();
							AutoFlushBatchDraw=false;
							DrawBackGround();
							DrawSign();//绘制标识牌
							DrawCard();//绘制名片
							DrawClose();//重绘关闭按钮
							FlushBatchDraw();//刷新显示
							AutoFlushBatchDraw=true;
						}
						DrawSwitch();//重绘开关
					}
					else if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){
						PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						if(MessageBox(hWnd,"你确定要返回吗？","返回",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						{
							PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
							closesocket(SockConnect);
							WSACleanup();
							BKmusic.Stop();//停止音乐
							return 0;
						}
					}
				}
			}
		}
		FlushMouseMsgBuffer();
		Sleep(10);
	}

	DrawScroll();
	settextcolor(0X000000);
	settextstyle(50,0,Typeface);
	outtextxy(300,254,"游戏结束");
	outtextxy(280,300,SuccessPlayer==1?"黑方获胜！":"白方获胜！");
	FlushBatchDraw();
	FlushMouseMsgBuffer();
	while(1){
		if(MouseHit()){
			Msg=GetMouseMsg();//获取鼠标消息
			if(Msg.uMsg==WM_LBUTTONUP&&Belong(Msg.x,Msg.y,ScrollX,ScrollY,ScrollWidth,ScrollHeight)){
				PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
				break;
			}
		}
		Sleep(5);
	}

	BKmusic.Stop();//停止音乐
	return 0;
}

int GameSingle(){
	
	NowCur=&Cur_Main;
	SetClassLong(hWnd,GCL_HCURSOR,(LONG)*NowCur);
	PlaySound(MAKEINTRESOURCE(START),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
	AutoFlushBatchDraw=false;
	DrawWholeWnd();//绘制全屏
	AutoFlushBatchDraw=true;
	WORD i;
	for(i=0;i<WinHeight/2;i++)
	{
		FlushBatchDraw(0,i,WinWidth-1,i);
		FlushBatchDraw(0,WinHeight-i,WinWidth-1,WinHeight-i);
		Sleep(12);
	}
	FlushBatchDraw();
	if(SwitchState)
		BKmusic.Play();//播放背景音乐

	MOUSEMSG Msg;
	FlushMouseMsgBuffer();
	bool SignLposDraw=false;//是否已经绘制
	BYTE Mx,My;//棋盘位置
	BYTE Lx=0,Ly=0;//上一次绘图位置
	BYTE Player=1;
	BYTE SuccessPlayer=0;
	while(!SuccessPlayer){//无人胜利
		if(MouseHit()){//有鼠标操作
			Msg=GetMouseMsg();//获取鼠标消息

			if(Belong(Msg.x,Msg.y,DB_X,DB_Y,MAP_X*PieceSize,MAP_Y*PieceSize)){//棋盘区
				NowCur=&Cur_Force;
				//计算对应棋盘坐标
				Mx=(Msg.x-DB_X)/PieceSize;
				My=(Msg.y-DB_Y)/PieceSize;
				if(Mx!=Lx||My!=Ly){//绘制新棋子
					if(!Map[Lx][Ly])//无子
						DrawVisualPiece(Lx,Ly,0);//擦去虚拟棋子
					Lx=Mx;//更新坐标
					Ly=My;//更新坐标
					if(!Map[Mx][My]){//无子
						DrawVisualPiece(Mx,My,Player);//绘制虚拟棋子
						SignLposDraw=true;
					}
				}
				if(Msg.uMsg==WM_LBUTTONUP){//左键弹起
					if(!Map[Mx][My]){//无子
						if(RandChoose(1,3))
							PlaySound(MAKEINTRESOURCE(PIECE0),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						else if(RandChoose(1,2))
							PlaySound(MAKEINTRESOURCE(PIECE1),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						else
							PlaySound(MAKEINTRESOURCE(PIECE2),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						PutMsg(Player==1?"轮到白方":"轮到黑方");
						Map[Mx][My]=Player;
						Player=Player==1?2:1;//交换双方
						DrawPiece(Mx,My);//绘图
						SuccessPlayer=Check(Mx,My);//检测胜利者
					}
				}
			}
			else{
				NowCur=&Cur_Main;
				if(SignLposDraw){
					if(!Map[Lx][Ly])//无子
						DrawVisualPiece(Mx,My,0);//擦除虚拟棋子
					SignLposDraw=false;//标记当前无虚拟棋子
				}
				if(Msg.uMsg==WM_LBUTTONUP){//左键弹起
					if(Belong(Msg.x,Msg.y,SwitchX,SwitchY,SwitchWidth,SwitchHeight)){//属于开关点
						//切换音乐
						PlaySound(MAKEINTRESOURCE(BUTTON),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						if(SwitchState=!SwitchState){
							BKmusic.Play();//播放背景音乐
							AutoFlushBatchDraw=false;
							DrawBackGround();
							DrawSign();//绘制标识牌
							DrawMusicNote();//绘制音符
							DrawClose();//重绘关闭按钮
							FlushBatchDraw();//刷新显示
							AutoFlushBatchDraw=true;
						}
						else{
							BKmusic.Pause();
							AutoFlushBatchDraw=false;
							DrawBackGround();
							DrawSign();//绘制标识牌
							DrawCard();//绘制名片
							DrawClose();//重绘关闭按钮
							FlushBatchDraw();//刷新显示
							AutoFlushBatchDraw=true;
						}
						DrawSwitch();//重绘开关
					}
					else if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){
						PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
						if(MessageBox(hWnd,"你确定要返回吗？","返回",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						{
							PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
							BKmusic.Stop();//停止音乐
							return 0;
						}
					}
				}
			}
		}
		FlushMouseMsgBuffer();
		Sleep(10);
	}

	DrawScroll();
	settextcolor(0X000000);
	settextstyle(50,0,Typeface);
	outtextxy(300,254,"游戏结束");
	outtextxy(280,300,SuccessPlayer==1?"黑方获胜！":"白方获胜！");
	FlushBatchDraw();
	FlushMouseMsgBuffer();
	while(1){
		if(MouseHit()){
			Msg=GetMouseMsg();//获取鼠标消息
			if(Msg.uMsg==WM_LBUTTONUP&&Belong(Msg.x,Msg.y,ScrollX,ScrollY,ScrollWidth,ScrollHeight)){
				PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//播放音乐
				break;
			}
		}
		Sleep(5);
	}
	BKmusic.Stop();//停止音乐
	return 0;
}
