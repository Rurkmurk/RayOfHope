#ifndef _ENEMY
#define _ENEMY

void player_enemy_collision_push(u8 n)
{
	if (player.y+15>(enemy[n].y)&&player.y<(enemy[n].y+15)){
		if (player.x+6==enemy[n].x||player.x+5==enemy[n].x)
			player.enemy_collision=COL_ENEMY_RIGHT;
		else if (player.x==enemy[n].x+6||player.x==enemy[n].x+5)
			player.enemy_collision=COL_ENEMY_LEFT;
		else if (player.x==enemy[n].x)
			player.enemy_collision=COL_ENEMY_CENTR;
	}
}

void player_enemy_collision_pull(u8 n)
{
	if (player.y+8>enemy[n].y&&player.y-8<enemy[n].y){
		if (player.x+5>=enemy[n].x&&player.x<enemy[n].x)
			player.enemy_collision=COL_ENEMY_LEFT;
		else if (player.x<=enemy[n].x+5&&player.x>enemy[n].x)
			player.enemy_collision=COL_ENEMY_RIGHT;
		else if (player.x==enemy[n].x)
			player.enemy_collision=COL_ENEMY_CENTR;
	}
}

void player_enemy_collision_block(u8 n)
{
	if (player.y+16>(enemy[n].y)&&player.y<(enemy[n].y+16)){
		if (player.x+6==enemy[n].x||player.x+5==enemy[n].x||player.x+4==enemy[n].x)
			player.enemy_collision=COL_ENEMY_LEFT+COL_ENEMY_CENTR;
		else if (player.x==enemy[n].x+6||player.x==enemy[n].x+5||player.x==enemy[n].x+4)
			player.enemy_collision=COL_ENEMY_RIGHT+COL_ENEMY_CENTR;
	}
}

u16 enemy_collision(u8 n)
{
	u8 i;
	
	static u8 exl, exr, eyu, eyd;
	
	static u16 collision;
	
	collision=0;
	
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
			player_enemy_collision_push(n);
		break;
		
		case BLOCK:
			player_enemy_collision_block(n);
		break;
		
		case ICE_SPIKE:
			if (player.y==enemy[n].y){
				if (enemy[n].x-player.x<=24&&player.x<enemy[n].x)
					collision=COL_RIGHT;
				else if (player.x-enemy[n].x<=24&&player.x>enemy[n].x)
					collision=COL_LEFT;
			}
			if (map[eyd][exr]==WALL||map[eyd+1][exr]!=WALL||exr==39)
				collision=COL_RIGHT;
			if (map[eyd][exl]==WALL||map[eyd+1][exl]!=WALL||exl==0)
				collision=COL_LEFT;
			player_enemy_collision_push(n);
		break;
		
		case S_SLIME:
			if (map[eyd][exr]==WALL||map[eyd+1][exr]!=WALL||exr==39)
				collision^=COL_RIGHT;
			if (map[eyd][exl]==WALL||map[eyd+1][exl]!=WALL||exl==0)
				collision^=COL_LEFT;
			player_enemy_collision_pull(n);
		break;
		
		case B_SLIME:
			if (map[eyd][exr]==WALL||map[eyd+1][exr]!=WALL||exr==39)
				collision^=COL_RIGHT;
			if (map[eyd][exl]==WALL||map[eyd+1][exl]!=WALL||exl==0)
				collision^=COL_LEFT;
			player_enemy_collision_pull(n);
		break;
		
		case STALACT:
			switch (enemy[n].direct){
				case WAIT:
					if (player.y>enemy[n].y){
						if (player.x+4>enemy[n].x&&player.x-4<enemy[n].x)
							collision^=COL_STALACT;
					}
					else if (player.status==ST_DOWN_PUSH){
						if (player.x+3>enemy[n].x&&player.x-3<enemy[n].x)
							collision^=COL_STALACT;
					}
				break;
				
				case DOWN:
					if (map[eyd][exl]==WALL)
						collision^=COL_DOWN;
					if (player.y==enemy[n].y){
						if (player.x+2>=enemy[n].x&&player.x<=enemy[n].x+2){
							player.health=0;
							update_hud();
						}
					}
					for (i=1;i<=enemy_summ;i++){
						if (n==i)
							continue;
						if (enemy[i].y<=enemy[n].y)
							if (enemy[i].x+3>=enemy[n].x&&enemy[i].x<=enemy[n].x+3)
							enemy[i].health=0;
						}
				break;
			}
		break;
		
		case SNOW_JUMP:
			if (player.y==enemy[n].y){
				if (player.x<enemy[n].x)
					collision=COL_RIGHT;
				else if (player.x>enemy[n].x)
					collision=COL_LEFT;
			}
			if (map[eyd][exr]==WALL||map[eyd+1][exr]!=WALL||exr==39)
				collision=COL_RIGHT;
			if (map[eyd][exl]==WALL||map[eyd+1][exl]!=WALL||exl==0)
				collision=COL_LEFT;
			player_enemy_collision_pull(n);
		break;
		
		case MINE_JUMP:
			if (player.y==enemy[n].y){
				if (player.x<enemy[n].x)
					collision=COL_RIGHT;
				else if (player.x>enemy[n].x)
					collision=COL_LEFT;
			}
			if (map[eyd][exr]==WALL||map[eyd+1][exr]!=WALL||exr==39)
				collision=COL_RIGHT;
			if (map[eyd][exl]==WALL||map[eyd+1][exl]!=WALL||exl==0)
				collision=COL_LEFT;
			player_enemy_collision_pull(n);
		break;
		
		case ANGRY_PLANT_R:
			if (player.y+8>enemy[n].y&&player.y-8<enemy[n].y){
				if (player.x+9>enemy[n].x&&player.x-1<enemy[n].x)
					collision=COL_DANGER;
			}
			player_enemy_collision_pull(n);
		break;
		
		case ANGRY_PLANT_L:
			if (player.y+8>enemy[n].y&&player.y-8<enemy[n].y){
				if (player.x-9<enemy[n].x&&player.x+1>enemy[n].x)
					collision=COL_DANGER;
			}
			player_enemy_collision_pull(n);
		break;
		
		default: collision=0;
	}
	return collision;
}


void enemy_animation(u8 n)
{
	static u8 n_spr;
	
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
		case ICE_SPIKE:
			n_spr=SPR_ICE_SPIKE;
		break;
		case BLOCK:
			n_spr=SPR_BLOCK;
		break;
		case SNOW_JUMP:
			n_spr=SPR_SNOW_JUMP;
		break;
		case MINE_JUMP:
			n_spr=SPR_MINE_JUMP;
		break;
		case ANGRY_PLANT_R:
			n_spr=SPR_ANGRY_PLANT_R;
		break;
		case ANGRY_PLANT_L:
			n_spr=SPR_ANGRY_PLANT_L;
		break;
	}

	switch (enemy[n].direct) {
		
		case ST_DEATH:
			if (enemy[n].frame==n_spr+11){
				enemy[n].direct=FALSE;
				break;
			}
			if (enemy[n].frame<n_spr+8||enemy[n].frame>n_spr+11){
				enemy[n].frame=n_spr+8;
				enemy[n].skip_count=0;
				if (enemy[n].type!=STALACT&&enemy[n].type!=BLOCK)
					sfx_play(SFX_ENEMY_DEATH,8);
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
			enemy[n].frame=n_spr+8;
		break;
		
		case WAIT:
			if (enemy[n].frame<(n_spr+12))
				enemy[n].frame=n_spr+12;
			enemy[n].frame=enemy[n].frame<(n_spr+19)?++enemy[n].frame:(n_spr+12);
		break;
		
		case ANGRY:
			if (enemy[n].frame>(n_spr+7))
				enemy[n].frame=n_spr;
			enemy[n].frame=enemy[n].frame<(n_spr+7)?++enemy[n].frame:(n_spr+0);
		break;
		
		default:
			break;
	}
}

 
void enemy_logic()
{
	static u16 addr;
	static u16 e_collision;
	static u8 n;
	static u8 j;
	
	for (n=1;n<=enemy_summ;n++){
		
		if (enemy[n].direct==FALSE)
			continue;
		
		e_collision=enemy_collision(n);
		
		if (!enemy[n].health){
			enemy[n].direct=ST_DEATH;
			addr=32768+(40*screen)+(40*level_size*enemy[n].y_start+enemy[n].x_start);
			put_mem(PAGE_MAP,addr,0);
		}
		
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
			
			case WAIT:
				if ((e_collision&COL_RIGHT)==COL_RIGHT)
					enemy[n].direct=LEFT;
				if ((e_collision&COL_LEFT)==COL_LEFT)
					enemy[n].direct=RIGHT;
				if ((e_collision&COL_STALACT)==COL_STALACT)
					enemy[n].direct=DOWN;
				if ((e_collision&COL_DANGER)==COL_DANGER)
					enemy[n].direct=ANGRY;
				enemy[n].skip_count++;
				if (enemy[n].skip_count>=enemy[n].skip){
					enemy[n].skip_count=0;
					enemy_animation(n);
				}
			break;
			
			case DOWN:
				if ((e_collision&COL_DOWN)!=COL_DOWN){
					enemy[n].skip+=1;
					for (j=10;j<enemy[n].skip;j++)
						if ((enemy_collision(n)&COL_DOWN)!=COL_DOWN)
					enemy[n].y++;
					enemy_animation(n);
				}
				else{
					enemy[n].health=0;
					sfx_play(SFX_STALACTIT,8);
				}
			break;
			
			case ANGRY:
				if ((e_collision&COL_DANGER)!=COL_DANGER)
						enemy[n].direct=WAIT;
				enemy[n].skip_count++;
				if (enemy[n].skip_count>=enemy[n].skip){
					enemy[n].skip_count=0;
					enemy_animation(n);
				}
			break;
			
			case ST_DEATH:
				enemy_animation(n);
			break;
				
			default: break;
		}
	}
}

#endif