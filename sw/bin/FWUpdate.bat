#set PYTHON3DIR=C:\Users\andre\AppData\Local\Arduino15\packages\esp8266\tools\python3\3.7.2-post1/python3
set PYTHON3DIR=python
set COMPORT=COM3
%PYTHON3DIR% upload.py --chip esp8266 --port %COMPORT% --baud 921600 --before default_reset --after hard_reset write_flash 0x0 temperaturReader.ino.bin 
