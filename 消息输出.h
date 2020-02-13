void PutMsg(char*Msg){
	DrawSign();
	settextcolor(0X000000);
	settextstyle(30,0,Typeface);
	outtextxy(MsgX,MsgY,Msg);
	if(AutoFlushBatchDraw)
		FlushBatchDraw();//Ë¢ÐÂ
}