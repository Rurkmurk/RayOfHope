@echo off

rem имя SCL файла

set output=atom.scl

rem сообщение, которое отображается при загрузке
rem 32 символа, стандартный шрифт

set title="          ATOM FOR PEACE"

rem список изображений, откуда брать палитры
rem в программе они вызываются по автоматически генерируемым
rem идентификаторам в файле resources.h
rem нумерация после точки должна быть возрастающей

set palette.0=res\palette0.bmp

rem список изображений, откуда брать графику

set image.0=res\tile.bmp
set image.1=res\font.bmp


rem спрайты

set sprite.0=res\player.bmp
set sprite.1=res\shot.bmp
set sprite.2=res\b_slime.bmp
set sprite.3=res\s_slime.bmp

rem набор звуковых эффектов, если нужен
rem он может быть только один

set soundfx=

rem музыка, нужное число треков

set music.0=

rem сэмплы

set sample.0=

call ..\evosdk\_compile.bat

call ..\evosdk\trdtool.exe + %output% Level\map00001.map

@if %error% ==0 ..\evosdk\tools\unreal_evo\emullvd %output%