#ifndef _INIT_SCREEN
#define _INIT_SCREEN

void draw_screen()
{
	u8 x, y;
	
	select_image(IMG_TILE_SNOW);
	
	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++)
			draw_tile(x,y,map[y][x]);
}


void init_screen()
{
	u8 x, y;
	
	u8 n=0,m=0,i=0,j=0;
	
	enemy_summ=0;
	water_summ=0;
	
	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++) {
			
			switch (map[y][x]) {
				
				// case PLAYER:
					// player.x=4*x;
					// player.y=8*(y-1);
					// map[y][x]=0;
					// player.health=10;
					// player.frame=20;
				// break;
				
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
					enemy_skip=5;
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
					enemy_skip=5;
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
					enemy_skip=4;
				break;
			}
			
		}	
}

#endif