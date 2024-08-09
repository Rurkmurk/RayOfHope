@echo off

rem ��� SCL �����

set output=ray.scl

rem ���������, ������� ������������ ��� ��������
rem 32 �������, ����������� �����

set title="          Ray of Hope"

rem ������ �����������, ������ ����� �������
rem � ��������� ��� ���������� �� ������������� ������������
rem ��������������� � ����� resources.h
rem ��������� ����� ����� ������ ���� ������������

set palette.0=res\tile_snow.bmp
set palette.1=res\tile_mine.bmp
set palette.2=res\rc.bmp
set palette.3=res\sun.bmp

rem ������ �����������, ������ ����� �������

set image.0=res\tile_snow.bmp
set image.1=res\back_snow.bmp
set image.2=res\tile_mine.bmp
set image.3=res\back_mine.bmp
set image.4=res\tile_hud.bmp
set image.5=res\img_hud.bmp
set image.6=res\font.bmp
set image.7=res\chapter_1.bmp
set image.8=res\chapter_2.bmp
set image.9=res\sun.bmp
set image.10=res\rc.bmp

rem �������

set sprite.0=res\player.bmp
set sprite.1=res\shot.bmp
set sprite.2=res\b_slime.bmp
set sprite.3=res\s_slime.bmp
set sprite.4=res\owl.bmp
set sprite.5=res\stalact.bmp
set sprite.6=res\ice_spike.bmp
set sprite.7=res\block.bmp
set sprite.8=res\snow_jump.bmp
set sprite.9=res\water.bmp
set sprite.10=res\light_1.bmp
set sprite.11=res\light_2.bmp
set sprite.12=res\mine_jump.bmp
set sprite.13=res\angry_plant_r.bmp
set sprite.14=res\angry_plant_l.bmp


rem ����� �������� ��������, ���� �����
rem �� ����� ���� ������ ����

set soundfx=res\sound.afb

rem ������, ������ ����� ������

set music.0=

rem ������

set sample.0=

call ..\evosdk\_compile.bat

call ..\evosdk\trdtool.exe + %output% Level\lev1_gfx.dat Level\lev1_map.dat Level\lev2_gfx.dat Level\lev2_map.dat

@if %error% ==0 ..\evosdk\tools\unreal_evo\emullvd %output%