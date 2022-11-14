@echo off
cd src
gcc -o app.exe ccoly.c lexer/lexer.c
app.exe ./input.coly
cd ..