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
	
	switch (enemy[n].fly) {
		case TRUE:
			if (map[eyd][exr]==WALL||exr==39)
				collision^=COL_RIGHT;
			if (map[eyd][exl]==WALL||exl==0)
				collision^=COL_LEFT;
		break;
		
		case FALSE:
			if (map[eyd][exr]==WALL||map[eyd+1][exr]==EMPTY)
				collision^=COL_RIGHT;
			if (map[eyd][exl]==WALL||map[eyd+1][exl]==EMPTY)
				collision^=COL_LEFT;
		break;
		
	}
	return collision;
}

void enemy_logic()
{
	u8 e_collision;
	u8 n;
	
	for (n=1;n<=enemy_summ;n++){
		
		e_collision=enemy_collision(n);
		
		if (!enemy[n].health)
			enemy[n].direct=ST_DEATH;
		
		if (enemy[n].direct==RIGHT) {
			if ((e_collision&COL_RIGHT)!=COL_RIGHT)
				enemy[n].x++;
			else enemy[n].direct=LEFT;
		}
		if (enemy[n].direct==LEFT) {
			if ((e_collision&COL_LEFT)!=COL_LEFT)
				enemy[n].x--;
			else enemy[n].direct=RIGHT;
		}
	}
}

void enemy_animation()
{
	u8 n;
	u8 n_spr=0;
	
	for (n=1;n<=enemy_summ;n++){
		
		switch (enemy[n].type) {
			case B_SLIME:
				n_spr=SPR_B_SLIME;
			break;
			case S_SLIME:
				n_spr=SPR_S_SLIME;
			break;
			case OWL:
				n_spr=SPR_OWL;
			break;
		}

		switch (enemy[n].direct) {
			
			case ST_DEATH:
				if (enemy[n].frame==n_spr+11){
					enemy[n].direct=FALSE;
					enemy[n].x=0;
					enemy[n].y=184;
					break;
				}
				if (enemy[n].frame<n_spr+7)
					enemy[n].frame=n_spr+7;
				enemy[n].frame++;
				break;
			
			case RIGHT:
				if (enemy[n].frame>(n_spr+3))
					enemy[n].frame=n_spr;
				enemy[n].frame=enemy[n].frame<(n_spr+3)?++enemy[n].frame:(n_spr+0);
				break;
			
			case LEFT:
				if (enemy[n].frame<(n_spr+4))
					enemy[n].frame=n_spr+4;
				enemy[n].frame=enemy[n].frame<(n_spr+7)?++enemy[n].frame:(n_spr+4);
				break;
			
			default:
				break;
		}
	}
}

#endif