
BYTE Check(BYTE x,BYTE y){//���ʤ��
	BYTE Player=Map[x][y];
	if(!Player)//����
		return 0;
	BYTE Count;
	BYTE i;
	Count=1;//��������λ
	//��������
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
		return Player;//����ʤ����
	Count=1;//��������λ
	//��������
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
		return Player;//����ʤ����
	Count=1;//��������λ
	//����
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
		return Player;//����ʤ����
	Count=1;//��������λ
	//����
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
		return Player;//����ʤ����
	return 0;

}