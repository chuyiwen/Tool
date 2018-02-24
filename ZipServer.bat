@echo off
@title "服务器打包诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)"
echo *****************************************************************************
echo "		将删除文件 E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)"
echo "		所有打包文件将被复制到 E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)"
echo "		确保能在环境变量中加入winrar的路径，复制完成后会自动压缩文件,诸神(%Date:~0,4%%Date:~5,2%%Date:~8,2%).rar"
echo "10秒后开始执行,否则请及时关闭批文件......"
echo "10秒后开始执行,否则请及时关闭批文件......"
echo *****************************************************************************

echo *****************************************************************************
echo "	删除目录以及压缩包"
echo 	 "请删除目录   E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\"
echo 	 "请删除压缩包 E:\诸神(%Date:~0,4%%Date:~5,2%%Date:~8,2%).rar"
echo *****************************************************************************
ping 127.0.0.1 -n 10 > nul
echo "		生成目录"
mkdir "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\log\"
mkdir "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\update\"
mkdir "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\hook_log\"
echo *****************************************************************************
ping 127.0.0.1 -n 10 > nul

echo "		开始复制资源文件"
echo *****************************************************************************
ping 127.0.0.1 -n 5  > nul

copy data\local\zhCN\table\Nameban.xml "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\local\zhCN\table\Nameban.xml"

xcopy /S /Y /F /R data\config\quest\*.* "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\config\quest\"
xcopy /S /Y /F /R data\config\table\*.* "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\config\table\"
xcopy /S /Y /F /R data\scene\*.*	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\scene\"
xcopy /S /Y /F /R data\SceneObj\*.*	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\SceneObj\"
xcopy /S /Y /F /R data\model\*.bvh	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\data\model\"
xcopy /S /Y /F /R server_data\*.*	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\server_data\"
xcopy /S /Y /F /R server_script\*.*	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\server_script\"

echo "		开始复制DLL件文件"
echo *****************************************************************************
ping 127.0.0.1 -n 3 > nul

xcopy /S /Y /F /R release\*.dll  	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"

del /F /S /Q  "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\axclt.dll"
del /F /S /Q  "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\siGameMapEditor.dll"
del /F /S /Q  "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\QtGui4.dll"
del /F /S /Q  "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\QtCore4.dll"
del /F /S /Q  "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\siNavMapEditor.dll"
del /F /S /Q  "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\siInGamePainterUI.dll"
del /F /S /Q  "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\ColorManagement.dll"
del /F /S /Q  "E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\DrawingEx.dll"

echo "		开始复制执行文件(EXE)"
echo *****************************************************************************
ping 127.0.0.1 -n 3 > nul


xcopy release\bill.exe		"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siDBServer.exe	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siExchange.exe	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siGameServer.exe	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siGMServer.exe	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"
xcopy release\siLogin.exe	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\release\"

start /MIN winrar a -r -m3 "E:\诸神(%Date:~0,4%%Date:~5,2%%Date:~8,2%).rar"	"E:\诸神打包(%Date:~0,4%%Date:~5,2%%Date:~8,2%)\"

echo "请等待压缩完成 && 按任意键结束"
SET /P UserInput=