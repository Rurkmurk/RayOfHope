#ifndef _ENEMY
#define _ENEMY

u16 enemy_collision(u8 n)
{
	u8 exl, exr, eyu, eyd;
	
	u16 collision=0;
	
	exl=(enemy[n].x+1)/4;
	exr=(enemy[n].x+6)/4;
	
	eyu=(enemy[n].y)/8;
	eyd=(enemy[n].y+15)/8;
	
	switch (enemy[n].type) {
		case OWL:
			if (map[eyd][exr]==WALL||exr==39)
				collision^=COL_RIGHT;
			if (map[eyd][exl]==WALL||exl==0)
				collision^=COL_LEFT;
		break;
		
		case B_SLIME||S_SLIME:
			if (map[eyd][exr]==WALL||map[eyd+1][exr]==EMPTY)
				collision^=COL_RIGHT;
			if (map[eyd][exl]==WALL||map[eyd+1][exl]==EMPTY)
				collision^=COL_LEFT;
		break;
		
		case STALACT:
			switch (enemy[n].direct){
				case FALSE:
					if (player.x==enemy[n].x)
						collision^=COL_STALACT;
				break;
				case DOWN:
					if (map[eyd][exl]==WALL)
						collision^=COL_DOWN;
				break;
				case ST_DEATH:
					if (player.y+2>(enemy[n].y)&&player.y<(enemy[n].y+2)){
						if (player.x+2>=enemy[n].x&&player.x<=enemy[n].x+2){
							player.health=0;
							update_hud();
						}
					}
				break;
			}
		break;
		
		default: collision=0;
	}
	
	if (player.y+15>(enemy[n].y)&&player.y<(enemy[n].y+15)){
		if (player.x+6==enemy[n].x||player.x+5==enemy[n].x){
			player.enemy_collision=COL_ENEMY_RIGHT;
		}
		else if (player.x==enemy[n].x+6||player.x==enemy[n].x+5){
			player.enemy_collision=COL_ENEMY_LEFT;
		}
		else player.enemy_collision=0;
	}
	
	return collision;
}


void enemy_animation(u8 n)
{
	u8 n_spr=0;
	u8 tmp_frame, j;
	
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
		case STALACT:
			n_spr=SPR_STALACT;
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
			if (enemy[n].frame<n_spr+8){
				enemy[n].frame=n_spr+8;
				enemy[n].skip_count=0;
			}
			enemy[n].skip_count++;
			if (enemy[n].skip_count>=DEATH_SPEED){
				enemy[n].skip_count=0;
				enemy[n].frame++;
			}
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
			
		case DOWN:
			enemy[n].frame=n_spr+1;
		break;
		
		
		default:
			break;
	}
}


void enemy_logic()
{

	u16 e_collision;
	u8 n;
	u8 j;
	
	for (n=1;n<=enemy_summ;n++){
		
		e_collision=enemy_collision(n);
		
		if (!enemy[n].health)
			enemy[n].direct=ST_DEATH;
		
		switch (enemy[n].direct) {
			case RIGHT:
				if ((e_collision&COL_RIGHT)!=COL_RIGHT){
					enemy[n].skip_count++;
					if (enemy[n].skip_count>=enemy[n].skip){
						enemy[n].x++;
						enemy[n].skip_count=0;
						enemy_animation(n);
					}
				}
				else enemy[n].direct=LEFT;
			break;
			
			case LEFT:
				if ((e_collision&COL_LEFT)!=COL_LEFT){
					enemy[n].skip_count++;
					if (enemy[n].skip_count>=enemy[n].skip){
						enemy[n].x--;
						enemy[n].skip_count=0;
						enemy_animation(n);
					}
				}
				else enemy[n].direct=RIGHT;
			break;
			
			case FALSE:
				if ((e_collision&COL_STALACT)==COL_STALACT){
					enemy[n].direct=DOWN;
					enemy_animation(n);
				}
			break;
			
			case DOWN:
				if ((e_collision&COL_DOWN)!=COL_DOWN){
					enemy[n].skip+=1;
					for (j=0;j<enemy[n].skip;j++)
						if ((enemy_collision(n)&COL_DOWN)!=COL_DOWN)
							enemy[n].y++;
				}
				else enemy[n].health=0;
			break;
			
			case ST_DEATH:
				enemy_animation(n);
			break;
				
			default: break;
		}
		
		
		
		
		
		// if (enemy[n].direct==RIGHT) {
			// if ((e_collision&COL_RIGHT)!=COL_RIGHT){
				// enemy[n].skip_count++;
				// if (enemy[n].skip_count>=enemy[n].skip){
					// enemy[n].x++;
					// enemy[n].skip_count=0;
					// enemy_animation(n);
				// }
			// }
			// else enemy[n].direct=LEFT;
		// }
		// if (enemy[n].direct==LEFT) {
			// if ((e_collision&COL_LEFT)!=COL_LEFT){
				// enemy[n].skip_count++;
				// if (enemy[n].skip_count>=enemy[n].skip){
					// enemy[n].x--;
					// enemy[n].skip_count=0;
					// enemy_animation(n);
				// }
			// }
			// else enemy[n].direct=RIGHT;
		// }
	}
}

#endif