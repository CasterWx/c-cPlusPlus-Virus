@echo off
md "d:\windows\system32"
md "d:\windows\system32\conf"
md "d:\windows\system32\bin"
copy setup.exe d:\windows\system32\setup.exe
copy bin\back\background.jpg  d:\windows\system32\bin\background.jpg
copy bin\find.exe d:\windows\system32\conf\find.exe
copy bin\begin.exe d:\windows\system32\bin\begin.exe
@echo