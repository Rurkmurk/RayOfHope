#ifndef __INIT
#define __INIT

#define	HIGH_LEVEL	25
#define	WIDTH_LEVEL	40

#define RIGHT 		#0x4
#define LEFT 		#0x8
#define JUMP		#0x1
#define JUMP_RIGHT 	#0x5
#define JUMP_LEFT 	#0x9


#define PLAYER 		240
#define WATER_WAVE 	241
#define WATER 		52
#define WATER_PLANTS 242
#define LAVA 		243

#define GRAVITY		4

u32 t_terrain=0, t_player=0, t_idle=0;
u8 lava_summ=0;
u8 water_summ=0;
u8 n_frame=0;


static u8 map[WIDTH_LEVEL][HIGH_LEVEL];

struct
{
	u8 x;	
	u8 y;
	u8 healt;
	u8 frame;
	u8 gravity;
	i8 h_velocity;
	u8 new_direct;
	u8 old_direct;
}player;

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