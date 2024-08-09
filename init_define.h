#ifndef _INIT_DEFINE
#define _INIT_DEFINE

//map size
#define	HIGH_LEVEL		22
#define	WIDTH_LEVEL		40

#define PAGE_GFX		60
#define PAGE_MAP		61
#define PAGE_GFX_TMP	62
#define PAGE_MAP_TMP	63

/* collizion ************************/
#define COL_UP			#0x1
#define COL_DOWN		#0x2
#define COL_RIGHT 		#0x4
#define COL_LEFT 		#0x8
#define COL_GROUND		#0x10
#define COL_STAIRS	 	#0x20
#define COL_WATER		#0x40
#define COL_DANGER		#0x80
#define COL_NXT_SCR		#0x100
#define COL_PRV_SCR		#0x200
#define COL_DOWN_SCR	#0x400
#define COL_UP_SCR		#0x800
#define COL_ENEMY_LEFT	#0x1000
#define COL_ENEMY_RIGHT	#0x2000
#define COL_ENEMY_CENTR	#0x4000
#define COL_STALACT		#0x8000

/*******************************************/



/* player status **************************/

#define ST_IDLE			#0x0
#define ST_JUMP			#0x1
#define ST_DOWN_PUSH	#0x2
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
//#define ST_WATERPLANT	#0x400
/*******************************************/

/* direct **********************************/
#define UP				#0x1
#define DOWN			#0x2
#define RIGHT 			#0x4
#define LEFT 			#0x8
#define WAIT			#0x10
#define ANGRY			#0x20
/*******************************************/

/* tile numbers ****************************/

#define EMPTY			0
#define WALL			1
#define STAIRS			2
#define WATER	 		3
#define ACID			4
#define DANGER			5
#define STALACT 		6
#define EXIT			7
#define HEALTH_FULL		8
#define HEALTH			9
#define AMMO_FULL		10
#define AMMO			11
#define LIGHT_1			12
#define LIGHT_2			13


#define PLAYER 			16

#define OWL				17
#define B_SLIME			18
#define S_SLIME			19
#define ICE_SPIKE		20
#define BLOCK			21
#define SNOW_JUMP		22
#define MINE_JUMP		23
#define ANGRY_PLANT_R	24
#define ANGRY_PLANT_L	25

/*****************************/

#define GRAVITY			2
#define AMMO_MAX		10
#define HEALTH_MAX		10
#define DEATH_SPEED		7

static u32 t_player, t_idle, t_death;

static u8 level;
static u8 level_size;
static u8 level_back;
static u8 level_tile;
static u8 screen;
static u8 map[HIGH_LEVEL][WIDTH_LEVEL];


static u8 acid_summ;
static u8 water_summ;
static u8 waterplant_summ;
static u8 enemy_summ;
static u8 light_summ;


static struct player
{
	u8 x;	
	u8 y;
	u8 health;
	u8 life;
	u16 frame;
	i8 gravity;
	i8 v_speed;
	i8 jump_impulse;
	i8 h_step;
	u8 direct;
	u16 status;
	u16 enemy_collision;
	u8 skip;
	i8 danger_height;
	i8 death_height;
	u8 ammo;
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
	u8 x_start;
	u8 y_start;
	u16 direct;
	u8 h_step;
	u8 skip;
	u8 skip_count;
	u8 type;
	u8 health;
	u16 frame;
} enemy[10]; //max enemy summ

struct water
{
	u8 x;	
	u8 y;
	u16 frame;
}water[10];

struct waterplant
{
	u8 x;	
	u8 y;
	u16 frame;
}waterplant[10];

struct light
{
	u8 x;
	u8 y;
	u8 n_spr;
	u16 frame;
}light[5];

static struct tmp_save
{
	u8 screen;
	u8 health;
	u8 ammo;
	u8 x;
	u8 y;
}tmp_save;	

#endif