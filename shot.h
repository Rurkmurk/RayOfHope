#ifndef _SHOT
#define _SHOT

u8 shot_collision()
{
	u8 collision=0;
	u8 sxc, syc;
	
	sxc=(s.x+3)/4;

	syc=(s.y+8)/8;

	if (map[syc][sxc]>47)
		collision=TRUE;
	
	return (collision);
}

void shot_logic()
{
	static u8 n;
	
	switch (s.direct){
		case RIGHT:
			if (s.status!=RIGHT){ 
				s.status=RIGHT;
				s.x=p.x+4;
				s.y=p.y;
				s.frame=SPR_SHOT+0;
				s.n++;
				n=0;
				return;
			}
			
			if (!shot_collision()&&(s.n<50)){
				s.x++;
				s.frame=SPR_SHOT+1;
				s.n++;
				return;
			}
			
			if (n<6){
			s.frame=SPR_SHOT+2;
			n++;
			}
			else if (n>=6&&n<10){
			s.frame=SPR_SHOT+3;
			n++;
			}
			else {
			s.frame=SPRITE_END;
			s.status=FALSE;
			s.direct=FALSE;
			s.n=0;
			}
		break;

		case LEFT:
			if (s.status!=LEFT){ 
				s.status=LEFT;
				s.x=p.x-4;
				s.y=p.y;
				s.frame=SPR_SHOT+4;
				s.n++;
				n=0;
				return;
			}
			
			if (!shot_collision()&&(s.n<50)){
				s.x--;
				s.frame=SPR_SHOT+5;
				s.n++;
				return;
			}
			
			if (n<6){
			s.frame=SPR_SHOT+6;
			n++;
			}
			else if (n>=6&&n<10){
			s.frame=SPR_SHOT+7;
			n++;
			}
			else {
			s.frame=SPRITE_END;
			s.status=FALSE;
			s.direct=FALSE;
			s.n=0;
			}
		break;
	}
}


#endif