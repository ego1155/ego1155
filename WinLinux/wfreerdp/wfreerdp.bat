@echo off
wfreerdp.exe /u:user2 /p:s@123456 /w:800 /h:600 /v:127.0.0.1:5000 /t:127.0.0.1:5000 /cert:tofu +clipboard /sound +themes +wallpaper +compression /bpp:32 /rfx /auto-reconnect
@echo on