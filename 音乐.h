bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType,WORD wResID)
{
	 // 资源大小  
    DWORD   dwWrite=0;
    // 创建文件  
    HANDLE  hFile = CreateFile(strDstFile, GENERIC_WRITE,FILE_SHARE_WRITE,NULL,  
                                CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);  
    if ( hFile == INVALID_HANDLE_VALUE )  
        return false; 
  
    // 查找资源文件中、加载资源到内存、得到资源大小  
    HRSRC   hrsc =  FindResource(NULL, MAKEINTRESOURCE(wResID), strResType);  
    HGLOBAL hG = LoadResource(NULL, hrsc);  
    DWORD   dwSize = SizeofResource( NULL,  hrsc);  
  
    // 写入文件  
    WriteFile(hFile,hG,dwSize,&dwWrite,NULL);     
    CloseHandle( hFile );  
    return true;  
}
class Music{;
	TCHAR Tmp[_MAX_PATH];				//临时文件路径
	TCHAR Cmd[_MAX_PATH];				//指令
	TCHAR CMDPlay[_MAX_PATH];
	TCHAR CMDPause[_MAX_PATH];
	TCHAR CMDClose[_MAX_PATH];
	TCHAR CMDStop[_MAX_PATH];
public:
	Music(WORD Res=BGM,char*Name="BGM",char*TmpFileName="Tmp_Music.mp3"){
		::GetTempPath(_MAX_PATH,Tmp);		//获取临时文件路径
		strcat_s(Tmp, _T(TmpFileName));		//合成完整路径
		ExtractResource(Tmp, _T("WAVE"),Res);//释放音乐资源文件
		sprintf_s(Cmd,"Open \"%s\" alias %s",Tmp,Name);
		sprintf_s(CMDPlay,"Play %s Repeat",Name);
		sprintf_s(CMDPause,"Pause %s",Name);
		sprintf_s(CMDClose,"Close %s",Name);
		sprintf_s(CMDStop,"Stop %s",Name);
		mciSendString(Cmd,NULL,0,NULL);
	}
	~Music(){
		mciSendString(CMDClose,NULL,0,NULL);
		DeleteFile(Tmp);
	}
	DWORD Play(){
		return mciSendString(CMDPlay,NULL,0,NULL);
	}
	DWORD Close(){
		return mciSendString(CMDClose,NULL,0,NULL);
	}
	DWORD Pause(){
		return mciSendString(CMDPause,NULL,0,NULL);
	}
	DWORD Stop(){
		return mciSendString(CMDStop,NULL,0,NULL);
	}

};