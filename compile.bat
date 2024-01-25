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

set palette.0=res\palette0.bmp

rem ������ �����������, ������ ����� �������

set image.0=res\tile.bmp
set image.1=res\font.bmp


rem �������

set sprite.0=res\player.bmp
set sprite.1=res\shot.bmp
set sprite.2=res\b_slime.bmp
set sprite.3=res\s_slime.bmp

rem ����� �������� ��������, ���� �����
rem �� ����� ���� ������ ����

set soundfx=

rem ������, ������ ����� ������

set music.0=

rem ������

set sample.0=

call ..\evosdk\_compile.bat

call ..\evosdk\trdtool.exe + %output% Level\map00001.map

@if %error% ==0 ..\evosdk\tools\unreal_evo\emullvd %output%