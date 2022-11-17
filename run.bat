@echo off
cd src
gcc -o app.exe ccoly.c ../lib/vc_vector/vc_vector.c lexer/lexer.c parser/parser.c compiler/compiler.c
app.exe ./input.coly
cd ..