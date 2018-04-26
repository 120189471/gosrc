@echo off
if exist "%~dp0\sstsyscfg\otc.ini.101" goto svr100
if exist "%~dp0\sstsyscfg\otc.ini.100" goto svr101
goto end

:svr100
echo .
echo 当前OTC服务器为 100，是否切换到101
set /p sercha=是否要切换服务器(y/n):
if %sercha%=="n" (goto end)
ren %~dp0\sstsyscfg\otc.ini otc.ini.100
ren %~dp0\sstsyscfg\otc.ini.101 otc.ini
goto end

:svr101
echo .
echo 当前OTC服务器为 101，是否切换到100
set /p sercha=是否要切换服务器(y/n):
if %sercha%==n goto end 
ren %~dp0\sstsyscfg\otc.ini otc.ini.101
ren %~dp0\sstsyscfg\otc.ini.100 otc.ini
goto end

:end
echo 服务器切换完成
pause
