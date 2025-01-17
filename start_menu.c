#ifndef _START_MENU
#define _START_MENU

void menu_main();
void start_level();
void game_loop();

static u8 letter;

u8 read_key()
{
	static u8 keys[40];
	static u8 key;
	
	key=255;
	while (key==255)
	{
		keyboard(keys);
		if(keys[KEY_0]&KEY_PRESS) {key=KEY_0; letter='0';}
		if(keys[KEY_1]&KEY_PRESS) {key=KEY_1; letter='1';}
		if(keys[KEY_2]&KEY_PRESS) {key=KEY_2; letter='2';}
		if(keys[KEY_3]&KEY_PRESS) {key=KEY_3; letter='3';}
		if(keys[KEY_4]&KEY_PRESS) {key=KEY_4; letter='4';}
		if(keys[KEY_5]&KEY_PRESS) {key=KEY_5; letter='5';}
		if(keys[KEY_6]&KEY_PRESS) {key=KEY_6; letter='6';}
		if(keys[KEY_7]&KEY_PRESS) {key=KEY_7; letter='7';}
		if(keys[KEY_8]&KEY_PRESS) {key=KEY_8; letter='8';}
		if(keys[KEY_9]&KEY_PRESS) {key=KEY_9; letter='9';}
													 
		if(keys[KEY_A]&KEY_PRESS) {key=KEY_A; letter='A';}
		if(keys[KEY_B]&KEY_PRESS) {key=KEY_B; letter='B';}
		if(keys[KEY_C]&KEY_PRESS) {key=KEY_C; letter='C';}
		if(keys[KEY_D]&KEY_PRESS) {key=KEY_D; letter='D';}
		if(keys[KEY_E]&KEY_PRESS) {key=KEY_E; letter='E';}
		if(keys[KEY_F]&KEY_PRESS) {key=KEY_F; letter='F';}
		if(keys[KEY_G]&KEY_PRESS) {key=KEY_G; letter='G';}
		if(keys[KEY_H]&KEY_PRESS) {key=KEY_H; letter='H';}
		if(keys[KEY_I]&KEY_PRESS) {key=KEY_I; letter='I';}
		if(keys[KEY_J]&KEY_PRESS) {key=KEY_J; letter='J';}
		if(keys[KEY_K]&KEY_PRESS) {key=KEY_K; letter='K';}
		if(keys[KEY_L]&KEY_PRESS) {key=KEY_L; letter='L';}
		if(keys[KEY_M]&KEY_PRESS) {key=KEY_M; letter='M';}
		if(keys[KEY_N]&KEY_PRESS) {key=KEY_N; letter='N';}
		if(keys[KEY_O]&KEY_PRESS) {key=KEY_O; letter='O';}
		if(keys[KEY_P]&KEY_PRESS) {key=KEY_P; letter='P';}
		if(keys[KEY_Q]&KEY_PRESS) {key=KEY_Q; letter='Q';}
		if(keys[KEY_R]&KEY_PRESS) {key=KEY_R; letter='R';}
		if(keys[KEY_S]&KEY_PRESS) {key=KEY_S; letter='S';}
		if(keys[KEY_T]&KEY_PRESS) {key=KEY_T; letter='T';}
		if(keys[KEY_U]&KEY_PRESS) {key=KEY_U; letter='U';}
		if(keys[KEY_V]&KEY_PRESS) {key=KEY_V; letter='V';}
		if(keys[KEY_W]&KEY_PRESS) {key=KEY_W; letter='W';}
		if(keys[KEY_X]&KEY_PRESS) {key=KEY_X; letter='X';}
		if(keys[KEY_Y]&KEY_PRESS) {key=KEY_Y; letter='Y';}
		if(keys[KEY_Z]&KEY_PRESS) {key=KEY_Z; letter='Z';}

		if(keys[KEY_SPACE]&KEY_PRESS) {key=KEY_SPACE; letter='_';}
		//if(keys[KEY_ENTER]&KEY_PRESS) key=KEY_ENTER;
	}
	sfx_play(SFX_MENU,8);

	return key;
}

void bright_down()
{
	static i8 i;
	for (i=BRIGHT_MID;i>=BRIGHT_MIN;i--){
		pal_bright(i);
		delay(3);
	}
}

void bright_up()
{
	static i8 i;
	for (i=BRIGHT_MIN;i<=BRIGHT_MID;i++){
		pal_bright(i);
		delay(3);
	}
}

void win_screen()
{
	set_sprite(0,0,0,SPRITE_END);
	bright_down();
	pal_select(level_palett_default);
	clear_screen(0);
	draw_image(7,3,IMG_WIN);
	swap_screen();
	bright_up();
	read_key();
}

void death_screen()
{
	set_sprite(0,0,0,SPRITE_END);
	bright_down();
	pal_select(level_palett_default);
	clear_screen(0);
	draw_image(7,3,IMG_DEATH);
	swap_screen();
	bright_up();
	read_key();
}

void chapter()
{
	static u8 n;
	n=0;
	music_stop();
	pal_select(level_palett_default);
	clear_screen(0);
	switch (level){
	case 0:
	n=IMG_CHAPTER_1;
	break;
	case 1:
	n=IMG_CHAPTER_2;
	break;
	case 2:
	n=IMG_CHAPTER_3;
	break;
	}
	draw_image(10,6,n);
	swap_screen();
	bright_up();
	read_key();
	bright_down();
}



void redefine_keys()
{
	static u8 key_temp;
	static u8 redefine[]="��������";
	static u8 up[]="�����";
	static u8 down[]="����";
	static u8 right[]="������";
	static u8 left[]="�����";
	static u8 fire[]="�����";
	static u8 check[]="��� �����? Y/N";

	
	clear_screen(0);
	swap_screen();
	clear_screen(0);
	draw_image(0,0,IMG_BACK_MENU);
	output_string(15, 4, redefine);
	output_string(16, 7, up);
	swap_screen();
	key_up=read_key();
	draw_tile_key(23,7,letter-32);
	
	output_string(16, 9, down);
	swap_screen();
	do key_temp=read_key();
	while (key_temp==key_up);
	key_down=key_temp;
	draw_tile_key(23,9,letter-32);

	output_string(16, 11, right);
	swap_screen();
	do key_temp=read_key();
	while (key_temp==key_up||key_temp==key_down);
	key_right=key_temp;
	draw_tile_key(23,11,letter-32);

	output_string(16, 13, left);
	swap_screen();
	do key_temp=read_key();
	while (key_temp==key_up||key_temp==key_down||key_temp==key_right);
	key_left=key_temp;
	draw_tile_key(23,13,letter-32);

	output_string(16, 15, fire);
	swap_screen();
	do key_temp=read_key();
	while (key_temp==key_up||key_temp==key_down||key_temp==key_right||key_temp==key_left);
	key_fire=key_temp;
	draw_tile_key(23,15,letter-32);
	
	output_string(13, 17, check);
	swap_screen();
	if (read_key()!=KEY_Y) redefine_keys();
	menu_main();
}

void menu_control()
{
	static u8 control[]="1 ��������^ ^2 ������+������^ ^3 ������� ����";
	bright_down();
	clear_screen(0);
	draw_image(0,0,IMG_BACK_MENU);
	output_string(13, 9, control);
	swap_screen();
	bright_up();
	switch (read_key())
	{
		case KEY_1:
			control_type=0;
			sfx_play(SFX_MENU,8);
		break;
		case KEY_2:
			control_type=0;
			sfx_play(SFX_MENU,8);
		break;
		case KEY_3:
			control_type=1;
			sfx_play(SFX_MENU,8);
			redefine_keys();
		break;
		default:
			sfx_play(SFX_MENU,8);
			menu_control();
		break;
	}
	menu_main();
}

void info()
{
	static u8 info[]="  ���  �������^ ^��� ������� ����^ ^  ����� ������^ ^      2024";
	static u8 ver_atm[]="7 ��� ��� �����";
	static u8 ver_evo[]="14��� EVO �����";
	bright_down();
	clear_screen(0);
	draw_image(0,0,IMG_BACK_MENU);
	output_string(12, 8, info);
	switch (model)
	{
		case ATM:
			output_string(13, 16, ver_atm);
		break;
		case EVO:
			output_string(13, 16, ver_evo);
		break;
	}
	swap_screen();
	bright_up();
	read_key();
	sfx_play(SFX_MENU,8);
	menu_main();
}

void intro()
{
	static u8 text1[]=" � ���������� ��������� ������^�������� �����, �� ������^������ �������� ������� �����.^ ������� ���������� ����,^����� ��������, � ����� � ����.^ ����� ��������� �������� �^������� ��������, � �����^� �����.^ �������� ������� ��������.";
	
	static u8 text2[]=" ���� ��������, ��� � ���������^����������� ���-3 ���������������^������� ������ �����-������.^��� �� ������ �������� ����������.^����� � ������������ ���� �������.^����������� ������������� �^����������� ����� �� ��������^������.";
	
	static u8 text3[]=" ����� ���� ����������� � ���^���������.^ �� ���������� ������� �����������^������ � ����������������^����������� ����������.^���� �� �� ������, �� ����������,^� ������� ����� ����� �� �����.^ ��� - ���� ��������� �������.";
	
	bright_down();
	pal_select(2);
	clear_screen(0);
	output_string(5, 3, text1);
	draw_image(16,14,IMG_VIRUS);
	swap_screen();
	bright_up();
	read_key();
	
	bright_down();
	pal_select(0);
	clear_screen(0);
	output_string(4, 3, text2);
	draw_image(10,14,IMG_MINE);
	swap_screen();
	bright_up();
	read_key();
	
	bright_down();
	clear_screen(0);
	output_string(4, 3, text3);
	draw_image(10,14,IMG_SNOWMOB);
	swap_screen();
	bright_up();
	read_key();
	
	level=0;
	start_level();
	game_loop();
}

void menu_main()
{
	static u8 menu[]="1 ����^ ^2 ����������^ ^3 ����������";
	
	set_sprite(0,0,0,SPRITE_END);
	bright_down();
	pal_select(PAL_SUN);
	clear_screen(0);
	draw_image(0,0,IMG_BACK_MENU);
	output_string(14, 9, menu);
	swap_screen();
	bright_up();
	switch (read_key())
	{
		case KEY_1:
			sfx_play(SFX_MENU,8);
			music_stop();
			intro();
		break;
		case KEY_2:
			sfx_play(SFX_MENU,8);
			menu_control();
		break;
		case KEY_3:
			sfx_play(SFX_MENU,8);
			info();
		break;
		default:
			sfx_play(SFX_MENU,8);
			menu_main();
		break;
	}
}

void start_image()
{
	pal_select(PAL_SUN);
	pal_bright(BRIGHT_MIN);
	border (0);
	clear_screen(0);
	draw_image(0,0,IMG_SUN);
	swap_screen();
	bright_up();
	music_play(MUS_MENU);
	read_key();
	sfx_play(SFX_MENU,8);
}

#endif