@echo off
@title "���������������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)"
echo *****************************************************************************
echo "		��ɾ���ļ� E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)"
echo "		���д���ļ��������Ƶ� E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)"
echo "		ȷ�����ڻ��������м���winrar��·����������ɺ���Զ�ѹ���ļ�,����(%Date:~0,4%%Date:~5,2%%Date:~8,2%).rar"
echo "10���ʼִ��,�����뼰ʱ�ر����ļ�......"
echo "10���ʼִ��,�����뼰ʱ�ر����ļ�......"
echo *****************************************************************************

echo *****************************************************************************
echo "	ɾ��Ŀ¼�Լ�ѹ����"
echo 	 "��ɾ��Ŀ¼   E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\"
echo 	 "��ɾ��ѹ���� E:\����(%Date:~0,4%%Date:~5,2%%Date:~8,2%).rar"
echo *****************************************************************************
ping 127.0.0.1 -n 10 > nul
echo "		����Ŀ¼"
mkdir "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\log\"
mkdir "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\update\"
mkdir "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\hook_log\"
echo *****************************************************************************
ping 127.0.0.1 -n 10 > nul

echo "		��ʼ������Դ�ļ�"
echo *****************************************************************************
ping 127.0.0.1 -n 5  > nul

copy data\local\zhCN\table\Nameban.xml "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\local\zhCN\table\Nameban.xml"

xcopy /S /Y /F /R data\config\quest\*.* "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\config\quest\"
xcopy /S /Y /F /R data\config\table\*.* "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\config\table\"
xcopy /S /Y /F /R data\scene\*.*	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\scene\"
xcopy /S /Y /F /R data\SceneObj\*.*	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\SceneObj\"
xcopy /S /Y /F /R data\model\*.bvh	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\model\"
xcopy /S /Y /F /R server_data\*.*	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\server_data\"
xcopy /S /Y /F /R server_script\*.*	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\server_script\"

echo "		��ʼ����DLL���ļ�"
echo *****************************************************************************
ping 127.0.0.1 -n 3 > nul

xcopy /S /Y /F /R release\*.dll  	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"

del /F /S /Q  "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\axclt.dll"
del /F /S /Q  "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\siGameMapEditor.dll"
del /F /S /Q  "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\QtGui4.dll"
del /F /S /Q  "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\QtCore4.dll"
del /F /S /Q  "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\siNavMapEditor.dll"
del /F /S /Q  "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\siInGamePainterUI.dll"
del /F /S /Q  "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\ColorManagement.dll"
del /F /S /Q  "E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\DrawingEx.dll"

echo "		��ʼ����ִ���ļ�(EXE)"
echo *****************************************************************************
ping 127.0.0.1 -n 3 > nul


xcopy release\bill.exe		"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siDBServer.exe	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siExchange.exe	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siGameServer.exe	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siGMServer.exe	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siLogin.exe	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"

start /MIN winrar a -r -m3 "E:\����(%Date:~0,4%%Date:~5,2%%Date:~8,2%).rar"	"E:\������(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\"

echo "��ȴ�ѹ����� && �����������"
SET /P UserInput=