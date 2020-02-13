void LoadResources(){//装载资源文件
	loadimage(&Board,"IMAGE","BOARD",MapWidth,MapHeight);
	loadimage(&Piece[0],"IMAGE","BLACK",PieceSize,PieceSize);
	loadimage(&Piece[1],"IMAGE","WHITE",PieceSize,PieceSize);
	loadimage(&SignBoard,"IMAGE","SIGNBOARD",SignWidth,SignHeight);
	loadimage(&BackGround,"IMAGE","BACKGROUND",BackWidth,BackHeight);
	loadimage(&Switch[0],"IMAGE","SWITCH_OFF",SwitchWidth,SwitchHeight);
	loadimage(&Switch[1],"IMAGE","SWITCH_ON",SwitchWidth,SwitchHeight);
	loadimage(&MusicNote,"IMAGE","MUSICNOTE",MusicWidth,MusicHeight);
	loadimage(&Card,"IMAGE","名片",CardWidth,CardHeight);
	loadimage(&StartBG,"IMAGE","起始画面",StartBGWidth,StartBGHeight);
	loadimage(&GameStart[0],"IMAGE","GAMESTART0",GameStartWidth,GameStartHeight);
	loadimage(&GameStart[1],"IMAGE","GAMESTART1",GameStartWidth,GameStartHeight);
	loadimage(&Close,"IMAGE","CLOSE",CloseWidth,CloseHeight);
	loadimage(&Menu,"IMAGE","MENU",MenuWidth,MenuHeight);
	loadimage(&Character[0],"IMAGE","CHARACTER0",CharacterWidth[0],CharacterHeight[0]);
	loadimage(&Character[1],"IMAGE","CHARACTER1",CharacterWidth[1],CharacterHeight[1]);
	loadimage(&CreateServerSign,"IMAGE","CreateServerSign",CreSrvWidth,CreSrvHeight);
	loadimage(&JoinServerSign,"IMAGE","JoinServerSign",JoiSrvWidth,JoiSrvHeight);
	loadimage(&Scroll,"IMAGE","SCROLL",ScrollWidth,ScrollHeight);

}
void InitResources(){//初始化资源文件
	Pscreen   =(COLOR*)GetImageBuffer(NULL  );//获取屏幕内存
	Pboard    =(COLOR*)GetImageBuffer(&Board);//获得棋盘内存
	Psign     =(COLOR*)GetImageBuffer(&SignBoard);//获得标识牌内存
	Pblack    =(COLOR*)GetImageBuffer(&Piece[0]);//获得黑棋内存
	Pwhite    =(COLOR*)GetImageBuffer(&Piece[1]);//获得白棋内存
	Pswitch[0]=(COLOR*)GetImageBuffer(&Switch[0]);//获得黑棋内存
	Pswitch[1]=(COLOR*)GetImageBuffer(&Switch[1]);//获得白棋内存
	Pback     =(COLOR*)GetImageBuffer(&BackGround);//获得背景内存
	Pmusic    =(COLOR*)GetImageBuffer(&MusicNote);//获得音符内存
	Pcard     =(COLOR*)GetImageBuffer(&Card);//获得名片内存
	Pstart    =(COLOR*)GetImageBuffer(&StartBG);//获得开始界面内存
	Pgame[0]  =(COLOR*)GetImageBuffer(&GameStart[0]);//获得开始游戏按钮内存
	Pgame[1]  =(COLOR*)GetImageBuffer(&GameStart[1]);//获得开始游戏按钮内存
	Pclose    =(COLOR*)GetImageBuffer(&Close);//获得关闭按钮内存
	Pmenu     =(COLOR*)GetImageBuffer(&Menu);//获得菜单内存
	Pcharacter[0]=(COLOR*)GetImageBuffer(&Character[0]);//获得人物内存
	Pcharacter[1]=(COLOR*)GetImageBuffer(&Character[1]);//获得人物内存
	Pcresrv   =(COLOR*)GetImageBuffer(&CreateServerSign);//获得创建服务器内存
	Pjoisrv   =(COLOR*)GetImageBuffer(&JoinServerSign);//获得加入服务器内存
	Pscroll   =(COLOR*)GetImageBuffer(&Scroll);//获得菜单内存

	IMAGE PieceNot[2];//掩码
	IMAGE SignBoardNot;//掩码
	IMAGE SwitchNot[2];//掩码
	IMAGE MusicNoteNot;//掩码
	IMAGE CardNot;//掩码
	IMAGE GameStartNot[2];//掩码
	IMAGE CloseNot;//掩码
	IMAGE CharacterNot[2];//掩码
	IMAGE CreateServerSignNot;//掩码
	IMAGE JoinServerSignNot;//掩码
	IMAGE ScrollNot;//掩码
	loadimage(&PieceNot[0],"IMAGE","BLACK~",PieceSize,PieceSize);
	loadimage(&PieceNot[1],"IMAGE","WHITE~",PieceSize,PieceSize);
	loadimage(&SwitchNot[0],"IMAGE","SWITCH_OFF~",SwitchWidth,SwitchHeight);
	loadimage(&SwitchNot[1],"IMAGE","SWITCH_ON~",SwitchWidth,SwitchHeight);
	loadimage(&SignBoardNot,"IMAGE","SIGNBOARD~",SignWidth,SignHeight);
	loadimage(&MusicNoteNot,"IMAGE","MUSICNOTE~",MusicWidth,MusicHeight);
	loadimage(&CardNot,"IMAGE","名片~",CardWidth,CardHeight);
	loadimage(&GameStartNot[0],"IMAGE","GAMESTART0~",GameStartWidth,GameStartHeight);
	loadimage(&GameStartNot[1],"IMAGE","GAMESTART1~",GameStartWidth,GameStartHeight);
	loadimage(&CloseNot,"IMAGE","CLOSE~",CloseWidth,CloseHeight);
	loadimage(&CharacterNot[0],"IMAGE","CHARACTER0~",CharacterWidth[0],CharacterHeight[0]);
	loadimage(&CharacterNot[1],"IMAGE","CHARACTER1~",CharacterWidth[1],CharacterHeight[1]);
	loadimage(&CreateServerSignNot,"IMAGE","CreateServerSign~",CreSrvWidth,CreSrvHeight);
	loadimage(&JoinServerSignNot,"IMAGE","JoinServerSign~",JoiSrvWidth,JoiSrvHeight);
	loadimage(&ScrollNot,"IMAGE","SCROLL~",ScrollWidth,ScrollHeight);

	WORD i,j;
	COLOR*PBuf;
	PBuf=(COLOR*)GetImageBuffer(&PieceNot[0]);
	for(i=0;i<PieceSize;i++)
		for(j=0;j<PieceSize;j++)
			if(PBuf[i+j*PieceSize].R>0X80)//透明
				Pblack[i+j*PieceSize].A=0XFF;//设置透明
	PBuf=(COLOR*)GetImageBuffer(&PieceNot[1]);
	for(i=0;i<PieceSize;i++)
		for(j=0;j<PieceSize;j++)
			if(PBuf[i+j*PieceSize].R>0X80)//透明
				Pwhite[i+j*PieceSize].A=0XFF;//设置透明

	PBuf=(COLOR*)GetImageBuffer(&SwitchNot[0]);
	for(i=0;i<SwitchWidth;i++)
		for(j=0;j<SwitchHeight;j++)
			if(PBuf[i+j*SwitchWidth].R>0X80)//透明
				Pswitch[0][i+j*SwitchWidth].A=0XFF;//设置透明
	PBuf=(COLOR*)GetImageBuffer(&SwitchNot[1]);
	for(i=0;i<SwitchWidth;i++)
		for(j=0;j<SwitchHeight;j++)
			if(PBuf[i+j*SwitchWidth].R>0X80)//透明
				Pswitch[1][i+j*SwitchWidth].A=0XFF;//设置透明

	PBuf=(COLOR*)GetImageBuffer(&SignBoardNot);
	for(i=0;i<SignWidth;i++)
		for(j=0;j<SignHeight;j++)
			if(PBuf[i+j*SignWidth].R>0X80)//透明
				Psign[i+j*SignWidth].A=0XFF;//设置透明			
	PBuf=(COLOR*)GetImageBuffer(&MusicNoteNot);
	for(i=0;i<MusicWidth;i++)
		for(j=0;j<MusicHeight;j++)
			if(PBuf[i+j*MusicWidth].R>0X80)//透明
				Pmusic[i+j*MusicWidth].A=0XFF;//设置透明
	PBuf=(COLOR*)GetImageBuffer(&CardNot);
	for(i=0;i<CardWidth;i++)
		for(j=0;j<CardHeight;j++)
			if(PBuf[i+j*CardWidth].R>0X80)//透明
				Pcard[i+j*CardWidth].A=0XFF;//设置透明
	PBuf=(COLOR*)GetImageBuffer(&GameStartNot[0]);
	for(i=0;i<GameStartWidth;i++)
		for(j=0;j<GameStartHeight;j++)
			if(PBuf[i+j*GameStartWidth].R>0X80)//透明
				Pgame[0][i+j*GameStartWidth].A=0XFF;//设置透明
	PBuf=(COLOR*)GetImageBuffer(&GameStartNot[1]);
	for(i=0;i<GameStartWidth;i++)
		for(j=0;j<GameStartHeight;j++)
			if(PBuf[i+j*GameStartWidth].R>0X80)//透明
				Pgame[1][i+j*GameStartWidth].A=0XFF;//设置透明
	PBuf=(COLOR*)GetImageBuffer(&CloseNot);
	for(i=0;i<CloseWidth;i++)
		for(j=0;j<CloseHeight;j++)
			if(PBuf[i+j*CloseWidth].R>0X80)//透明
				Pclose[i+j*CloseWidth].A=0XFF;//设置透明
	PBuf=(COLOR*)GetImageBuffer(&CharacterNot[0]);
	for(i=0;i<CharacterWidth[0];i++)
		for(j=0;j<CharacterHeight[0];j++)
			if(PBuf[i+j*CharacterWidth[0]].R>0X80)//透明
				Pcharacter[0][i+j*CharacterWidth[0]].A=0XFF;//设置透明
	PBuf=(COLOR*)GetImageBuffer(&CharacterNot[1]);
	for(i=0;i<CharacterWidth[1];i++)
		for(j=0;j<CharacterHeight[1];j++)
			if(PBuf[i+j*CharacterWidth[1]].R>0X80)//透明
				Pcharacter[1][i+j*CharacterWidth[1]].A=0XFF;//设置透明


	PBuf=(COLOR*)GetImageBuffer(&CreateServerSignNot);
	for(i=0;i<CreSrvWidth;i++)
		for(j=0;j<CreSrvHeight;j++)
			if(PBuf[i+j*CreSrvWidth].R>0X80)//透明
				Pcresrv[i+j*CreSrvWidth].A=0XFF;//设置透明

	PBuf=(COLOR*)GetImageBuffer(&JoinServerSignNot);
	for(i=0;i<JoiSrvWidth;i++)
		for(j=0;j<JoiSrvHeight;j++)
			if(PBuf[i+j*JoiSrvWidth].R>0X80)//透明
				Pjoisrv[i+j*JoiSrvWidth].A=0XFF;//设置透明
	PBuf=(COLOR*)GetImageBuffer(&ScrollNot);
	for(i=0;i<ScrollWidth;i++)
		for(j=0;j<ScrollHeight;j++)
			if(PBuf[i+j*ScrollWidth].R>0X80)//透明
				Pscroll[i+j*ScrollWidth].A=0XFF;//设置透明
}