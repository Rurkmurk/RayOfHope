@echo off

rem ��� SCL �����

set output=atom.scl

rem ���������, ������� ������������ ��� ��������
rem 32 �������, ����������� �����

set title="          ATOM FOR PEACE"

rem ������ �����������, ������ ����� �������
rem � ��������� ��� ���������� �� ������������� ������������
rem ��������������� � ����� resources.h
rem ��������� ����� ����� ������ ���� ������������

set palette.0=res\tile_snow.bmp

rem ������ �����������, ������ ����� �������

set image.0=res\tile_snow.bmp
set image.1=res\back_snow.bmp
set image.2=res\tile_hud.bmp
set image.4=res\font.bmp

rem �������

set sprite.0=res\player.bmp
set sprite.1=res\shot.bmp
set sprite.2=res\b_slime.bmp
set sprite.3=res\s_slime.bmp
set sprite.4=res\owl.bmp
set sprite.5=res\water.bmp
set sprite.6=res\stalact.bmp
set sprite.7=res\ice_spike.bmp

rem ����� �������� ��������, ���� �����
rem �� ����� ���� ������ ����

set soundfx=

rem ������, ������ ����� ������

set music.0=

rem ������

set sample.0=

call ..\evosdk\_compile.bat

call ..\evosdk\trdtool.exe + %output% Level\gfxlev_1.dat Level\maplev_1.dat

@if %error% ==0 ..\evosdk\tools\unreal_evo\emullvd %output%