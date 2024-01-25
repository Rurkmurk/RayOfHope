#ifndef _INIT_SCREEN
#define _INIT_SCREEN

void draw_screen()
{
	u8 x, y;
	
	select_image(IMG_TILE);
	
	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++)
			draw_tile(x,y,map[y][x]);
}


void init_screen()
{
	u8 x, y;
	
	u8 n=0,m=0,i=0,j=0;
	


	
	select_image(IMG_TILE);


	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++) {
			
			if (map[y][x]==LAVA) {
				lava[n].x[m]=x;
				lava[n].y[0]=y;
				lava[n].tile[m]=48+m;
				draw_tile(lava[n].x[m],lava[n].y[0],lava[n].tile[m]);
				lava[n].y[1]=y+1;
				lava[n].tile[m+4]=52+m;
				m++;
				if (m>3) {
					lava_summ++;
					m=0;
					n++;
				}
			}
			if (map[y][x]==WATER_WAVE) {
				water[i].x[j]=x;
				water[i].y[0]=y;
				water[i].tile[j]=64+j;
				draw_tile(water[i].x[j],water[i].y[0],water[i].tile[j]);
				water[i].y[1]=y+3;
				water[i].tile[j+4]=72+j;
				draw_tile(water[i].x[j],water[i].y[1],water[i].tile[j+4]);
				j++;
				if (j>3) {
					water_summ++;
					j=0;
					i++;
				}
			}
			
			switch (map[y][x]) {
				
				case PLAYER:
					player.x=4*x;
					player.y=8*(y-1);
					map[y][x]=0;
					player.health=10;
					player.frame=20;
				break;
				
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