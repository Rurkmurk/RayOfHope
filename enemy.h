#ifndef _ENEMY
#define _ENEMY

u8 enemy_collision(u8 n)
{
	u8 exl, exr, eyu, eyd;
	
	u8 collision=0;
	
	exl=(enemy[n].x+1)/4;
	exr=(enemy[n].x+6)/4;
	
	eyu=(enemy[n].y)/8;
	eyd=(enemy[n].y+15)/8;
	
	if (map[eyd][exr]>47||map[eyd+1][exr]<80)
		collision^=RIGHT;
	if (map[eyd][exl]>47||map[eyd+1][exl]<80)
		collision^=LEFT;
	return collision;
}

void enemy_logic()
{
	u8 e_collision;
	u8 n;
	
	for (n=1;n<=enemy_summ;n++){
		
		e_collision=enemy_collision(n);
		
		if (!enemy[n].health)
			enemy[n].direct=DEATH;
		
		if (enemy[n].direct==RIGHT) {
			if ((e_collision&RIGHT)!=RIGHT)
				enemy[n].x++;
			else enemy[n].direct=LEFT;
		}
		if (enemy[n].direct==LEFT) {
			if ((e_collision&LEFT)!=LEFT)
				enemy[n].x--;
			else enemy[n].direct=RIGHT;
		}
	}
}

void enemy_animation()
{
	u8 n;
	
	for (n=1;n<=enemy_summ;n++){
		
		if (enemy[n].type==B_SLIME) {
			switch (enemy[n].direct) {
				
				case DEATH:
					if (enemy[n].frame==SPR_B_SLIME+11){
						enemy[n].direct=FALSE;
						enemy[n].x=0;
						enemy[n].y=184;
						break;
					}
					if (enemy[n].frame<SPR_B_SLIME+7)
						enemy[n].frame=SPR_B_SLIME+7;
					enemy[n].frame++;
					break;
				
				case RIGHT:
					if (enemy[n].frame>(SPR_B_SLIME+3))
						enemy[n].frame=SPR_B_SLIME;
					enemy[n].frame=enemy[n].frame<(SPR_B_SLIME+3)?++enemy[n].frame:(SPR_B_SLIME+0);
					break;
				
				case LEFT:
					if (enemy[n].frame<(SPR_B_SLIME+4))
						enemy[n].frame=SPR_B_SLIME+4;
					enemy[n].frame=enemy[n].frame<(SPR_B_SLIME+7)?++enemy[n].frame:(SPR_B_SLIME+4);
					break;
				
				default:
					break;
			}
		}
		if (enemy[n].type==S_SLIME) {
			switch (enemy[n].direct) {
				
				case DEATH:
					if (enemy[n].frame==SPR_S_SLIME+11){
						enemy[n].direct=FALSE;
						enemy[n].x=0;
						enemy[n].y=184;
						break;
					}
					if (enemy[n].frame<SPR_S_SLIME+7)
						enemy[n].frame=SPR_S_SLIME+7;
					enemy[n].frame++;
					break;
				
				case RIGHT:
					if (enemy[n].frame>(SPR_S_SLIME+3))
						enemy[n].frame=SPR_S_SLIME;
					enemy[n].frame=enemy[n].frame<(SPR_S_SLIME+3)?++enemy[n].frame:(SPR_S_SLIME);
					break;
				
				case LEFT:
					if (enemy[n].frame<(SPR_S_SLIME+4))
						enemy[n].frame=SPR_S_SLIME+4;
					enemy[n].frame=enemy[n].frame<(SPR_S_SLIME+7)?++enemy[n].frame:(SPR_S_SLIME+4);
					break;
			}
		}
	}
}
#endif