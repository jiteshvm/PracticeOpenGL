@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86     
set compilerflags=/Od /Zi /EHsc /I include\ /MD
set linkerflags=/LIBPATH:lib\ /OUT:PracticeOpenGL.exe opengl32.lib glfw3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
cl.exe %compilerflags% src\main.cpp src\glad.c /link %linkerflags%