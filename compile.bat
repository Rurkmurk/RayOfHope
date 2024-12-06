@echo off

rem имя SCL файла

set output=ray.scl

rem сообщение, которое отображается при загрузке
rem 32 символа, стандартный шрифт

set title="             LOADING"

rem список изображений, откуда брать палитры
rem в программе они вызываются по автоматически генерируемым
rem идентификаторам в файле resources.h
rem нумерация после точки должна быть возрастающей

set palette.0=res\tile_snow.bmp
set palette.1=res\tile_mine.bmp
set palette.2=res\tile_lab.bmp
set palette.3=res\sun.bmp

rem список изображений, откуда брать графику

set image.0=res\tile_snow.bmp
set image.1=res\back_snow.bmp
set image.2=res\tile_mine.bmp
set image.3=res\back_mine.bmp
set image.4=res\tile_hud.bmp
set image.5=res\img_hud.bmp
set image.6=res\font.bmp
set image.7=res\chapter_1.bmp
set image.8=res\chapter_2.bmp
set image.9=res\chapter_3.bmp
set image.10=res\sun.bmp
set image.11=res\tile_lab.bmp
set image.12=res\back_lab.bmp
set image.13=res\win.bmp
set image.14=res\death.bmp
set image.15=res\virus.bmp
set image.16=res\mine.bmp
set image.17=res\snowmob.bmp
set image.18=res\back_menu.bmp

rem спрайты

set sprite.0=res\player.bmp
set sprite.1=res\shot.bmp
set sprite.2=res\b_slime.bmp
set sprite.3=res\s_slime.bmp
set sprite.4=res\owl.bmp
set sprite.5=res\stalact.bmp
set sprite.6=res\ice_spike.bmp
set sprite.7=res\block.bmp
set sprite.8=res\snow_jump.bmp
set sprite.9=res\water_snow.bmp
set sprite.10=res\light_1_mine.bmp
set sprite.11=res\light_2_mine.bmp
set sprite.12=res\mine_jump.bmp
set sprite.13=res\angry_plant_r.bmp
set sprite.14=res\angry_plant_l.bmp
set sprite.15=res\angry_plant.bmp
set sprite.16=res\coal.bmp
set sprite.17=res\bat.bmp
set sprite.18=res\spider.bmp
set sprite.19=res\zombi.bmp
set sprite.20=res\colba.bmp
set sprite.21=res\s_slime_lab.bmp
set sprite.22=res\light_1_lab.bmp
set sprite.23=res\light_2_lab.bmp
set sprite.24=res\fan.bmp
set sprite.25=res\acid.bmp
set sprite.26=res\zombi_hat.bmp
set sprite.27=res\light_1_snow.bmp
set sprite.28=res\light_2_snow.bmp
set sprite.29=res\water_mine.bmp


rem набор звуковых эффектов, если нужен
rem он может быть только один

set soundfx=res\sound.afb

rem музыка, нужное число треков

set music.0=res\menu.pt3
set music.1=res\level1.pt3

rem сэмплы

set sample.0=

call ..\evosdk\_compile.bat

call ..\evosdk\trdtool.exe + %output% Level\lev1_gfx.dat Level\lev1_map.dat Level\lev2_gfx.dat Level\lev2_map.dat Level\lev3_gfx.dat Level\lev3_map.dat

@if %error% ==0 ..\evosdk\tools\unreal_evo\emullvd %output%