#ifndef _INIT_DEFINE
#define _INIT_DEFINE

#define	HIGH_LEVEL	25
#define	WIDTH_LEVEL	40

#define DOWN		#0x2
#define RIGHT 		#0x4
#define LEFT 		#0x8
#define UP			#0x1
#define STAIRS_UP 	#0x20
#define STAIRS_DOWN	#0x40
#define GROUND		#0x10


#define PLAYER 		240
#define WATER_WAVE 	241
#define WATER 		52
#define WATER_PLANTS 242
#define LAVA 		243

#define GRAVITY		3

u32 t_terrain=0, t_player=0, t_idle=0;
u8 lava_summ=0;
u8 water_summ=0;
u8 n_frame=0;


static u8 map[HIGH_LEVEL][WIDTH_LEVEL];

struct player
{
	u8 x;	
	u8 y;
	u8 healt;
	u8 frame;
	i8 gravity;
	i8 v_speed;
	i8 jump_impulse;
	i8 h_speed;
	u8 new_direct;
	u8 old_direct;
} p;


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