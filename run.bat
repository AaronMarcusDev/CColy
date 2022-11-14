@echo off
cd src
gcc ccoly.c -o app.exe
app.exe ./input.coly
cd ..