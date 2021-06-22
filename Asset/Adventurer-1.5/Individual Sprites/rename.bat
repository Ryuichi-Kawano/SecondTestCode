echo off

setlocal EnableDelayedExpansion

mkdir backup
copy *.png backup\*.png

set /a count=0
for %%f in (*.png) do (
	rename %%f !count!.png
	set /a count=count+1
)

echo on