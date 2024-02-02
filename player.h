#ifndef _PLAYER
#define _PLAYER

void control_player()
{
	u8 key;
	u8 dx=0, dy=0, fire=0;
	key=joystick();
	if(key&JOY_UP) {
		dy=JOY_UP;
		}
	if(key&JOY_RIGHT) {
		dx=JOY_RIGHT;
	}
	if(key&JOY_LEFT) {
		dx=JOY_LEFT;
	}
	if(key&JOY_DOWN) {
		dy=JOY_DOWN;
	}
	if(key&JOY_FIRE) {
		fire=JOY_FIRE;
	}
	if(key!=FALSE) t_idle=time();
	player.direct=dx+dy+fire;
}


u16 player_collision()
{
	static u16 collision;
	
	u8 pxl, pxc, pxr, pyu, pyc, pyd, py_ground, py_stairs;
	
	collision=0;
	
	pxl=(player.x+2)/4;
	pxc=(player.x+3)/4;
	pxr=(player.x+5)/4;
	
	pyu=(player.y)/8;
	pyc=(player.y+7)/8;
	pyd=(player.y+15)/8;
	
	py_stairs=(player.y+10)/8;
	py_ground=(player.y+16)/8;

	//up
	if ((map[pyu][pxl]!=0)&&(map[pyu][pxr]!=0))
		collision^=COL_UP;
	//down
	if ((map[py_ground][pxl]==WALL)||(map[py_ground][pxc]==WALL)||(map[py_ground][pxr]==WALL))
		collision^=COL_DOWN;
	//right
	if (map[pyu][pxr]==WALL||map[pyc][pxr]==WALL||map[pyd][pxr]==WALL)
		collision^=COL_RIGHT;
	//left
	if ((map[pyu][pxl]==WALL)||(map[pyc][pxl]==WALL)||(map[pyd][pxl]==WALL))
		collision^=COL_LEFT;
	//ground
	if ((map[py_ground][pxl]==WALL)||(map[py_ground][pxr]==WALL))
		collision^=COL_GROUND;
	//stairs
	if (map[py_stairs][pxl]==STAIRS&&map[py_stairs][pxr]==STAIRS)
		collision^=COL_STAIRS;
	//lava
	if (map[py_ground][pxc]==6)
		collision^=COL_LAVA;
	//water
	if (map[py_ground][pxl]==WATER&&map[py_ground][pxr]==WATER)
		collision^=COL_WATER;
	//water plant
	if (map[py_ground][pxc]==WATERPLANT)
		collision^=COL_WATERPLANT;
	
	//screen right
	if (pxc==39)
		collision^=COL_NEX_SCR;
	
	//screen left
	if (pxc==0)
		collision^=COL_PRV_SCR;
	return (collision);
}



void player_logic()
{
	i8 j;
	
	static u8 trig_jump;
	
	u16 p_collision;
	
	if (!player.health) {
		if ((player.old_status!=ST_WATER)&&(player.old_status!=ST_LAVA)) player.new_status=ST_DEATH;
		return;
	}
	
	p_collision=player_collision();
	
	player.h_step=1;
	
	//idle
	if (!player.direct&&player.new_status!=ST_JUMP&&player.old_status!=ST_STAIRS)
		player.new_status=ST_IDLE;
	 
	//stairs stand
	if (!player.direct&&(p_collision&COL_STAIRS)==COL_STAIRS)
		player.new_status=STAIRS_STAND;
	
	//water 
	if ((p_collision&COL_WATER)==COL_WATER) {
		player.y++;
		player.new_status=ST_WATER;
		return;
	}
	if ((p_collision&COL_WATERPLANT)==COL_WATERPLANT) {
		player.y+=4;
		player.health=0;
		return;
	}

	//lava
	if ((p_collision&COL_LAVA)==COL_LAVA) {
		player.y+=7;
		player.new_status=ST_LAVA;
		player.health=0;
		return;
	}
	
	//up
	if ((player.direct&JOY_UP)==JOY_UP) {
		if ((p_collision&COL_STAIRS)==COL_STAIRS) {
			player.y-=2;
			player.new_status=ST_STAIRS;
		}
		if ((p_collision&COL_GROUND)==COL_GROUND&&player.new_status!=ST_STAIRS&&trig_jump) {
			player.v_speed=player.jump_impulse-GRAVITY;
			player.new_status=ST_JUMP;
			trig_jump=FALSE;
		}
	}
	
	if (player.v_speed>0) {
		player.v_speed--;
		for (j=0;j<=player.v_speed;j++) {
			if ((player_collision()&COL_UP)!=COL_UP) player.y--;
			else {
				player.v_speed=0;
				break;
			}
		}
	}
	
	//left jump
	if (player.direct==JOY_LEFT+JOY_UP){
		player.new_status=JUMP_LEFT;
		player.h_step=2;
	}
	//right jump
	if (player.direct==JOY_RIGHT+JOY_UP){
		player.new_status=JUMP_RIGHT;
		player.h_step=2; 
	}
	
	// right 
	if ((player.direct&JOY_RIGHT)==JOY_RIGHT&&(p_collision&COL_RIGHT)!=COL_RIGHT&&(player.direct&JOY_DOWN)!=JOY_DOWN) {
		player.x+=player.h_step;
		player.new_status=ST_RIGHT;
	}
	if ((player_collision()&COL_RIGHT)==COL_RIGHT)
		player.x-=player.h_step;
	if ((player_collision()&COL_NEX_SCR)==COL_NEX_SCR)
		nex_screen();

	
	//left
	if ((player.direct&JOY_LEFT)==JOY_LEFT&&(p_collision&COL_LEFT)!=COL_LEFT&&(player.direct&JOY_DOWN)!=JOY_DOWN) {
		player.x-=player.h_step;
		player.new_status=ST_LEFT;
	}
	if ((player_collision()&COL_LEFT)==COL_LEFT)
		player.x+=player.h_step;
	if ((player_collision()&COL_PRV_SCR)==COL_PRV_SCR)
		prv_screen();
	
	
	//down stairs
	if ((player.direct&JOY_DOWN)==JOY_DOWN) {
		for (j=0;j<2;j++) {
			if ((p_collision&COL_STAIRS)==COL_STAIRS&&(player_collision()&COL_GROUND)!=COL_GROUND) {
				player.y+=1;
				player.new_status=ST_STAIRS;
			}
			else break;
		}
	}
	
	// drop down
	if ((p_collision&COL_DOWN)!=COL_DOWN&&player.v_speed<=0) {
		player.v_speed-=GRAVITY;
		for (j=0;j>player.v_speed;j--) {
			if ((player_collision()&COL_DOWN)!=COL_DOWN&&(p_collision&COL_STAIRS)!=COL_STAIRS) {
				player.new_status=ST_DOWN;
				player.y++;
			}
			else {
				if (player.v_speed<player.deadly_height)
					player.health-=5;

				player.v_speed=0;
				break;
			}
		}
	}
	
	// fire
	if ((player.direct&JOY_DOWN)==JOY_DOWN&&(player_collision()&COL_GROUND)==COL_GROUND) {
		if (player.old_status==ST_LEFT)
			player.new_status=DOWN_LEFT;
		if (player.old_status==ST_RIGHT||!player.old_status)
			player.new_status=DOWN_RIGHT;
	}	

	if (player.old_status==DOWN_RIGHT&&(player.direct&(JOY_LEFT+JOY_DOWN))==(JOY_LEFT+JOY_DOWN)) {
		player.new_status=DOWN_LEFT;
	}	
	
	if (player.old_status==DOWN_LEFT&&(player.direct&(JOY_RIGHT+JOY_DOWN))==(JOY_RIGHT+JOY_DOWN)) {
		player.new_status=DOWN_RIGHT;
	}	
	
	if (player.old_status==DOWN_LEFT&&(player.direct&JOY_FIRE)==JOY_FIRE) {
		shot.direct=LEFT;
	}	
	
	if (player.old_status==DOWN_RIGHT&&(player.direct&JOY_FIRE)==JOY_FIRE) {
		shot.direct=RIGHT;
	}	

	if ((player.direct&JOY_UP)!=JOY_UP)
		trig_jump=TRUE;

}

void player_animation()
{
	switch (player.new_status) {
		
		case ST_DEATH:
			player.frame=27;
			break;
		
		case ST_WATER:
			player.frame=28;
			player.old_status=ST_WATER;
			break;
			
		case ST_LAVA:
			player.frame=31;
			player.old_status=ST_LAVA;
			break;
		
		case ST_RIGHT:
			if ((player.old_status)!=ST_RIGHT) {
				player.old_status=ST_RIGHT;
				player.frame=0;
			}
			else {
				player.frame=player.frame<7?++player.frame:0;
			}
			break;
		
		case ST_LEFT:
			if ((player.old_status)!=ST_LEFT) {
				player.old_status=ST_LEFT;
				player.frame=8;
			}
			else {
				player.frame=player.frame<15?++player.frame:8;
			}
			break;
			
		case ST_JUMP:
			player.frame=22;
			break;
			
		case JUMP_LEFT:
			player.old_status=JUMP_LEFT;
			player.frame=19;
			break;
			
		case JUMP_RIGHT:
			player.old_status=JUMP_RIGHT;
			player.frame=18;
			break;
			
		case ST_STAIRS:
			if ((player.old_status)!=ST_STAIRS) {
				player.old_status=ST_STAIRS;
				player.frame=23;
			}
			else {
				player.frame=player.frame<26?++player.frame:23;
			}
			break;
			
		case STAIRS_STAND:
			player.frame=23;
			player.old_status=STAIRS_STAND;
			break;
			
		case DOWN_LEFT:
			player.frame=17;
			player.old_status=DOWN_LEFT;
			break;
		
		case DOWN_RIGHT:
			player.frame=16;
			player.old_status=DOWN_RIGHT;
			break;

		default:
			if (player.new_status==ST_IDLE&&(player_collision()&COL_STAIRS)!=COL_STAIRS&&
			(player.health!=0)) {
				if (t_idle+200>time())
					player.frame=20;
				else if (t_idle+210>time())
					player.frame=22;
				else if (t_idle+230>time())
					player.frame=21;
				else if (t_idle+240>time())
					player.frame=22;
				else if (t_idle+260>time())
					player.frame=21;
				else t_idle=time();
				if (player.old_status==DOWN_RIGHT)
					player.old_status=ST_RIGHT;
				if (player.old_status==DOWN_LEFT)
					player.old_status=ST_LEFT;
			}
	}
}

#endif