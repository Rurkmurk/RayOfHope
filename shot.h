#ifndef _SHOT
#define _SHOT



void shot_logic()
{
	if (s.direct==RIGHT){
		if (s.status!=RIGHT){ 
			s.status=RIGHT;
			s.x=p.x+4;
			s.y=p.y;
			s.frame=SPR_SHOT+0;
			s.n++;
		}
		if (s.status==RIGHT){
			if (s.n<50){
				s.x++;
				s.frame=SPR_SHOT+1;
				s.n++;
			}
			else if (s.n>=50&&s.n<60){
				s.frame=SPR_SHOT+2;
				s.n++;
			}
			else if (s.n>=60&&s.n<65){
				s.frame=SPR_SHOT+3;
				s.n++;
			}
			else {
				s.frame=SPRITE_END;
				s.status=FALSE;
				s.direct=FALSE;
				s.n=0;
			}
		}
	}
	if (s.direct==LEFT){
		if (s.status!=LEFT){ 
			s.status=LEFT;
			s.x=p.x-4;
			s.y=p.y;
			s.frame=SPR_SHOT+4;
			s.n++;
		}
		if (s.status==LEFT){
			if (s.n<50){
				s.x--;
				s.frame=SPR_SHOT+5;
				s.n++;
			}
			else if (s.n>=50&&s.n<60){
				s.frame=SPR_SHOT+6;
				s.n++;
			}
			else if (s.n>=60&&s.n<65){
				s.frame=SPR_SHOT+7;
				s.n++;
			}
			else {
				s.frame=SPRITE_END;
				s.status=FALSE;
				s.direct=FALSE;
				s.n=0;
			}
		}
	}
}








#endif