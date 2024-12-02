#ifndef _START_MENU
#define _START_MENU

void menu_main();
void start_level();
void game_loop();

u8 press_key()
{
	u8 keys[40];
	while (TRUE)
	{
		keyboard(keys);
		if (keys[KEY_SPACE]==KEY_DOWN)
			return KEY_SPACE;
		if (keys[KEY_1]==KEY_DOWN)
			return KEY_1;
		if (keys[KEY_2]==KEY_DOWN)
			return KEY_2;
		if (keys[KEY_3]==KEY_DOWN)
			return KEY_3;
	}
}

void bright_down()
{
	i8 i;
	for (i=BRIGHT_MID;i>=BRIGHT_MIN;i--){
		pal_bright(i);
		delay(3);
	}
}

void bright_up()
{
	i8 i;
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
	press_key();
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
	press_key();
}

void chapter()
{
	u8 n;
	n=0;

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
	press_key();
	bright_down();
}

u8 read_key()
{
	u8 keys[40];
	u8 key;
	key=255;
	while (key==255)
	{
		keyboard(keys);
		if(keys[KEY_0]&KEY_PRESS) key=KEY_0;
		if(keys[KEY_1]&KEY_PRESS) key=KEY_1;
		if(keys[KEY_2]&KEY_PRESS) key=KEY_2;
		if(keys[KEY_3]&KEY_PRESS) key=KEY_3;
		if(keys[KEY_4]&KEY_PRESS) key=KEY_4;
		if(keys[KEY_5]&KEY_PRESS) key=KEY_5;
		if(keys[KEY_6]&KEY_PRESS) key=KEY_6;
		if(keys[KEY_7]&KEY_PRESS) key=KEY_7;
		if(keys[KEY_8]&KEY_PRESS) key=KEY_8;
		if(keys[KEY_9]&KEY_PRESS) key=KEY_9;

		if(keys[KEY_A]&KEY_PRESS) key=KEY_A;
		if(keys[KEY_B]&KEY_PRESS) key=KEY_B;
		if(keys[KEY_C]&KEY_PRESS) key=KEY_C;
		if(keys[KEY_D]&KEY_PRESS) key=KEY_D;
		if(keys[KEY_E]&KEY_PRESS) key=KEY_E;
		if(keys[KEY_F]&KEY_PRESS) key=KEY_F;
		if(keys[KEY_G]&KEY_PRESS) key=KEY_G;
		if(keys[KEY_H]&KEY_PRESS) key=KEY_H;
		if(keys[KEY_I]&KEY_PRESS) key=KEY_I;
		if(keys[KEY_J]&KEY_PRESS) key=KEY_J;
		if(keys[KEY_K]&KEY_PRESS) key=KEY_K;
		if(keys[KEY_L]&KEY_PRESS) key=KEY_L;
		if(keys[KEY_M]&KEY_PRESS) key=KEY_M;
		if(keys[KEY_N]&KEY_PRESS) key=KEY_N;
		if(keys[KEY_O]&KEY_PRESS) key=KEY_O;
		if(keys[KEY_P]&KEY_PRESS) key=KEY_P;
		if(keys[KEY_Q]&KEY_PRESS) key=KEY_Q;
		if(keys[KEY_R]&KEY_PRESS) key=KEY_R;
		if(keys[KEY_S]&KEY_PRESS) key=KEY_S;
		if(keys[KEY_T]&KEY_PRESS) key=KEY_T;
		if(keys[KEY_U]&KEY_PRESS) key=KEY_U;
		if(keys[KEY_V]&KEY_PRESS) key=KEY_V;
		if(keys[KEY_W]&KEY_PRESS) key=KEY_W;
		if(keys[KEY_X]&KEY_PRESS) key=KEY_X;
		if(keys[KEY_Y]&KEY_PRESS) key=KEY_Y;
		if(keys[KEY_Z]&KEY_PRESS) key=KEY_Z;

		if(keys[KEY_SPACE]&KEY_PRESS) key=KEY_SPACE;
		if(keys[KEY_ENTER]&KEY_PRESS) key=KEY_ENTER;
	}
	sfx_play(SFX_MENU,8);
	return key;
}

void redefine_keys()
{
	static u8 redefine[]="ВЫБЕРИТЕ";
	static u8 up[]="ВВЕРХ";
	static u8 down[]="ВНИЗ";
	static u8 right[]="ВПРАВО";
	static u8 left[]="ВЛЕВО";
	static u8 fire[]="ОГОНЬ";
	

	clear_screen(0);
	swap_screen();
	clear_screen(0);
	draw_image(0,0,IMG_BACK_MENU);
	output_string(15, 4, redefine);
	output_string(16, 7, up);
	swap_screen();
	key_up=read_key();

	output_string(16, 9, down);
	swap_screen();
	key_down=read_key();

	output_string(16, 11, right);
	swap_screen();
	key_right=read_key();

	output_string(16, 13, left);
	swap_screen();
	key_left=read_key();

	output_string(16, 15, fire);
	swap_screen();
	key_fire=read_key();
	menu_main();
}

void menu_control()
{
	static u8 menu_control[]="1 КЕМПСТОН^ ^2 КУРСОР+ПРОБЕЛ^ ^3 ВЫБРАТЬ СВОЕ";
	bright_down();
	clear_screen(0);
	draw_image(0,0,IMG_BACK_MENU);
	output_string(13, 8, menu_control);
	swap_screen();
	bright_up();
	switch (press_key())
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
	}
	menu_main();
}

void info()
{
	static u8 info[]="ЛУЧ НАДЕЖДЫ v1.0^ ^код графика звук^ ^  Роман Скорик^ ^      2024";
	
	bright_down();
	clear_screen(0);
	draw_image(0,0,IMG_BACK_MENU);
	output_string(12, 10, info);
	swap_screen();
	bright_up();
	while (TRUE)
	{
		if (press_key()==KEY_SPACE){
			sfx_play(SFX_MENU,8);
			menu_main();
		}
	}
}

void intro()
{
	static u8 text1[]=" В результате активного таяния^полярных льдов, из глубин^океана вырвался древний вирус.^ Сначала заразились рыбы,^потом животные, а после и люди.^ Вирус превращал животных в^ужасных монстров, а людей^в зомби.^ Спастись удалось немногим.";
	
	static u8 text2[]=" Есть сведения, что в секретной^лаборатории ЛУЧ-3 разрабатывалась^вакцина против зомбо-вируса.^Был ли проект закончен неизвестно.^Связь с лабораторией была утеряна.^Лаборатория распологалась в^заброшенной шахте за полярным^кругом.";
	
	static u8 text3[]=" Вам нужно туда отправиться и^все проверить.^ Из снаряжения имеется биозащитный^костюм и модифицированный^керосиновый плазмотрон.^Бьет он не далеко, но эффективно,^а керосин можно найти на месте.^ ЛУЧ - наша последняя надежда.";
	
	bright_down();
	pal_select(2);
	clear_screen(0);
	output_string(5, 3, text1);
	draw_image(16,14,IMG_VIRUS);
	swap_screen();
	bright_up();
	press_key();
	
	bright_down();
	pal_select(0);
	clear_screen(0);
	output_string(4, 3, text2);
	draw_image(10,14,IMG_MINE);
	swap_screen();
	bright_up();
	press_key();
	
	bright_down();
	pal_select(0);
	clear_screen(0);
	output_string(4, 3, text3);
	draw_image(10,14,IMG_SNOWMOB);
	swap_screen();
	bright_up();
	press_key();
	
	level=0;
	start_level();
	game_loop();
}

void menu_main()
{
	static u8 menu_main[]="1 ИГРА^ ^2 УПРАВЛЕНИЕ^ ^3 ИНФОРМАЦИЯ";
	
	set_sprite(0,0,0,SPRITE_END);
	bright_down();
	pal_select(PAL_SUN);
	clear_screen(0);
	draw_image(0,0,IMG_BACK_MENU);
	output_string(13, 8, menu_main);
	swap_screen();
	bright_up();
	switch (press_key())
	{
		case KEY_1:
			sfx_play(SFX_MENU,8);
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
			info();
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
	press_key();
	sfx_play(SFX_MENU,8);
}

#endif