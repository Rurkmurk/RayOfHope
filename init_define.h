#ifndef _INIT_DEFINE
#define _INIT_DEFINE

//map size
#define	HIGH_LEVEL		22
#define	WIDTH_LEVEL		40

/* collizion ************************/
#define COL_UP			#0x1
#define COL_DOWN		#0x2
#define COL_RIGHT 		#0x4
#define COL_LEFT 		#0x8
#define COL_GROUND		#0x10
#define COL_STAIRS	 	#0x20
#define COL_WATER		#0x40
#define COL_WATERPLANT	#0x80
#define COL_LAVA		#0x100
#define COL_NEX_SCR		#0x200
#define COL_PRV_SCR		#0x400
/*******************************************/



/* player status **************************/
#define ST_IDLE			#0x0
#define ST_JUMP			#0x1
#define ST_DOWN			#0x2
#define ST_RIGHT 		#0x4
#define ST_LEFT 		#0x8
#define ST_STAIRS	 	#0x20
#define STAIRS_STAND	#0x40
#define JUMP_LEFT		#0x9
#define JUMP_RIGHT		#0x5
#define DOWN_LEFT		#0xA
#define DOWN_RIGHT		#0x6
#define FIRE_LEFT		#0x12
#define FIRE_RIGHT		#0x11
#define ST_LAVA			#0x80
#define ST_WATER		#0x100
#define ST_DEATH		#0x200
#define ST_WATERPLANT	#0x400
/*******************************************/

/* direct **********************************/
#define UP				#0x1
#define DOWN			#0x2
#define RIGHT 			#0x4
#define LEFT 			#0x8
/*******************************************/

/* tile numbers ****************************/

#define EMPTY			0
#define WALL			1
#define STAIRS			2
#define WATER	 		3
#define WATERPLANT		4
#define DANGER			5
#define LAVA 			6
#define EXIT			7

#define PLAYER 			16
#define OWL				17
#define B_SLIME			18
#define S_SLIME			19

/*****************************/

#define GRAVITY			2

u32 t_terrain=0, t_player=0, t_idle=0, t_enemy=0;

u8 level=0;
u8 screen=0;
u8 map[HIGH_LEVEL][WIDTH_LEVEL];


u8 lava_summ=0;
u8 water_summ=0;

u8 enemy_summ=0;

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
	u16 new_status;
	u16 old_status;
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
	u16 direct;
	u8 h_step;
	u8 skip;
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