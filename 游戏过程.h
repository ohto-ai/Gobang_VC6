

void Init(){
	srand(time(NULL));//��ʼ�������
	LoadResources();//װ����Դ�ļ�
 	initgraph(WinWidth,WinHeight);//��������
	hWnd = GetHWnd();
	SetWindowLong(hWnd,GWL_STYLE,GetWindowLong(hWnd,GWL_STYLE)&(~WS_CAPTION));//ȡ�����
	SetWindowText(hWnd, "������");
	SetWindowPos(hWnd,NULL,100,100,WinWidth,WinHeight,SWP_SHOWWINDOW);
	BeginBatchDraw();//��ʼ������ͼ
	InitResources();//��ʼ����Դ�ļ�
	setbkmode(TRANSPARENT);//���ñ���͸��
}
int GameMultip(){
	//ѡ�񴴽����������߼��������
	

	BYTE MyID;
	MOUSEMSG Msg;
	DWORD i,j;
	
	for(i=0;i<MAP_X;i++)
		for(j=0;j<MAP_Y;j++)
			Map[i][j]=0;

	AutoFlushBatchDraw=false;//�ر��Զ�ˢ��

	DrawMenu();//���Ʋ˵�
	DrawClose();//���ƹر�
	DrawCharacter(0);//��������	
	DrawCreSrvSign();
	DrawJoiSrvSign();

	FlushBatchDraw();//ˢ��
	AutoFlushBatchDraw=true;//�����Զ�ˢ��
	FlushMouseMsgBuffer();

	
	NowCur=&Cur_Main;
	SetClassLong(hWnd,GCL_HCURSOR,(LONG)*NowCur);

	while(1){
		if(MouseHit()){//��������
			Msg=GetMouseMsg();//��ȡ�����Ϣ
			if(Msg.uMsg==WM_LBUTTONUP)//�������
				if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){//��������
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
					if(MessageBox(hWnd,"��ȷ��Ҫ������","����",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						return 0;
				}
				else if(Belong(Msg.x,Msg.y,CreSrvX,CreSrvY,CreSrvWidth,CreSrvHeight)
					&&Pcresrv[Msg.x-CreSrvX+(Msg.y-CreSrvY)*CreSrvWidth].A>0X80){
					//����������
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������

					AutoFlushBatchDraw=false;//�ر��Զ�ˢ��
					DrawScroll();
					settextcolor(0X000000);
					settextstyle(50,0,Typeface);
					outtextxy(300,254,"����ƴ��");
					outtextxy(280,300,"�������");
					FlushBatchDraw();

					CreateServer();//����������
					

					DrawScroll();
					outtextxy(300,254,"���ڵȴ�");
					outtextxy(280,300,"�ͻ�������");
					FlushBatchDraw();

					FlushMouseMsgBuffer();
					while(ConnectAttrib==SOCKET_UNCONNECTED){
						if(MouseHit()){
							Msg=GetMouseMsg();//��ȡ�����Ϣ
							if(Msg.uMsg==WM_LBUTTONUP&&Belong(Msg.x,Msg.y,ScrollX,ScrollY,ScrollWidth,ScrollHeight))
							{
								PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
								ConnectAttrib=SOCKET_DISCONNECT;//�Ͽ�����
								closesocket(SockConnect);//�رռ���
								WSACleanup();
							}
						}
						Sleep(5);
					}

					if(ConnectAttrib==SOCKET_CONNECTED){
						PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						DrawScroll();
						outtextxy(300,254,"���ӳɹ�");
						outtextxy(280,300,"�ͻ�������");
						FlushBatchDraw();
						Sleep(1000);
						StartMusic.Stop();//����ֹͣ
						MyID=1;
						goto Begin;//��ʼ��Ϸ
					}

					DrawMenu();//���Ʋ˵�
					DrawClose();//���ƹر�
					DrawCharacter(0);//��������
					DrawCreSrvSign();
					DrawJoiSrvSign();
					FlushBatchDraw();
					AutoFlushBatchDraw=true;//�����Զ�ˢ��

				}
				else if(Belong(Msg.x,Msg.y,JoiSrvX,JoiSrvY,JoiSrvWidth,JoiSrvHeight)
					&&Pjoisrv[Msg.x-JoiSrvX+(Msg.y-JoiSrvY)*JoiSrvWidth].A>0X80){
					//���ӷ�����
					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������


					AutoFlushBatchDraw=false;//�ر��Զ�ˢ��

					InputBox(SendBuff,16,"�����������IP","���ӷ�����","127.0.0.1",0,0,true);

					DrawScroll();
					settextcolor(0X000000);
					settextstyle(50,0,Typeface);
					outtextxy(300,254,"����Ŭ��");
					outtextxy(280,300,"���ӷ�����");
					FlushBatchDraw();
					CreateClient(SendBuff);
					
					FlushMouseMsgBuffer();
					while(ConnectAttrib==SOCKET_UNCONNECTED){
						if(MouseHit()){
							Msg=GetMouseMsg();//��ȡ�����Ϣ
							if(Msg.uMsg==WM_LBUTTONUP&&Belong(Msg.x,Msg.y,ScrollX,ScrollY,ScrollWidth,ScrollHeight))
							{
								PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
								ConnectAttrib=SOCKET_DISCONNECT;//�Ͽ�����
								closesocket(SockConnect);//�ر�����
								WSACleanup();
								break;
							}
						}
						Sleep(5);
					}

					if(ConnectAttrib==SOCKET_CONNECTED){
						PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						DrawScroll();
						outtextxy(300,254,"���ӳɹ�");
						outtextxy(280,300,"�ͻ�������");
						FlushBatchDraw();
						Sleep(1000);
						StartMusic.Stop();//����ֹͣ
						MyID=2;
						goto Begin;//��ʼ��Ϸ
					}

					PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
					DrawMenu();//���Ʋ˵�
					DrawClose();//���ƹر�
					DrawCharacter(0);//��������
					DrawCreSrvSign();
					DrawJoiSrvSign();
					FlushBatchDraw();
					AutoFlushBatchDraw=true;//�����Զ�ˢ��

				}

		}
		Sleep(10);
	}


Begin://��Ϸ��ʼ
	RenjuMsg SockMsg;

	NowCur=&Cur_Main;
	SetClassLong(hWnd,GCL_HCURSOR,(LONG)*NowCur);

	PlaySound(MAKEINTRESOURCE(START),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
	AutoFlushBatchDraw=false;
	DrawWholeWnd();//����ȫ��
	AutoFlushBatchDraw=true;

	for(i=0;i<WinHeight/2;i++)
	{
		FlushBatchDraw(0,i,WinWidth-1,i);
		FlushBatchDraw(0,WinHeight-i,WinWidth-1,WinHeight-i);
		Sleep(12);
	}
	FlushBatchDraw();
	if(SwitchState)
		BKmusic.Play();//���ű�������

//����

	FlushMouseMsgBuffer();
	bool SignLposDraw=false;//�Ƿ��Ѿ�����
	BYTE Mx,My;//����λ��
	BYTE Lx=0,Ly=0;//��һ�λ�ͼλ��
	BYTE Player=1;
	BYTE SuccessPlayer=0;
	while(!SuccessPlayer){//����ʤ��
		if(Player!=MyID)//�Է�����
			if(MsgQueue.IsNewMsg()){//���µ���Ϣ
				MsgQueue.Read(SockMsg);//��ȡ��Ϣ

				switch(SockMsg.Attrib){
				case A_VisualPiece:
					DrawWholeBoard();//�ػ�����
					if(!Map[SockMsg.Pos.x][SockMsg.Pos.y])//����
							DrawVisualPiece(SockMsg.Pos.x,SockMsg.Pos.y,Player);//������������
					break;
				case A_PieceDown:
					if(!Map[SockMsg.Pos.x][SockMsg.Pos.y]){//����
						if(RandChoose(1,3))
							PlaySound(MAKEINTRESOURCE(PIECE0),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						else if(RandChoose(1,2))
							PlaySound(MAKEINTRESOURCE(PIECE1),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						else
							PlaySound(MAKEINTRESOURCE(PIECE2),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						Map[SockMsg.Pos.x][SockMsg.Pos.y]=Player;
						//DrawWholeBoard();//�ػ�����
						DrawPiece(SockMsg.Pos.x,SockMsg.Pos.y);//��ͼ
						Player=Player==1?2:1;//����˫��		
						PutMsg("�ֵ��ҷ�");
						SuccessPlayer=Check(SockMsg.Pos.x,SockMsg.Pos.y);//���ʤ����
					}
					break;
				}
			}
		if(MouseHit()){//��������
			Msg=GetMouseMsg();//��ȡ�����Ϣ

			if(Belong(Msg.x,Msg.y,DB_X,DB_Y,MAP_X*PieceSize,MAP_Y*PieceSize)){//������
				NowCur=&Cur_Force;
				if(Player==MyID){//�ֵ��Լ�
					//�����Ӧ��������
					Mx=(Msg.x-DB_X)/PieceSize;
					My=(Msg.y-DB_Y)/PieceSize;
					if(Mx!=Lx||My!=Ly){//����������
						if(!Map[Lx][Ly])//����
							DrawVisualPiece(Lx,Ly,0);//��ȥ��������
						Lx=Mx;//��������
						Ly=My;//��������
						if(!Map[Mx][My]){//����
							sprintf_s(SendBuff,"%c%u %u",A_VisualPiece,Mx,My);
							send(SockConnect,SendBuff,SOCKET_DEF_SENDLEN,0);//��������
							DrawVisualPiece(Mx,My,Player);//������������
							SignLposDraw=true;
						}
					}
					if(Msg.uMsg==WM_LBUTTONUP){//�������
						if(!Map[Mx][My]){//����
							sprintf_s(SendBuff,"%c%u %u",A_PieceDown,Mx,My);
							send(SockConnect,SendBuff,SOCKET_DEF_SENDLEN,0);//��������
							if(RandChoose(1,3))
								PlaySound(MAKEINTRESOURCE(PIECE0),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
							else if(RandChoose(1,2))
								PlaySound(MAKEINTRESOURCE(PIECE1),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
							else
								PlaySound(MAKEINTRESOURCE(PIECE2),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
							Map[Mx][My]=Player;
							PutMsg("�ֵ��Է�");
							Player=Player==1?2:1;//����˫��
							DrawPiece(Mx,My);//��ͼ
							SuccessPlayer=Check(Mx,My);//���ʤ����
						}
					}
				}
			}
			else{//������������
				NowCur=&Cur_Main;
				if(SignLposDraw){
					if(!Map[Lx][Ly])//����
						DrawVisualPiece(Mx,My,0);//������������
					SignLposDraw=false;//��ǵ�ǰ����������
				}
				if(Msg.uMsg==WM_LBUTTONUP){//�������
					if(Belong(Msg.x,Msg.y,SwitchX,SwitchY,SwitchWidth,SwitchHeight)){//���ڿ��ص�
						//�л�����
						PlaySound(MAKEINTRESOURCE(BUTTON),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						if(SwitchState=!SwitchState){
							BKmusic.Play();//���ű�������
							AutoFlushBatchDraw=false;
							DrawBackGround();
							DrawSign();//���Ʊ�ʶ��
							DrawMusicNote();//��������
							DrawClose();//�ػ�رհ�ť
							FlushBatchDraw();//ˢ����ʾ
							AutoFlushBatchDraw=true;
						}
						else{
							BKmusic.Pause();
							AutoFlushBatchDraw=false;
							DrawBackGround();
							DrawSign();//���Ʊ�ʶ��
							DrawCard();//������Ƭ
							DrawClose();//�ػ�رհ�ť
							FlushBatchDraw();//ˢ����ʾ
							AutoFlushBatchDraw=true;
						}
						DrawSwitch();//�ػ濪��
					}
					else if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){
						PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						if(MessageBox(hWnd,"��ȷ��Ҫ������","����",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						{
							PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
							closesocket(SockConnect);
							WSACleanup();
							BKmusic.Stop();//ֹͣ����
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
	outtextxy(300,254,"��Ϸ����");
	outtextxy(280,300,SuccessPlayer==1?"�ڷ���ʤ��":"�׷���ʤ��");
	FlushBatchDraw();
	FlushMouseMsgBuffer();
	while(1){
		if(MouseHit()){
			Msg=GetMouseMsg();//��ȡ�����Ϣ
			if(Msg.uMsg==WM_LBUTTONUP&&Belong(Msg.x,Msg.y,ScrollX,ScrollY,ScrollWidth,ScrollHeight)){
				PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
				break;
			}
		}
		Sleep(5);
	}

	BKmusic.Stop();//ֹͣ����
	return 0;
}

int GameSingle(){
	
	NowCur=&Cur_Main;
	SetClassLong(hWnd,GCL_HCURSOR,(LONG)*NowCur);
	PlaySound(MAKEINTRESOURCE(START),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
	AutoFlushBatchDraw=false;
	DrawWholeWnd();//����ȫ��
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
		BKmusic.Play();//���ű�������

	MOUSEMSG Msg;
	FlushMouseMsgBuffer();
	bool SignLposDraw=false;//�Ƿ��Ѿ�����
	BYTE Mx,My;//����λ��
	BYTE Lx=0,Ly=0;//��һ�λ�ͼλ��
	BYTE Player=1;
	BYTE SuccessPlayer=0;
	while(!SuccessPlayer){//����ʤ��
		if(MouseHit()){//��������
			Msg=GetMouseMsg();//��ȡ�����Ϣ

			if(Belong(Msg.x,Msg.y,DB_X,DB_Y,MAP_X*PieceSize,MAP_Y*PieceSize)){//������
				NowCur=&Cur_Force;
				//�����Ӧ��������
				Mx=(Msg.x-DB_X)/PieceSize;
				My=(Msg.y-DB_Y)/PieceSize;
				if(Mx!=Lx||My!=Ly){//����������
					if(!Map[Lx][Ly])//����
						DrawVisualPiece(Lx,Ly,0);//��ȥ��������
					Lx=Mx;//��������
					Ly=My;//��������
					if(!Map[Mx][My]){//����
						DrawVisualPiece(Mx,My,Player);//������������
						SignLposDraw=true;
					}
				}
				if(Msg.uMsg==WM_LBUTTONUP){//�������
					if(!Map[Mx][My]){//����
						if(RandChoose(1,3))
							PlaySound(MAKEINTRESOURCE(PIECE0),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						else if(RandChoose(1,2))
							PlaySound(MAKEINTRESOURCE(PIECE1),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						else
							PlaySound(MAKEINTRESOURCE(PIECE2),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						PutMsg(Player==1?"�ֵ��׷�":"�ֵ��ڷ�");
						Map[Mx][My]=Player;
						Player=Player==1?2:1;//����˫��
						DrawPiece(Mx,My);//��ͼ
						SuccessPlayer=Check(Mx,My);//���ʤ����
					}
				}
			}
			else{
				NowCur=&Cur_Main;
				if(SignLposDraw){
					if(!Map[Lx][Ly])//����
						DrawVisualPiece(Mx,My,0);//������������
					SignLposDraw=false;//��ǵ�ǰ����������
				}
				if(Msg.uMsg==WM_LBUTTONUP){//�������
					if(Belong(Msg.x,Msg.y,SwitchX,SwitchY,SwitchWidth,SwitchHeight)){//���ڿ��ص�
						//�л�����
						PlaySound(MAKEINTRESOURCE(BUTTON),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						if(SwitchState=!SwitchState){
							BKmusic.Play();//���ű�������
							AutoFlushBatchDraw=false;
							DrawBackGround();
							DrawSign();//���Ʊ�ʶ��
							DrawMusicNote();//��������
							DrawClose();//�ػ�رհ�ť
							FlushBatchDraw();//ˢ����ʾ
							AutoFlushBatchDraw=true;
						}
						else{
							BKmusic.Pause();
							AutoFlushBatchDraw=false;
							DrawBackGround();
							DrawSign();//���Ʊ�ʶ��
							DrawCard();//������Ƭ
							DrawClose();//�ػ�رհ�ť
							FlushBatchDraw();//ˢ����ʾ
							AutoFlushBatchDraw=true;
						}
						DrawSwitch();//�ػ濪��
					}
					else if(Belong(Msg.x,Msg.y,CloseX,CloseY,CloseWidth,CloseHeight)){
						PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
						if(MessageBox(hWnd,"��ȷ��Ҫ������","����",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND)==IDYES)
						{
							PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
							BKmusic.Stop();//ֹͣ����
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
	outtextxy(300,254,"��Ϸ����");
	outtextxy(280,300,SuccessPlayer==1?"�ڷ���ʤ��":"�׷���ʤ��");
	FlushBatchDraw();
	FlushMouseMsgBuffer();
	while(1){
		if(MouseHit()){
			Msg=GetMouseMsg();//��ȡ�����Ϣ
			if(Msg.uMsg==WM_LBUTTONUP&&Belong(Msg.x,Msg.y,ScrollX,ScrollY,ScrollWidth,ScrollHeight)){
				PlaySound(MAKEINTRESOURCE(CLICK),NULL,SND_RESOURCE|SND_NODEFAULT|SND_ASYNC);//��������
				break;
			}
		}
		Sleep(5);
	}
	BKmusic.Stop();//ֹͣ����
	return 0;
}
