echo off
#升级后执行
echo set WshShell=WScript.CreateObject("WScript.Shell")   >ico.vbs
echo strDesktop=WshShell.SpecialFolders("Desktop")  >>ico.vbs
echo set oShellLink=WshShell.CreateShortcut(strDesktop ^& "\QWin期权策略交易系统（仿真）.lnk")  >>ico.vbs
echo oShellLink.TargetPath="%~dp0qymain.exe"  >>ico.vbs
echo oShellLink.WindowStyle=1  >>ico.vbs
echo oShellLink.IconLocation="%~dp0Res\MockDemo.ico,0"  >>ico.vbs
echo oShellLink.Description="%~dp0"  >>ico.vbs
echo oShellLink.WorkingDirectory=strDesktop  >>ico.vbs
echo oShellLink.Save  >>ico.vbs

echo destPath = WshShell.SpecialFolders("StartMenu") >>ico.vbs
echo set dpShellLink=WshShell.CreateShortcut(destPath ^& "\Programs\QWin期权策略交易系统（仿真）\QWin期权策略交易系统（仿真）.lnk")  >>ico.vbs
echo dpShellLink.TargetPath="%~dp0qymain.exe"  >>ico.vbs
echo dpShellLink.WindowStyle=1  >>ico.vbs
echo dpShellLink.IconLocation="%~dp0Res\MockDemo.ico,0"  >>ico.vbs
echo dpShellLink.Description="%~dp0"  >>ico.vbs
echo dpShellLink.WorkingDirectory=destPath  >>ico.vbs
echo dpShellLink.Save  >>ico.vbs

cscript ico.vbs

del ico.vbs

@echo echo OFF >clear.bat
echo echo . >>clear.bat
echo echo QWin 升级中，请稍后... >>clear.bat
echo ping -n 6 127.0.0.1 ^>nul >>clear.bat
echo taskkill /IM QlUpdate.exe >>clear.bat
echo taskkill /IM QWin.exe >>clear.bat
echo ren qlupdate.exe qlupdate.exe.del >>clear.bat
echo ren QWin.exe QWin.exe.del >>clear.bat
echo start QYMain.exe >>clear.bat
echo del clear.bat>>clear.bat

clear.bat

