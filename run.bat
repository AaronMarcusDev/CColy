@echo off
cd src
gcc -o app.exe ccoly.c lexer/lexer.c ../lib/vc_vector/vc_vector.c
app.exe ./input.coly
cd ..