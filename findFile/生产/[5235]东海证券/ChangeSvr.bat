@echo off
if exist "%~dp0\sstsyscfg\otc.ini.101" goto svr100
if exist "%~dp0\sstsyscfg\otc.ini.100" goto svr101
goto end

:svr100
echo .
echo ��ǰOTC������Ϊ 100���Ƿ��л���101
set /p sercha=�Ƿ�Ҫ�л�������(y/n):
if %sercha%=="n" (goto end)
ren %~dp0\sstsyscfg\otc.ini otc.ini.100
ren %~dp0\sstsyscfg\otc.ini.101 otc.ini
goto end

:svr101
echo .
echo ��ǰOTC������Ϊ 101���Ƿ��л���100
set /p sercha=�Ƿ�Ҫ�л�������(y/n):
if %sercha%==n goto end 
ren %~dp0\sstsyscfg\otc.ini otc.ini.101
ren %~dp0\sstsyscfg\otc.ini.100 otc.ini
goto end

:end
echo �������л����
pause
