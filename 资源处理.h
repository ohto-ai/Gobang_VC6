void LoadResources(){//װ����Դ�ļ�
	loadimage(&Board,"IMAGE","BOARD",MapWidth,MapHeight);
	loadimage(&Piece[0],"IMAGE","BLACK",PieceSize,PieceSize);
	loadimage(&Piece[1],"IMAGE","WHITE",PieceSize,PieceSize);
	loadimage(&SignBoard,"IMAGE","SIGNBOARD",SignWidth,SignHeight);
	loadimage(&BackGround,"IMAGE","BACKGROUND",BackWidth,BackHeight);
	loadimage(&Switch[0],"IMAGE","SWITCH_OFF",SwitchWidth,SwitchHeight);
	loadimage(&Switch[1],"IMAGE","SWITCH_ON",SwitchWidth,SwitchHeight);
	loadimage(&MusicNote,"IMAGE","MUSICNOTE",MusicWidth,MusicHeight);
	loadimage(&Card,"IMAGE","��Ƭ",CardWidth,CardHeight);
	loadimage(&StartBG,"IMAGE","��ʼ����",StartBGWidth,StartBGHeight);
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
void InitResources(){//��ʼ����Դ�ļ�
	Pscreen   =(COLOR*)GetImageBuffer(NULL  );//��ȡ��Ļ�ڴ�
	Pboard    =(COLOR*)GetImageBuffer(&Board);//��������ڴ�
	Psign     =(COLOR*)GetImageBuffer(&SignBoard);//��ñ�ʶ���ڴ�
	Pblack    =(COLOR*)GetImageBuffer(&Piece[0]);//��ú����ڴ�
	Pwhite    =(COLOR*)GetImageBuffer(&Piece[1]);//��ð����ڴ�
	Pswitch[0]=(COLOR*)GetImageBuffer(&Switch[0]);//��ú����ڴ�
	Pswitch[1]=(COLOR*)GetImageBuffer(&Switch[1]);//��ð����ڴ�
	Pback     =(COLOR*)GetImageBuffer(&BackGround);//��ñ����ڴ�
	Pmusic    =(COLOR*)GetImageBuffer(&MusicNote);//��������ڴ�
	Pcard     =(COLOR*)GetImageBuffer(&Card);//�����Ƭ�ڴ�
	Pstart    =(COLOR*)GetImageBuffer(&StartBG);//��ÿ�ʼ�����ڴ�
	Pgame[0]  =(COLOR*)GetImageBuffer(&GameStart[0]);//��ÿ�ʼ��Ϸ��ť�ڴ�
	Pgame[1]  =(COLOR*)GetImageBuffer(&GameStart[1]);//��ÿ�ʼ��Ϸ��ť�ڴ�
	Pclose    =(COLOR*)GetImageBuffer(&Close);//��ùرհ�ť�ڴ�
	Pmenu     =(COLOR*)GetImageBuffer(&Menu);//��ò˵��ڴ�
	Pcharacter[0]=(COLOR*)GetImageBuffer(&Character[0]);//��������ڴ�
	Pcharacter[1]=(COLOR*)GetImageBuffer(&Character[1]);//��������ڴ�
	Pcresrv   =(COLOR*)GetImageBuffer(&CreateServerSign);//��ô����������ڴ�
	Pjoisrv   =(COLOR*)GetImageBuffer(&JoinServerSign);//��ü���������ڴ�
	Pscroll   =(COLOR*)GetImageBuffer(&Scroll);//��ò˵��ڴ�

	IMAGE PieceNot[2];//����
	IMAGE SignBoardNot;//����
	IMAGE SwitchNot[2];//����
	IMAGE MusicNoteNot;//����
	IMAGE CardNot;//����
	IMAGE GameStartNot[2];//����
	IMAGE CloseNot;//����
	IMAGE CharacterNot[2];//����
	IMAGE CreateServerSignNot;//����
	IMAGE JoinServerSignNot;//����
	IMAGE ScrollNot;//����
	loadimage(&PieceNot[0],"IMAGE","BLACK~",PieceSize,PieceSize);
	loadimage(&PieceNot[1],"IMAGE","WHITE~",PieceSize,PieceSize);
	loadimage(&SwitchNot[0],"IMAGE","SWITCH_OFF~",SwitchWidth,SwitchHeight);
	loadimage(&SwitchNot[1],"IMAGE","SWITCH_ON~",SwitchWidth,SwitchHeight);
	loadimage(&SignBoardNot,"IMAGE","SIGNBOARD~",SignWidth,SignHeight);
	loadimage(&MusicNoteNot,"IMAGE","MUSICNOTE~",MusicWidth,MusicHeight);
	loadimage(&CardNot,"IMAGE","��Ƭ~",CardWidth,CardHeight);
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
			if(PBuf[i+j*PieceSize].R>0X80)//͸��
				Pblack[i+j*PieceSize].A=0XFF;//����͸��
	PBuf=(COLOR*)GetImageBuffer(&PieceNot[1]);
	for(i=0;i<PieceSize;i++)
		for(j=0;j<PieceSize;j++)
			if(PBuf[i+j*PieceSize].R>0X80)//͸��
				Pwhite[i+j*PieceSize].A=0XFF;//����͸��

	PBuf=(COLOR*)GetImageBuffer(&SwitchNot[0]);
	for(i=0;i<SwitchWidth;i++)
		for(j=0;j<SwitchHeight;j++)
			if(PBuf[i+j*SwitchWidth].R>0X80)//͸��
				Pswitch[0][i+j*SwitchWidth].A=0XFF;//����͸��
	PBuf=(COLOR*)GetImageBuffer(&SwitchNot[1]);
	for(i=0;i<SwitchWidth;i++)
		for(j=0;j<SwitchHeight;j++)
			if(PBuf[i+j*SwitchWidth].R>0X80)//͸��
				Pswitch[1][i+j*SwitchWidth].A=0XFF;//����͸��

	PBuf=(COLOR*)GetImageBuffer(&SignBoardNot);
	for(i=0;i<SignWidth;i++)
		for(j=0;j<SignHeight;j++)
			if(PBuf[i+j*SignWidth].R>0X80)//͸��
				Psign[i+j*SignWidth].A=0XFF;//����͸��			
	PBuf=(COLOR*)GetImageBuffer(&MusicNoteNot);
	for(i=0;i<MusicWidth;i++)
		for(j=0;j<MusicHeight;j++)
			if(PBuf[i+j*MusicWidth].R>0X80)//͸��
				Pmusic[i+j*MusicWidth].A=0XFF;//����͸��
	PBuf=(COLOR*)GetImageBuffer(&CardNot);
	for(i=0;i<CardWidth;i++)
		for(j=0;j<CardHeight;j++)
			if(PBuf[i+j*CardWidth].R>0X80)//͸��
				Pcard[i+j*CardWidth].A=0XFF;//����͸��
	PBuf=(COLOR*)GetImageBuffer(&GameStartNot[0]);
	for(i=0;i<GameStartWidth;i++)
		for(j=0;j<GameStartHeight;j++)
			if(PBuf[i+j*GameStartWidth].R>0X80)//͸��
				Pgame[0][i+j*GameStartWidth].A=0XFF;//����͸��
	PBuf=(COLOR*)GetImageBuffer(&GameStartNot[1]);
	for(i=0;i<GameStartWidth;i++)
		for(j=0;j<GameStartHeight;j++)
			if(PBuf[i+j*GameStartWidth].R>0X80)//͸��
				Pgame[1][i+j*GameStartWidth].A=0XFF;//����͸��
	PBuf=(COLOR*)GetImageBuffer(&CloseNot);
	for(i=0;i<CloseWidth;i++)
		for(j=0;j<CloseHeight;j++)
			if(PBuf[i+j*CloseWidth].R>0X80)//͸��
				Pclose[i+j*CloseWidth].A=0XFF;//����͸��
	PBuf=(COLOR*)GetImageBuffer(&CharacterNot[0]);
	for(i=0;i<CharacterWidth[0];i++)
		for(j=0;j<CharacterHeight[0];j++)
			if(PBuf[i+j*CharacterWidth[0]].R>0X80)//͸��
				Pcharacter[0][i+j*CharacterWidth[0]].A=0XFF;//����͸��
	PBuf=(COLOR*)GetImageBuffer(&CharacterNot[1]);
	for(i=0;i<CharacterWidth[1];i++)
		for(j=0;j<CharacterHeight[1];j++)
			if(PBuf[i+j*CharacterWidth[1]].R>0X80)//͸��
				Pcharacter[1][i+j*CharacterWidth[1]].A=0XFF;//����͸��


	PBuf=(COLOR*)GetImageBuffer(&CreateServerSignNot);
	for(i=0;i<CreSrvWidth;i++)
		for(j=0;j<CreSrvHeight;j++)
			if(PBuf[i+j*CreSrvWidth].R>0X80)//͸��
				Pcresrv[i+j*CreSrvWidth].A=0XFF;//����͸��

	PBuf=(COLOR*)GetImageBuffer(&JoinServerSignNot);
	for(i=0;i<JoiSrvWidth;i++)
		for(j=0;j<JoiSrvHeight;j++)
			if(PBuf[i+j*JoiSrvWidth].R>0X80)//͸��
				Pjoisrv[i+j*JoiSrvWidth].A=0XFF;//����͸��
	PBuf=(COLOR*)GetImageBuffer(&ScrollNot);
	for(i=0;i<ScrollWidth;i++)
		for(j=0;j<ScrollHeight;j++)
			if(PBuf[i+j*ScrollWidth].R>0X80)//͸��
				Pscroll[i+j*ScrollWidth].A=0XFF;//����͸��
}