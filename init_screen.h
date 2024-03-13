#ifndef _INIT_SCREEN
#define _INIT_SCREEN

void draw_hud()
{
	pal_select(level);
	clear_screen(0);
	draw_image(0,22,IMG_IMG_HUD);
	update_hud();
}


void init_screen()
{
	static u8  x, y;
	static u16 addr;
	
	addr=32768+(40*screen);
	
	enemy_summ=0;
	water_summ=0;
	waterplant_summ=0;
	
	draw_image(0,0,level_back);
	select_image(level_tile);
	color_key(15);
	
	for (y=0; y<HIGH_LEVEL; y++){
		for (x=0; x<WIDTH_LEVEL; x++) {
			
			draw_tile_key(x,y,get_mem(PAGE_GFX,addr));
			map[y][x]=get_mem(PAGE_MAP,addr++);
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
				
				case STALACT:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*y;
					enemy[enemy_summ].type=STALACT;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].skip=10;
					enemy[enemy_summ].direct=WAIT;
					enemy[enemy_summ].frame=SPR_STALACT;
				break;
				
				case B_SLIME:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=B_SLIME;
					enemy[enemy_summ].health=2;
					enemy[enemy_summ].skip=6;
					enemy[enemy_summ].direct=LEFT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_B_SLIME;
				break;
				
				case S_SLIME:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=S_SLIME;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].skip=7;
					enemy[enemy_summ].direct=RIGHT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_S_SLIME;
				break;
				
				case OWL:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=OWL;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].skip=5;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=LEFT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_OWL;
				break;
				
				case ICE_SPIKE:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=ICE_SPIKE;
					enemy[enemy_summ].health=2;
					enemy[enemy_summ].skip=6;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_ICE_SPIKE;
				break;
				
				case BLOCK:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=BLOCK;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].skip=10;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_BLOCK;
				break;
				
				case SNOWMEN:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=SNOWMEN;
					enemy[enemy_summ].health=3;
					enemy[enemy_summ].skip=4;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_SNOWMEN;
				break;
				
			}
		}
		addr+=(level_size-1)*40;
	}
	set_sprite(0,0,0,SPRITE_END);
	swap_screen();
}


void start_level()
{
	//i8 i;
	screen=0;//0;8
	player.x=8;
	player.y=120;//120;
	player.health=4;
	player.ammo=0;
	player.frame=25;
	player.enemy_collision=0;

	// for (i=BRIGHT_MID;i>=BRIGHT_MIN;i--){
		// pal_bright(i);
		// delay(3);
	// }
	
	load_level();
	
	clear_screen(0);
	
	draw_hud();

	init_screen();
	// for (i=BRIGHT_MIN;i<=BRIGHT_MID+1;i++){
		// pal_bright(i);
		// delay(3);
	// }

}


void nxt_screen()
{
	screen++;
	player.x=1;
	player.enemy_collision=0;
	init_screen();
	update_screen();
}


void prv_screen()
{
	screen--;
	player.x=152;
	player.enemy_collision=0;
	init_screen();
	update_screen();
}


#endif