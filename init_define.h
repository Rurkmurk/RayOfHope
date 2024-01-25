#ifndef _INIT_DEFINE
#define _INIT_DEFINE

//map size
#define	HIGH_LEVEL	23
#define	WIDTH_LEVEL	40

//player collizion
#define IDLE		#0x0
#define UP			#0x1
#define DOWN		#0x2
#define RIGHT 		#0x4
#define LEFT 		#0x8
#define GROUND		#0x10
#define STAIRS	 	#0x20


/* player status **************************/
#define JUMP			UP
#define STAIRS_STAND	#0x40
#define JUMP_LEFT		JUMP+LEFT
#define JUMP_RIGHT		JUMP+RIGHT
#define DOWN_LEFT		DOWN+LEFT
#define DOWN_RIGHT		DOWN+RIGHT
#define FIRE_LEFT		JOY_FIRE+JOY_LEFT
#define FIRE_RIGHT		JOY_FIRE+JOY_RIGHT
#define DEATH			#0x80
/*******************************************/

/* tile numbers ****************************/
#define PLAYER 			240
#define B_SLIME			241
#define S_SLIME			242

#define WATER 			68
#define WATER_WAVE 		250
#define WATER_PLANTS	251
#define LAVA 			252
/*****************************/

#define GRAVITY			2

u32 t_terrain=0, t_player=0, t_idle=0, t_slime=0;

u8 lava_summ=0;
u8 water_summ=0;
u8 n_frame=0;

u8 enemy_summ=0;


static u8 map[HIGH_LEVEL][WIDTH_LEVEL];

struct player
{
	u8 x;	
	u8 y;
	u8 health;
	u16 frame;
	i8 gravity;
	i8 v_speed;
	i8 jump_impulse;
	i8 h_step;
	u8 direct;
	u8 new_status;
	u8 old_status;
	u8 skip;
	i8 deadly_height;
} player;

struct shot
{
	u8 x;	
	u8 y;
	u16 frame;
	u8 direct;
	u8 status;
	u8 dist;
	u8 speed;
} shot;

struct enemy
{
	u8 x;	
	u8 y;
	u8 direct;
	u8 h_step;
	u8 type;
	u8 health;
	u16 frame;
} enemy[10]; //max enemy summ



struct
{
	u8 x[4];	
	u8 y[2];
	u8 tile[8];
}lava[2];

struct
{
	u8 x[4];	
	u8 y[2];
	u8 tile[8];
}water[2];


#endif