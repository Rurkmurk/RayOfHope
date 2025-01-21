#ifndef _SHOT
#define _SHOT

void shot_collision()
{
	static u8 n;
	static u8 sxl, sxr, sy;

	sxl=(shot.x+1)/4;
	sxr=(shot.x+6)/4;
	sy=(shot.y+8)/8;

	if (map[sy][sxl]==WALL||map[sy][sxr]==WALL){
		shot.direct=BOOM;
		sfx_play(SFX_BOOM,8);
	}
	for (n=1;n<=enemy_summ;n++)
		if (enemy[n].direct!=FALSE)
			if (enemy[n].y-shot.y<9&&shot.y-enemy[n].y<3)
				if (shot.x>enemy[n].x-4&&shot.x<enemy[n].x+4)
				{
					shot.direct=BOOM;
					if (enemy[n].type!=ANGRY_PLANT){
						enemy[n].health--;
						sfx_play(SFX_BOOM,8);
					}
					else
						if (enemy[n].direct==ANGRY){
							enemy[n].health--;
							sfx_play(SFX_BOOM,8);
						}
				}
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
				sfx_play(SFX_SHOT,8);
				m=0;
				n=0;
				return;
			}
			
			shot.x+=shot.speed;
			m++;
			shot.frame=SPR_SHOT+1;
			
			shot_collision();
			
			if (shot.x>151||m==shot.dist) {
				n=10;
				shot.direct=BOOM;
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
				sfx_play(SFX_SHOT,8);
				m=0;
				n=0;
				return;
			}
			
			shot.x-=shot.speed;
			m++;
			shot.frame=SPR_SHOT+3;
			
			shot_collision();
			
			if (shot.x<2||m==shot.dist) {
				n=10;
				shot.direct=BOOM;
			}
		break;
		
		case BOOM:
			switch (n)
			{
				case 2:
					shot.frame=SPR_SHOT+5;
				break;
				case 6:
					shot.frame=SPR_SHOT+6;
				break;
				case 10:
					shot.frame=SPRITE_END;
					shot.status=FALSE;
					shot.direct=FALSE;
				break;
			}
			n++;
		break;
	}	
}

#endif