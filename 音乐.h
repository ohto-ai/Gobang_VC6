bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType,WORD wResID)
{
	 // ��Դ��С  
    DWORD   dwWrite=0;
    // �����ļ�  
    HANDLE  hFile = CreateFile(strDstFile, GENERIC_WRITE,FILE_SHARE_WRITE,NULL,  
                                CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);  
    if ( hFile == INVALID_HANDLE_VALUE )  
        return false; 
  
    // ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С  
    HRSRC   hrsc =  FindResource(NULL, MAKEINTRESOURCE(wResID), strResType);  
    HGLOBAL hG = LoadResource(NULL, hrsc);  
    DWORD   dwSize = SizeofResource( NULL,  hrsc);  
  
    // д���ļ�  
    WriteFile(hFile,hG,dwSize,&dwWrite,NULL);     
    CloseHandle( hFile );  
    return true;  
}
class Music{;
	TCHAR Tmp[_MAX_PATH];				//��ʱ�ļ�·��
	TCHAR Cmd[_MAX_PATH];				//ָ��
	TCHAR CMDPlay[_MAX_PATH];
	TCHAR CMDPause[_MAX_PATH];
	TCHAR CMDClose[_MAX_PATH];
	TCHAR CMDStop[_MAX_PATH];
public:
	Music(WORD Res=BGM,char*Name="BGM",char*TmpFileName="Tmp_Music.mp3"){
		::GetTempPath(_MAX_PATH,Tmp);		//��ȡ��ʱ�ļ�·��
		strcat_s(Tmp, _T(TmpFileName));		//�ϳ�����·��
		ExtractResource(Tmp, _T("WAVE"),Res);//�ͷ�������Դ�ļ�
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