#ifndef _SHOT
#define _SHOT

u8 shot_collision()
{
	u8 n;
	u8 collision=FALSE;
	static u8 shot_enemy;
	u8 sxl, sxr, sy;
	
	sxl=(shot.x+1)/4;
	sxr=(shot.x+6)/4;
	sy=(shot.y+8)/8;

	if (map[sy][sxl]==WALL||map[sy][sxr]==WALL)
		collision=TRUE;
	
	for (n=1;n<=enemy_summ;n++)
		if (shot.y==enemy[n].y)
			if (shot.x>enemy[n].x-2&&shot.x<enemy[n].x+4) {
				collision=TRUE;
				if (shot.frame==SPR_SHOT+4)
					enemy[n].health--;
			}
	
	return (collision);
}

void shot_logic()
{
	static u8 m, n;
	
	if (!shot.direct)
		return;
	
	switch (shot.direct){
		case RIGHT:
			if (shot.status!=RIGHT){ 
				shot.status=RIGHT;
				player.ammo--;
				update_hud();
				shot.x=player.x+4;
				shot.y=player.y;
				shot.frame=SPR_SHOT+0;
				m=0;
				n=0;
				return;
			}
			
			if (!shot_collision()&&(m<shot.dist)){
				shot.x+=shot.speed;
				if (shot.x>151) {
					m=shot.dist;
					n=10;
					return;
				}
				shot.frame=SPR_SHOT+1;
				m++;
				return;
			}
		break;

		case LEFT:
			if (shot.status!=LEFT){ 
				shot.status=LEFT;
				player.ammo--;
				update_hud();
				shot.x=player.x-4;
				shot.y=player.y;
				shot.frame=SPR_SHOT+2;
				m=0;
				n=0;
				return;
			}
			
			if (!shot_collision()&&(m<shot.dist)){
				shot.x-=shot.speed;
				if (shot.x<2) {
					m=shot.dist;
					n=10;
					return;
				}
				shot.frame=SPR_SHOT+3;
				m++;
				return;
			}
		break;
	}	
	
	if (n==0){
		shot.frame=SPR_SHOT+4;
		n++;
		}
	else if (n>0&&n<6){
		shot.frame=SPR_SHOT+5;
		n++;
		}
	else if (n>=6&&n<10){
		shot.frame=SPR_SHOT+6;
		n++;
		}
	else {
		shot.frame=SPRITE_END;
		shot.status=FALSE;
		shot.direct=FALSE;
		}
}

#endif