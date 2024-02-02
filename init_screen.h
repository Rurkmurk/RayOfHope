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
				
				case B_SLIME:
					enemy_summ++;
					enemy[enemy_summ].x=4*x;
					enemy[enemy_summ].y=8*(y-1);
					enemy[enemy_summ].type=B_SLIME;
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
					enemy[enemy_summ].health=1;
					enemy[enemy_summ].direct=RIGHT;
					map[y][x]=0;
					enemy[enemy_summ].frame=SPR_S_SLIME;
				break;
			}
			
		}	
}

#endif