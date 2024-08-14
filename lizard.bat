@ECHO OFF

SET SCRIPT_PATH=%~dp0
CD %SCRIPT_PATH%

CALL py -m lizard .\Middleware\ > lizard.txt