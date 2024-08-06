#ifndef _START_MENU
#define _START_MENU



void press_key()
{
	while (TRUE)
	{
		vsync();
		if(joystick())
		{
			return;
		}
	}
}

void chapter()
{
	i8 i, n;
	n=0;

	clear_screen(0);
	switch (level){
	case 0:
	//pal_select(0);
	n=IMG_CHAPTER_1;
	break;
	case 1:
	//pal_select(1);
	n=IMG_CHAPTER_2;
	break;
	case 2:
	//pal_select(0);
	n=IMG_CHAPTER_1;
	break;
	}
	draw_image(10,6,n);
	swap_screen();
	for (i=BRIGHT_MIN;i<=BRIGHT_MID;i++){
		pal_bright(i);
		delay(3);
	}
	press_key();
}

void start()
{
	i8 i;
	pal_select(PAL_SUN);
	pal_bright(BRIGHT_MIN);
	border (0);
	clear_screen(0);
	draw_image(0,0,IMG_SUN);
	swap_screen();
	for (i=BRIGHT_MIN;i<=BRIGHT_MID;i++){
		pal_bright(i);
		delay(3);
	}
	press_key();
	for (i=BRIGHT_MID;i>=BRIGHT_MIN;i--){
		pal_bright(i);
		delay(3);
	}
}

#endif