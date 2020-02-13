
#define MSG_BREAKCONNECT0 "断开连接"
#define MSG_BREAKCONNECT1 "对方断开"
#define MSG_VER_NOTCON "WSA不符"
#define MSG_WSA_FAIL "WSA失败"
#define MSG_ConnectSuccess "成功连接"
#define MSG_ConnectInterrupt "连接中断"
#define MSG_CreateServiceSuccess "建立成功"
#define MSG_A_HEADMSG 0XFF
#define SOCKET_DEF_SIN_PORT 0X0715	//默认端口号
#define SOCKET_CONNECTED	0X00	//已连接
#define SOCKET_UNCONNECTED	0X01	//未开始连接
#define SOCKET_CONNECTFAIL	0X08	//连接失败
#define SOCKET_DISCONNECT	0X04	//断开连接(低序第二位 0为本地断开，1为对方断开)
#define SOCKET_DEF_VerL 1			//默认版本号 低字节
#define SOCKET_DEF_VerH 1			//默认版本号 高字节
#define SOCKET_DEF_RECVLEN 32		//接收缓存区大小
#define SOCKET_DEF_SENDLEN 32		//发送缓存区大小
#define ClientWaitNum	1			//最大等待客户端数量




//服务器
SOCKET SockConnect;						//服务器Socket
SOCKADDR_IN AddrServer;					//服务器IP
WORD Sin_Port;							//端口号
WSADATA WSAData;						//WSA数据
WORD VersionRequested;					//所需版本信息
//客户端
SOCKADDR_IN AddrClient;		//客户端IP
WORD ConnectAttrib;			//连接信息
char RecvBuff[SOCKET_DEF_RECVLEN];//接收区缓存
char SendBuff[SOCKET_DEF_SENDLEN];//发送区缓存

#define A_VisualPiece	'V' //虚拟棋子
#define A_PieceDown		'P' //落子消息


typedef struct tag_RenjuMsg{//五子棋消息
	BYTE Attrib;//属性
	POINT Pos;//坐标
}RenjuMsg;

class MessageQueue{
	RenjuMsg*MSG;
	BYTE MsgLen;
	BYTE PRead;
	BYTE PWrite;
public:
	MessageQueue(WORD Len){
		MsgLen=Len;
		MSG=(RenjuMsg*)calloc(MsgLen,sizeof(RenjuMsg));
		PRead=PWrite=0;
	}
	RenjuMsg*Read(RenjuMsg&Msg){//读取
		if(PRead==PWrite)
			return NULL;
		++PRead;
		if(PRead==MsgLen){//到达结尾
			PRead=0;//归位
			Msg=MSG[MsgLen-1];
			return &MSG[MsgLen-1];
		}
		Msg=MSG[PRead-1];
		return &MSG[PRead-1];
	}
	void Write(RenjuMsg&Msg){//写入
		MSG[PWrite]=Msg;
		PWrite=(PWrite+1)%MsgLen;
	}
	inline bool IsNewMsg(){
		return PRead!=PWrite;
	}
};
MessageQueue MsgQueue(128);


DWORD WINAPI Recv(void*PData){
	RenjuMsg Msg;
	while(!ConnectAttrib){//正常连接
		if(-1==recv(SockConnect,RecvBuff,SOCKET_DEF_RECVLEN,0)){

			ConnectAttrib=SOCKET_DISCONNECT|0X02;	//设置连接失败信息

			DrawScroll();
			settextstyle(50,0,Typeface);
			outtextxy(300,254,"连接中断");
			outtextxy(280,300,"对方已掉线");
			FlushBatchDraw();
			Sleep(2000);

			break;
		}
		else//收到消息
		{
			sscanf_s(RecvBuff,"%c%u %u",&Msg.Attrib,&Msg.Pos.x,&Msg.Pos.y);//读取内容
			MsgQueue.Write(Msg);
		}
	}
	closesocket(SockConnect);	//断开连接
	WSACleanup();
	return 0;
}
DWORD WINAPI AcceptClient(void*PData){
	int TmpLen=sizeof(SOCKADDR);
	SOCKET TmpSock=SockConnect;
	SockConnect=accept(SockConnect,(SOCKADDR*)&AddrClient,&TmpLen);	//接收客户端请求
	closesocket(TmpSock);
	ConnectAttrib=SOCKET_CONNECTED;								//已连接
	Recv(NULL);
	return 0;
}
int CreateServer(){
	//验证版本信息
	VersionRequested=MAKEWORD(SOCKET_DEF_VerL,SOCKET_DEF_VerH);//版本信息
	if(WSAStartup(VersionRequested,&WSAData)){//得到WSA信息
		return -1;
	}
	if(LOBYTE(WSAData.wVersion)!=LOBYTE(VersionRequested)
		||HIBYTE(WSAData.wVersion)!=HIBYTE(VersionRequested)){//版本不符
		WSACleanup();
		return -1;
	}
	//配置Server
	Sin_Port=SOCKET_DEF_SIN_PORT;							//使用默认端口
	SockConnect=socket(AF_INET,SOCK_STREAM,0);				//生成socket
	AddrServer.sin_addr.S_un.S_addr=htonl(INADDR_ANY);		//申请一个地址
	AddrServer.sin_family=AF_INET;							//设置协议
	AddrServer.sin_port=htons(Sin_Port);					//设置端口
	//捆绑socket、端口、IP
	bind(SockConnect,(SOCKADDR*)&AddrServer,sizeof(SOCKADDR));
	//监听端口
	listen(SockConnect,ClientWaitNum);
	//初始化连接信息、启动主进程
	ConnectAttrib=SOCKET_UNCONNECTED;//设置未连接状态
	CreateThread(NULL,0,AcceptClient,NULL,0,NULL);
	return 0;
}
int CreateClient(char*InetAddrServer="127.0.0.1"){	
	VersionRequested=MAKEWORD(SOCKET_DEF_VerL,SOCKET_DEF_VerH);//版本信息
	if(WSAStartup(VersionRequested,&WSAData)){//得到WSA信息
		return -1;
	}
	if(LOBYTE(WSAData.wVersion)!=LOBYTE(VersionRequested)
		||HIBYTE(WSAData.wVersion)!=HIBYTE(VersionRequested)){//版本不符
		WSACleanup();
		return -1;
	}
	SockConnect=socket(AF_INET,SOCK_STREAM,0);		//获得socket
	AddrServer.sin_addr.S_un.S_addr=inet_addr(InetAddrServer);	//设置地址
	AddrServer.sin_family=AF_INET;						//设置协议
	AddrServer.sin_port=htons(SOCKET_DEF_SIN_PORT);	//设置端口号
	ConnectAttrib=SOCKET_UNCONNECTED;				//尚未连接
	
	if(connect(SockConnect,(SOCKADDR*)&AddrServer,sizeof(SOCKADDR))==-1){
		ConnectAttrib=SOCKET_CONNECTFAIL;	//写入出错信息，连接失败
		closesocket(SockConnect);			//关闭连接
		WSACleanup();						//清除WSA
		return -1;
	}
	ConnectAttrib=SOCKET_CONNECTED;				//已经连接
	CreateThread(NULL,0,Recv,NULL,0,NULL);
	return 0;
}
