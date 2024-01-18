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
	static u8 m, n;
	
	if (!s.direct)
		return;
	
	switch (s.direct){
		case RIGHT:
			if (s.status!=RIGHT){ 
				s.status=RIGHT;
				s.x=p.x+4;
				s.y=p.y;
				s.frame=SPR_SHOT+0;
				m=0;
				n=0;
				return;
			}
			
			if (!shot_collision()&&(m<s.dist)){
				s.x+=s.speed;
				s.frame=SPR_SHOT+1;
				m++;
				return;
			}
		break;

		case LEFT:
			if (s.status!=LEFT){ 
				s.status=LEFT;
				s.x=p.x-4;
				s.y=p.y;
				s.frame=SPR_SHOT+4;
				m=0;
				n=0;
				return;
			}
			
			if (!shot_collision()&&(m<s.dist)){
				s.x-=s.speed;
				s.frame=SPR_SHOT+5;
				m++;
				return;
			}
		break;
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
	}
}

#endif