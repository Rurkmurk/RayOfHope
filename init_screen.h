#ifndef _INIT_SCREEN
#define _INIT_SCREEN

void draw_screen()
{
	u8 x, y, n=0;
	
	u16 addr;
	addr=32768+40*screen;
	
	pal_select(level);
	clear_screen(0);
	
	draw_image(0,0,IMG_BACK_SNOW);
	
	select_image(IMG_TILE_SNOW);
	color_key(15);
	for (y=0; y<HIGH_LEVEL; y++){
		for (x=0; x<WIDTH_LEVEL; x++){
			draw_tile_key(x,y,get_mem(61,addr++));
		}
		addr+=160;
	}
	
	select_image(IMG_TILE_HUD);
	for (y=22; y<25; y++)
		for (x=0; x<40; x++){
			draw_tile(x,y,n);
			n++;
		}
}

void init_screen()
{
	u8 x, y;
	
	u8 n=0,m=0,i=0,j=0;
	
	u16 addr=0;
	
	addr=32768+40*screen;
	
	enemy_summ=0;
	water_summ=0;
	waterplant_summ=0;
	
	for (y=0; y<HIGH_LEVEL; y++){
		for (x=0; x<WIDTH_LEVEL; x++) {
			
			map[y][x]=get_mem(63,addr++);
			
			switch (map[y][x]) {
				
				case WATER:
					water_summ++;
					waterplant_summ++;
					water[water_summ].x=4*x;
					water[water_summ].y=8*y;
					waterplant[water_summ].x=water[water_summ].x;
					waterplant[water_summ].y=water[water_summ].y+16;
					if (water_summ%2!=0){
						water[water_summ].frame=SPR_WATER;
						waterplant[water_summ].frame=SPR_WATER+2;
					}
					else {
						water[water_summ].frame=SPR_WATER+1;
						waterplant[water_summ].frame=SPR_WATER+3;
					}
				break;
				
				case B_SLIME:
					enemy_summ++;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=B_SLIME;
					enemy[enemy_summ].fly=FALSE;
					enemy[enemy_summ].health=2;
					enemy[enemy_summ].direct=LEFT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_B_SLIME;
				break;
				
				case S_SLIME:
					enemy_summ++;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=S_SLIME;
					enemy[enemy_summ].fly=FALSE;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].direct=RIGHT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_S_SLIME;
				break;
				
				case OWL:
					enemy_summ++;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=OWL;
					enemy[enemy_summ].fly=TRUE;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].direct=LEFT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_OWL;
				break;
			}
		}
		addr+=160;
	}
	update_screen();
}

void start_level()
{
	i8 i=3;
	screen=0;
	player.x=8;
	player.y=120;
	player.health=5;
	player.ammo=0;
	player.frame=1;
	player.enemy_collision=0;
	for (i=BRIGHT_MID;i>=BRIGHT_MIN;i--){
		pal_bright(i);
		delay(3);
	}
	draw_screen();
	init_screen();
	for (i=BRIGHT_MIN;i<=BRIGHT_MID;i++){
		pal_bright(i);
		delay(3);
	}
}

void nxt_screen()
{
	screen++;
	player.x=1;
	player.enemy_collision=0;
	draw_screen();
	init_screen();
}

void prv_screen()
{
	screen--;
	player.x=152;
	player.enemy_collision=0;
	draw_screen();
	init_screen();
}

#endif