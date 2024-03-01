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

set palette.0=res\tile_snow.bmp

rem список изображений, откуда брать графику

set image.0=res\tile_snow.bmp
set image.1=res\back_snow.bmp
set image.2=res\tile_hud.bmp
set image.4=res\font.bmp

rem спрайты

set sprite.0=res\player.bmp
set sprite.1=res\shot.bmp
set sprite.2=res\b_slime.bmp
set sprite.3=res\s_slime.bmp
set sprite.4=res\owl.bmp
set sprite.5=res\water.bmp
set sprite.6=res\stalact.bmp
set sprite.7=res\ice_spike.bmp

rem набор звуковых эффектов, если нужен
rem он может быть только один

set soundfx=

rem музыка, нужное число треков

set music.0=

rem сэмплы

set sample.0=

call ..\evosdk\_compile.bat

call ..\evosdk\trdtool.exe + %output% Level\gfxlev_1.dat Level\maplev_1.dat

@if %error% ==0 ..\evosdk\tools\unreal_evo\emullvd %output%