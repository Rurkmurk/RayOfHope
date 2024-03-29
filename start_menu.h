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
	
	for (i=BRIGHT_MID;i>=BRIGHT_MIN;i--){
		pal_bright(i);
		delay(3);
	}
	clear_screen(0);
	switch (level){
	case 0:
	n=IMG_CHAPTER_1;
	break;
	// case 1:
	// n=IMG_CHAPTER_2;
	// break;
	// case 2:
	// n=IMG_CHAPTER_3;
	// break;
	}
	draw_image(10,6,n);
	for (i=BRIGHT_MIN;i<=BRIGHT_MID;i++){
		pal_bright(i);
		delay(3);
	}
	swap_screen();
	press_key();
}



#endif