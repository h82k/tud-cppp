: Modify the following lines to suit your setup
set FILE=main.mhx
set FLASHLY_PATH=flashly\flashly.exe


%FLASHLY_PATH% -cpu MB96F348HSB -m:RTS- -r:DTR+ -Q:4 -E:DF0000 -E:FF0000 -nolog -newlog -msgok -P: %FILE%
