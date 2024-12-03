#ifndef _INIT_SCREEN
#define _INIT_SCREEN

void draw_hud()
{
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
	light_summ=0;
	fan_summ=0;
	
	//pal_select(level_palett_default);
	
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
						switch (level){
							case 1:
							water[water_summ].n_spr=SPR_WATER_MINE;
							water[water_summ].frame=SPR_WATER_MINE;
							waterplant[water_summ].frame=SPR_WATER_MINE+2;
							break;
							case 2:
							water[water_summ].n_spr=SPR_ACID;
							water[water_summ].frame=SPR_ACID;
							waterplant[water_summ].frame=SPR_ACID+2;
							break;
							default:
							water[water_summ].n_spr=SPR_WATER_SNOW;
							water[water_summ].frame=SPR_WATER_SNOW;
							waterplant[water_summ].frame=SPR_WATER_SNOW+2;
							break;
						}
					}
					else {
						switch (level){
							case 1:
							water[water_summ].n_spr=SPR_WATER_MINE;
							water[water_summ].frame=SPR_WATER_MINE+1;
							waterplant[water_summ].frame=SPR_WATER_MINE+3;
							break;
							case 2:
							water[water_summ].n_spr=SPR_ACID;
							water[water_summ].frame=SPR_ACID+1;
							waterplant[water_summ].frame=SPR_ACID+3;
							break;
							default:
							water[water_summ].n_spr=SPR_WATER_SNOW;
							water[water_summ].frame=SPR_WATER_SNOW+1;
							waterplant[water_summ].frame=SPR_WATER_SNOW+3;
							break;
						}
					}
				break;
				
				case LIGHT_1:
					light_summ++;
					light[light_summ].x=4*x;
					light[light_summ].y=8*y;
					switch (level){
						case 0:
							light[light_summ].frame=SPR_LIGHT_1_SNOW;
							light[light_summ].n_spr=SPR_LIGHT_1_SNOW;
						break;
						case 1:
							light[light_summ].frame=SPR_LIGHT_1_MINE;
							light[light_summ].n_spr=SPR_LIGHT_1_MINE;
						break;
						case 2:
							light[light_summ].frame=SPR_LIGHT_1_LAB;
							light[light_summ].n_spr=SPR_LIGHT_1_LAB;
						break;
					}
				break;
				
				case LIGHT_2:
					light_summ++;
					light[light_summ].x=4*x;
					light[light_summ].y=8*y;
					switch (level){
						case 0:
							light[light_summ].frame=SPR_LIGHT_2_SNOW;
							light[light_summ].n_spr=SPR_LIGHT_2_SNOW;
						break;
						case 1:
							light[light_summ].frame=SPR_LIGHT_2_MINE;
							light[light_summ].n_spr=SPR_LIGHT_2_MINE;
						break;
						case 2:
							light[light_summ].frame=SPR_LIGHT_2_LAB;
							light[light_summ].n_spr=SPR_LIGHT_2_LAB;
						break;
					}
				break;
				
				
				case FAN:
					fan_summ++;
					fan[fan_summ].x=4*x;
					fan[fan_summ].y=8*y;
					fan[fan_summ].frame=SPR_FAN;
					fan[fan_summ].n_spr=SPR_FAN;
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
					//map[y][x]=0;
					switch (level){
						case 0:
							enemy[enemy_summ].frame=SPR_BLOCK+12;
						break;
						case 1:
							enemy[enemy_summ].frame=SPR_COAL+12;
						break;
						case 2:
							enemy[enemy_summ].frame=SPR_COLBA+12;
						break;
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
					enemy[enemy_summ].frame=SPR_STALACT+12;
				break;
				
				case B_SLIME:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=B_SLIME;
					enemy[enemy_summ].health=2;
					enemy[enemy_summ].skip=10;
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
					enemy[enemy_summ].skip=8;
					enemy[enemy_summ].direct=RIGHT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_S_SLIME;
					switch (level){
						case 0:
							enemy[enemy_summ].frame=SPR_S_SLIME;
						break;
						case 1:
							enemy[enemy_summ].frame=SPR_S_SLIME;
						break;
						case 2:
							enemy[enemy_summ].frame=SPR_S_SLIME_LAB;
						break;
					}
				break;
				
				case OWL:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=OWL;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].skip=6;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=LEFT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_OWL;
				break;
				
				case BAT:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=BAT;
					enemy[enemy_summ].health=2;
					enemy[enemy_summ].skip=4;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=UP;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_BAT;
				break;
				
				case ICE_SPIKE:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=ICE_SPIKE;
					enemy[enemy_summ].health=2;
					enemy[enemy_summ].skip=14;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_ICE_SPIKE+12;
				break;
				
				case SPIDER:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=SPIDER;
					enemy[enemy_summ].health=2;
					enemy[enemy_summ].skip=12;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_SPIDER+12;
				break;
				
				case ZOMBI:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=ZOMBI;
					enemy[enemy_summ].health=3;
					enemy[enemy_summ].skip=15;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_ZOMBI+12;
				break;
				
				case ZOMBI_HAT:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=ZOMBI_HAT;
					enemy[enemy_summ].health=3;
					enemy[enemy_summ].skip=20;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_ZOMBI_HAT+12;
				break;
				
				case SNOW_JUMP:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=SNOW_JUMP;
					enemy[enemy_summ].health=3;
					enemy[enemy_summ].skip=6;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_SNOW_JUMP;
				break;
				
				case MINE_JUMP:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=MINE_JUMP;
					enemy[enemy_summ].health=4;
					enemy[enemy_summ].skip=8;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_MINE_JUMP;
				break;
				
				case ANGRY_PLANT_R:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*(x-1);
					enemy[enemy_summ].y=8*y;
					enemy[enemy_summ].type=ANGRY_PLANT_R;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].skip=7;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_ANGRY_PLANT_R+12;
				break;
				
				case ANGRY_PLANT_L:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*y;
					enemy[enemy_summ].type=ANGRY_PLANT_L;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].skip=7;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_ANGRY_PLANT_L+12;
				break;
				
				case ANGRY_PLANT:
					enemy_summ++;
					enemy[enemy_summ].x_start=x;
					enemy[enemy_summ].y_start=y;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=ANGRY_PLANT;
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].skip=14;
					enemy[enemy_summ].skip_count=0;
					enemy[enemy_summ].direct=WAIT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_ANGRY_PLANT+12;
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
	set_sprite(0,0,0,SPRITE_END);
	bright_down();
	load_level();
	
	chapter();
	
	tmp_save.screen=screen;
	tmp_save.health=player.health;
	tmp_save.ammo=player.ammo;
	tmp_save.x=player.x;
	tmp_save.y=player.y;

	clear_screen(0);
	
	draw_hud();

	init_screen();
	
	bright_up();
}



void restart_level()
{
	i8 i;
	screen=tmp_save.screen;
	player.x=tmp_save.x;
	player.y=tmp_save.y;
	player.health=tmp_save.health;
	player.ammo=tmp_save.ammo;
	player.frame=25;
	player.enemy_collision=0;
	player.v_speed=0;
	
	bright_down();
	
	reload_level();
	
	clear_screen(0);
	
	//pal_select(level_palett_default);
	
	draw_hud();

	init_screen();
	
	bright_up();
}

void nxt_screen()
{
	screen++;
	player.x=1;
	if (screen!=tmp_save.screen)
		if (screen==6||screen==12){
			tmp_save.screen=screen;
			tmp_save.health=player.health;
			tmp_save.ammo=player.ammo;
			tmp_save.x=player.x;
			tmp_save.y=player.y;
			}
	player.enemy_collision=0;
	init_screen();
	update_screen();
	//pal_select(level_palett_default);
}


void prv_screen()
{
	screen--;
	player.x=152;
	player.enemy_collision=0;
	init_screen();
	update_screen();
	//pal_select(level_palett_default);
}


void down_screen()
{
	screen+=3;
	player.y=2;
	if (screen!=tmp_save.screen)
		if (screen==6||screen==12){
			tmp_save.screen=screen;
			tmp_save.health=player.health;
			tmp_save.ammo=player.ammo;
			tmp_save.x=player.x;
			tmp_save.y=player.y;
			}
	player.enemy_collision=0;
	init_screen();
	update_screen();
	//pal_select(level_palett_default);
}

void up_screen()
{
	screen-=3;
	player.y=159;
	player.enemy_collision=0;
	init_screen();
	update_screen();
	//pal_select(level_palett_default);
}


#endif