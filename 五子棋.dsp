# Microsoft Developer Studio Project File - Name="五子棋" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=五子棋 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "五子棋.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "五子棋.mak" CFG="五子棋 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "五子棋 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "五子棋 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "五子棋 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "五子棋 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "五子棋 - Win32 Release"
# Name "五子棋 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\RES.RC
# End Source File
# Begin Source File

SOURCE=".\五子棋.cpp"
# End Source File
# Begin Source File

SOURCE=".\游戏过程.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DRAW.H
# End Source File
# Begin Source File

SOURCE="..\..\..\HEADFILE\EasyX++.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\HEADFILE\MemMng.h
# End Source File
# Begin Source File

SOURCE=".\SOCKET通信.H"
# End Source File
# Begin Source File

SOURCE=".\附加宏.h"
# End Source File
# Begin Source File

SOURCE=".\消息输出.h"
# End Source File
# Begin Source File

SOURCE=".\音乐.h"
# End Source File
# Begin Source File

SOURCE=".\游戏算法.h"
# End Source File
# Begin Source File

SOURCE=".\资源处理.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\20171227120046394_easyicon_net_128.ico
# End Source File
# Begin Source File

SOURCE=.\RES\BACKGROUND.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\BLACK.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\BLACK~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\Close.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\Close~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\CreatServerSign.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\CreatServerSign~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\GameStart0.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\GameStart0~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\GameStart1.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\GameStart1~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\ICON.ico
# End Source File
# Begin Source File

SOURCE=.\ICON1.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\JoinServerSign.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\JoinServerSign~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\MAin.cur
# End Source File
# Begin Source File

SOURCE=.\RES\MENU.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\MusicNote.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\MusicNote~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\Scroll.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\Scroll~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\SignBoard.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\SignBoard~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\StartBG.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\Switch_off.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\Switch_off~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\Switch_on.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\Switch_on~.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\WHITE.jpg
# End Source File
# Begin Source File

SOURCE=.\RES\WHITE~.jpg
# End Source File
# Begin Source File

SOURCE=".\RES\名片.jpg"
# End Source File
# Begin Source File

SOURCE=".\RES\名片~.jpg"
# End Source File
# Begin Source File

SOURCE=".\RES\棋盘.jpg"
# End Source File
# Begin Source File

SOURCE=".\RES\人物0.jpg"
# End Source File
# Begin Source File

SOURCE=".\RES\人物0~.jpg"
# End Source File
# Begin Source File

SOURCE=".\RES\人物1.jpg"
# End Source File
# Begin Source File

SOURCE=".\RES\人物1~.jpg"
# End Source File
# Begin Source File

SOURCE=".\RES\准星.cur"
# End Source File
# End Group
# Begin Source File

SOURCE=.\RES\BGM.mp3
# End Source File
# Begin Source File

SOURCE=.\RES\Button.wav
# End Source File
# Begin Source File

SOURCE=.\RES\Click.wav
# End Source File
# Begin Source File

SOURCE=.\RES\MainWin.wav
# End Source File
# Begin Source File

SOURCE=.\RES\On.wav
# End Source File
# Begin Source File

SOURCE=.\RES\PIECE0.wav
# End Source File
# Begin Source File

SOURCE=.\RES\PIECE1.wav
# End Source File
# Begin Source File

SOURCE=.\RES\PIECE2.wav
# End Source File
# Begin Source File

SOURCE=.\RES\Start.wav
# End Source File
# Begin Source File

SOURCE=.\RES\STARTMUSIC.mp3
# End Source File
# Begin Source File

SOURCE=".\RES\抖动.ani"
# End Source File
# End Target
# End Project
