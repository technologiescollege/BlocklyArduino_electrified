@echo off
break ON
rem fichiers BAT et fork créés par Sébastien CANET
SET currentpath=%~dp1
cd %currentpath%tools\python
cls
python.exe .\Lib\site-packages\pymata_aio\pymata_iot.py -l 5 -c no_client -comport COM26