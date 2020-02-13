
void DrawScroll(){
	WORD i,j;
	for(i=0;i<ScrollWidth;i++)
		for(j=0;j<ScrollHeight;j++)
				if(Pscroll[i+j*ScrollWidth].A>0X80)//不透明
					Pscreen[ScrollX+i+(ScrollY+j)*WinWidth].Color=Pscroll[i+j*ScrollWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(ScrollX,ScrollY,ScrollX+ScrollWidth,ScrollY+ScrollHeight);//刷新
}

void DrawCreSrvSign(){
	WORD i,j;
	for(i=0;i<CreSrvWidth;i++)
		for(j=0;j<CreSrvHeight;j++)
				if(Pcresrv[i+j*CreSrvWidth].A>0X80)//不透明
					Pscreen[CreSrvX+i+(CreSrvY+j)*WinWidth].Color=Pcresrv[i+j*CreSrvWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(CreSrvX,CreSrvY,CreSrvX+CreSrvWidth,CreSrvY+CreSrvHeight);//刷新
}
void DrawJoiSrvSign(){
	WORD i,j;
	for(i=0;i<JoiSrvWidth;i++)
		for(j=0;j<JoiSrvHeight;j++)
				if(Pjoisrv[i+j*JoiSrvWidth].A>0X80)//不透明
					Pscreen[JoiSrvX+i+(JoiSrvY+j)*WinWidth].Color=Pjoisrv[i+j*JoiSrvWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(JoiSrvX,JoiSrvY,JoiSrvX+JoiSrvWidth,JoiSrvY+JoiSrvHeight);//刷新
}

void DrawVisualCharacter(BYTE Num){//画虚化人物
	WORD i,j;
	WORD CX=CharacterX[Num];
	WORD CY=CharacterY[Num];
	WORD CW=CharacterWidth[Num];
	WORD CH=CharacterHeight[Num];
	for(i=0;i<CW;i++)
		for(j=0;j<CH;j++)
			if(Pcharacter[Num][i+j*CW].A>0X80){//不透明
					Pscreen[CX+i+(CY+j)*WinWidth].R=(Pcharacter[Num][i+j*CW].R+Pmenu[CX+i+(CY+j)*WinWidth].R)>>1;
					Pscreen[CX+i+(CY+j)*WinWidth].G=(Pcharacter[Num][i+j*CW].G+Pmenu[CX+i+(CY+j)*WinWidth].G)>>1;
					Pscreen[CX+i+(CY+j)*WinWidth].B=(Pcharacter[Num][i+j*CW].B+Pmenu[CX+i+(CY+j)*WinWidth].B)>>1;
			}
	if(AutoFlushBatchDraw)
		FlushBatchDraw(CX,CY,CX+CW,CY+CH);//刷新
}
void DrawCharacter(BYTE Num){//画人物
	WORD i,j;
	WORD CX=CharacterX[Num];
	WORD CY=CharacterY[Num];
	WORD CW=CharacterWidth[Num];
	WORD CH=CharacterHeight[Num];
	for(i=0;i<CW;i++)
		for(j=0;j<CH;j++)
				if(Pcharacter[Num][i+j*CW].A>0X80)//不透明
					Pscreen[CX+i+(CY+j)*WinWidth].Color=Pcharacter[Num][i+j*CW].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(CX,CY,CX+CW,CY+CH);//刷新
}
void DrawClose(){
	WORD i,j;
	for(i=0;i<CloseWidth;i++)
		for(j=0;j<CloseHeight;j++)
				if(Pclose[i+j*CloseWidth].A>0X80)//不透明
					Pscreen[CloseX+i+(CloseY+j)*WinWidth].Color=Pclose[i+j*CloseWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(CloseX,CloseY,CloseX+CloseWidth,CloseY+CloseHeight);//刷新
}
void DrawClose(WORD X,WORD Y){//指定位置
	WORD i,j;
	for(i=0;i<CloseWidth;i++)
		for(j=0;j<CloseHeight;j++)
				if(Pclose[i+j*CloseWidth].A>0X80)//不透明
					Pscreen[X+i+(Y+j)*WinWidth].Color=Pclose[i+j*CloseWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(X,Y,X+CloseWidth,Y+CloseHeight);//刷新
}

void DrawMenu(){
	WORD i,j;
	for(i=0;i<MenuWidth;i++)
		for(j=0;j<MenuHeight;j++)
			Pscreen[i+j*WinWidth].Color=Pmenu[i+j*MenuWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(0,0,MenuWidth,MenuHeight);//刷新
}



void DrawGameStart(bool Sign){
	WORD i,j;
	for(i=0;i<GameStartWidth;i++)
		for(j=0;j<GameStartHeight;j++)
				if(Pgame[Sign][i+j*GameStartWidth].A>0X80)//不透明
					Pscreen[GameStartX+i+(GameStartY+j)*WinWidth].Color=Pgame[Sign][i+j*GameStartWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(GameStartX,GameStartY,GameStartX+GameStartWidth,GameStartY+GameStartHeight);//刷新
}
void DrawPiece(BYTE x,BYTE y){	//绘制棋子
	WORD SrcX=DB_X+x*PieceSize;	//起点
	WORD SrcY=DB_Y+y*PieceSize;	//起点
	WORD i,j;					//遍历指针

	if(!Map[x][y])//无棋子
		for(i=0;i<PieceSize;i++)
			for(j=0;j<PieceSize;j++)
				Pscreen[SrcX+i+(SrcY+j)*WinWidth].Color=Pboard[SrcX+i+(SrcY+j)*MapWidth].Color;
	else if(Map[x][y]==ValueBlack)
		for(i=0;i<PieceSize;i++)
			for(j=0;j<PieceSize;j++)
				if(Pblack[i+j*PieceSize].A<0X80)//透明
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].Color=Pboard[SrcX+i+(SrcY+j)*MapWidth].Color;
				else							//不透明
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].Color=Pblack[i+j*PieceSize].Color;
	else if(Map[x][y]==ValueWhite)
		for(i=0;i<PieceSize;i++)
			for(j=0;j<PieceSize;j++)
				if(Pwhite[i+j*PieceSize].A<0X80)//透明
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].Color=Pboard[SrcX+i+(SrcY+j)*MapWidth].Color;
				else							//不透明
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].Color=Pwhite[i+j*PieceSize].Color;
				
	if(AutoFlushBatchDraw)
		FlushBatchDraw(SrcX,SrcY,SrcX+PieceSize,SrcY+PieceSize);//刷新
}
void DrawCard(){//画名片
	WORD i,j;
	for(i=0;i<CardWidth;i++)
		for(j=0;j<CardHeight;j++)
				if(Pcard[i+j*CardWidth].A>0X80)//不透明
					Pscreen[CardX+i+(CardY+j)*WinWidth].Color=Pcard[i+j*CardWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(CardX,CardY,CardX+CardWidth,CardX+CardHeight);//刷新
}
void DrawMusicNote(){//画音符
	WORD i,j;
	for(i=0;i<MusicWidth;i++)
		for(j=0;j<MusicHeight;j++)
				if(Pmusic[i+j*MusicWidth].A>0X80)//不透明
					Pscreen[MusicX+i+(MusicY+j)*WinWidth].Color=Pmusic[i+j*MusicWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(MusicX,MusicY,MusicX+MusicWidth,MusicY+MusicHeight);//刷新
}
void DrawSwitch(){//画开关
	WORD i,j;
	for(i=0;i<SwitchWidth;i++)
		for(j=0;j<SwitchHeight;j++)
				if(Pswitch[SwitchState][i+j*SwitchWidth].A>0X80)//不透明
					Pscreen[SwitchX+i+(SwitchY+j)*WinWidth].Color=Pswitch[SwitchState][i+j*SwitchWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(SwitchX,SwitchY,SwitchX+SwitchWidth,SwitchY+SwitchHeight);//刷新
}
void DrawBackGround(){
	WORD i,j;
	for(i=0;i<BackWidth;i++)
		for(j=0;j<BackHeight;j++)
			Pscreen[BackX+i+(BackY+j)*WinWidth].Color=Pback[i+j*BackWidth].Color;
		if(AutoFlushBatchDraw)
			FlushBatchDraw(BackX,BackY,BackX+BackWidth,BackY+BackHeight);//刷新

}
void DrawSign(){
	WORD i,j;
	for(i=0;i<SignWidth;i++)
		for(j=0;j<SignHeight;j++)
				if(Psign[i+j*SignWidth].A>0X80)//不透明
					Pscreen[SignX+i+(SignY+j)*WinWidth].Color=Psign[i+j*SignWidth].Color;
	if(AutoFlushBatchDraw)
		FlushBatchDraw(SignX,SignY,SignX+SignWidth,SignY+SignHeight);//刷新
}
void DrawVisualPiece(BYTE x,BYTE y,BYTE piece){	//绘制虚拟棋子
	WORD SrcX=DB_X+x*PieceSize;	//起点
	WORD SrcY=DB_Y+y*PieceSize;	//起点
	WORD i,j;					//遍历指针

	if(!piece)//无棋子
		for(i=0;i<PieceSize;i++)
			for(j=0;j<PieceSize;j++)
				Pscreen[SrcX+i+(SrcY+j)*WinWidth].Color=Pboard[SrcX+i+(SrcY+j)*MapWidth].Color;
	else if(piece==ValueBlack)
		for(i=0;i<PieceSize;i++)
			for(j=0;j<PieceSize;j++)
				if(Pblack[i+j*PieceSize].A<0X80)//透明
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].Color=Pboard[SrcX+i+(SrcY+j)*MapWidth].Color;
				else{							//不透明
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].R=(Pboard[SrcX+i+(SrcY+j)*MapWidth].R+Pblack[i+j*PieceSize].R)>>1;
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].G=(Pboard[SrcX+i+(SrcY+j)*MapWidth].G+Pblack[i+j*PieceSize].G)>>1;
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].B=(Pboard[SrcX+i+(SrcY+j)*MapWidth].B+Pblack[i+j*PieceSize].B)>>1;
				}
	else if(piece==ValueWhite)
		for(i=0;i<PieceSize;i++)
			for(j=0;j<PieceSize;j++)
				if(Pwhite[i+j*PieceSize].A<0X80)//透明
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].Color=Pboard[SrcX+i+(SrcY+j)*MapWidth].Color;
				else{							//不透明
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].R=(Pboard[SrcX+i+(SrcY+j)*MapWidth].R+Pwhite[i+j*PieceSize].R)>>1;
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].G=(Pboard[SrcX+i+(SrcY+j)*MapWidth].G+Pwhite[i+j*PieceSize].G)>>1;
					Pscreen[SrcX+i+(SrcY+j)*WinWidth].B=(Pboard[SrcX+i+(SrcY+j)*MapWidth].B+Pwhite[i+j*PieceSize].B)>>1;
				}
	if(AutoFlushBatchDraw)
		FlushBatchDraw(SrcX,SrcY,SrcX+PieceSize,SrcY+PieceSize);//刷新
}
void DrawWholeBoard(){
	putimage(0,0,&Board);//绘制棋盘
	for(BYTE i=0;i<MAP_X;i++)
		for(BYTE j=0;j<MAP_Y;j++)
			DrawPiece(i,j);
	if(AutoFlushBatchDraw)
		FlushBatchDraw();//刷新

}
void DrawWholeWnd(){
	DrawWholeBoard();//绘制整个棋盘
	DrawBackGround();//绘制背景
	DrawSign();//绘制标识牌
	DrawSwitch();//绘制开关
	DrawClose();//绘制关闭按钮
	if(SwitchState)
		DrawMusicNote();//绘制音符
	else
		DrawCard();//绘制名片
	if(AutoFlushBatchDraw)
		FlushBatchDraw();//刷新
}
void DrawStartBG(){
	putimage(0,0,&StartBG);
	if(AutoFlushBatchDraw)
		FlushBatchDraw();//刷新
}