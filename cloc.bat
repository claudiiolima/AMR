@ECHO OFF

SET SCRIPT_PATH=%~dp0
CD %SCRIPT_PATH%

CALL scc --cocomo-project-type organic --ci .\Patterns\  > scc.txt