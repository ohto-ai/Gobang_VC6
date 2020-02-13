
BYTE Check(BYTE x,BYTE y){//检测胜利
	BYTE Player=Map[x][y];
	if(!Player)//无子
		return 0;
	BYTE Count;
	BYTE i;
	Count=1;//计数器复位
	//左上右下
	for(i=1;x-i>=0&&y-i>=0;i++){
		if(Map[x-i][y-i]==Player)
			++Count;
		else break;
	}
	for(i=1;x+i<MAP_X&&y+i<MAP_Y;i++){
		if(Map[x+i][y+i]==Player)
			++Count;
		else break;
	}
	if(Count>=5)
		return Player;//返回胜利者
	Count=1;//计数器复位
	//左下右上
	for(i=1;x-i>=0&&y+i<MAP_Y;i++){
		if(Map[x-i][y+i]==Player)
			++Count;
		else break;
	}
	for(i=1;x+i<MAP_X&&y-i>=0;i++){
		if(Map[x+i][y-i]==Player)
			++Count;
		else break;
	}
	if(Count>=5)
		return Player;//返回胜利者
	Count=1;//计数器复位
	//上下
	for(i=1;y-i>=0;i++){
		if(Map[x][y-i]==Player)
			++Count;
		else break;
	}
	for(i=1;y+i<MAP_Y-1;i++){
		if(Map[x][y+i]==Player)
			++Count;
		else break;
	}
	if(Count>=5)
		return Player;//返回胜利者
	Count=1;//计数器复位
	//左右
	for(i=1;x-i>=0;i++){
		if(Map[x-i][y]==Player)
			++Count;
		else break;
	}
	for(i=1;x+i<MAP_X-1;i++){
		if(Map[x+i][y]==Player)
			++Count;
		else break;
	}
	if(Count>=5)
		return Player;//返回胜利者
	return 0;

}