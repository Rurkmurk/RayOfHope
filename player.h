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
	if ((map[pyu][pxl]>31)&&(map[pyu][pxr]>31))
		collision^=UP;
	//down
	if ((map[py_ground][pxl]>47)||(map[py_ground][pxc]>47)||(map[py_ground][pxr]>47))
		collision^=DOWN;
	//right
	if (map[pyu][pxr]>47||map[pyc][pxr]>47||map[pyd][pxr]>47)
		collision^=RIGHT;
	//left
	if (map[pyu][pxl]>47||map[pyc][pxl]>47||map[pyd][pxl]>47)
		collision^=LEFT;
	//ground
	if ((map[py_ground][pxl]>95)&&(map[py_ground][pxl]<239)||(map[py_ground][pxr]>95)&&(map[py_ground][pxr]<239))
		collision^=GROUND;
	//stairs
	if ((map[py_stairs][pxl]>31)&&(map[py_stairs][pxl]<48)&&
		(map[py_stairs][pxr]>31)&&(map[py_stairs][pxr]<48))
		collision^=STAIRS;
	//lava
	if (map[py_ground][pxc]==LAVA)
		collision^=#0x80;
	//water_wave
	if ((map[py_ground][pxl]==WATER_WAVE)&&(map[py_ground][pxr]==WATER_WAVE))
		collision^=DOWN;
	//water
	if (map[py_ground][pxc]==WATER)
		collision^=#0x100;
	//water plant
	if (map[py_ground][pxc]==WATER_PLANTS)
		collision^=#0x200;
	
	return (collision);
}



void player_logic()
{
	i8 j;
	
	u16 p_collision;
	
	if (!player.health) {
		if ((player.old_status!=WATER)&&(player.old_status!=LAVA)) player.new_status=DEATH;
		return;
	}
	
	p_collision=player_collision();
	
	player.h_step=1;
	
	//idle
	if (!player.direct&&player.new_status!=JUMP&&player.old_status!=STAIRS)
		player.new_status=IDLE;
	
	//stairs stand
	if (!player.direct&&(p_collision&STAIRS)==STAIRS)
		player.new_status=STAIRS_STAND;
	
	//water 
	if ((p_collision&#0x100)==#0x100) {
		player.y++;
		player.new_status=WATER;
		return;
	}
	if ((p_collision&#0x200)==#0x200) {
		player.y+=4;
		player.health=0;
		return;
	}

	//lava
	if ((p_collision&#0x80)==#0x80) {
		player.y+=7;
		player.new_status=LAVA;
		player.health=0;
		return;
	}
	
	//up
	if ((player.direct&JOY_UP)==JOY_UP) {
		if ((p_collision&STAIRS)==STAIRS) {
			player.y-=2;
			player.new_status=STAIRS;
		}
		if ((p_collision&GROUND)==GROUND&&player.new_status!=STAIRS) {
			player.v_speed=player.jump_impulse-GRAVITY;
			player.new_status=JUMP;
		}
	}
	
	if (player.v_speed>0) {
		player.v_speed--;
		for (j=0;j<=player.v_speed;j++) {
			if ((player_collision()&UP)!=UP) player.y--;
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
	if ((player.direct&JOY_RIGHT)==JOY_RIGHT&&(p_collision&RIGHT)!=RIGHT&&(player.direct&JOY_DOWN)!=JOY_DOWN) {
		player.x+=player.h_step;
		player.new_status=RIGHT;
	}
	if ((player_collision()&RIGHT)==RIGHT)
		player.x-=player.h_step;
	
	//left
	if ((player.direct&JOY_LEFT)==JOY_LEFT&&(p_collision&LEFT)!=LEFT&&(player.direct&JOY_DOWN)!=JOY_DOWN) {
		player.x-=player.h_step;
		player.new_status=LEFT;
	}
	if ((player_collision()&LEFT)==LEFT)
		player.x+=player.h_step;
	
	
	
	//down stairs
	if ((player.direct&JOY_DOWN)==JOY_DOWN) {
		for (j=0;j<2;j++) {
			if ((p_collision&STAIRS)==STAIRS&&(player_collision()&GROUND)!=GROUND) {
				player.y+=1;
				player.new_status=STAIRS;
			}
			else break;
		}
	}
	
	// drop down
	if ((p_collision&DOWN)!=DOWN&&player.v_speed<=0) {
		player.v_speed-=GRAVITY;
		for (j=0;j>player.v_speed;j--) {
			if ((player_collision()&DOWN)!=DOWN&&(p_collision&STAIRS)!=STAIRS) {
				player.new_status=DOWN;
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
	if ((player.direct&JOY_DOWN)==JOY_DOWN&&(player_collision()&GROUND)==GROUND) {
		if (player.old_status==LEFT)
			player.new_status=DOWN_LEFT;
		if (player.old_status==RIGHT||!player.old_status)
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

}

void player_animation()
{
	switch (player.new_status) {
		
		case DEATH:
			player.frame=27;
			break;
		
		case WATER:
			player.frame=28;
			player.old_status=WATER;
			break;
			
		case LAVA:
			player.frame=31;
			player.old_status=LAVA;
			break;
		
		case RIGHT:
			if ((player.old_status)!=RIGHT) {
				player.old_status=RIGHT;
				player.frame=0;
			}
			else {
				player.frame=player.frame<7?++player.frame:0;
			}
			break;
		
		case LEFT:
			if ((player.old_status)!=LEFT) {
				player.old_status=LEFT;
				player.frame=8;
			}
			else {
				player.frame=player.frame<15?++player.frame:8;
			}
			break;
			
		case JUMP:
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
			
		case STAIRS:
			if ((player.old_status)!=STAIRS) {
				player.old_status=STAIRS;
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
			if (player.new_status==IDLE&&(player_collision()&STAIRS)!=STAIRS&&(player.health!=0)) {
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
					player.old_status=RIGHT;
				if (player.old_status==DOWN_LEFT)
					player.old_status=LEFT;
			}
	}
}

#endif