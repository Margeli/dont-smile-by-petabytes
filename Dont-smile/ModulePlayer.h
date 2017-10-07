#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Collider;

struct vec_2d {
	float x;
	float y;
};

struct particle {
	vec_2d position{ 0.0f,0.0f };
	SDL_Texture* graphs = nullptr;
	double scale = 1.0f;
	SDL_Rect section = { 390,240, 47,47 };
	int initial_width = 47;
	int initial_height = 47;
	int initial_x = 390;
	int initial_y = 240;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void Dead();

public:

	Particle basic_shot;
	

	Particle misile_left;
	Particle misile_mid;
	Particle misile_right;

	Particle laser_shot;
	Particle big_laser_shot;


public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;

	Animation idle;
	Animation splash;
	Animation dead;

	
	Particle bomb_explosion;
	fPoint position;
	fPoint saved_position;


	


	Collider* spaceship_collider;
	bool destroyed = false;
	bool player1 = false;
	float hit_dmg;
	float bomb_dmg;
	bool godmode = false;
	uint high_score = 0;
	uint score = 0;
	int total_bombs;
	Uint32 born;
	Uint32 estela_time;
	Uint32 last_bomb;
	int spaceship_speed;

	char score_text[10];
	char high_score_text[10];
	char *user_interface;
	char *godmode_activated;

	int 
_score = 0;
	int yellow_font_score = 0;

	uint Red_Powerup_Lvl;
	uint Blue_Powerup_Lvl;
	uint M_Powerup_Lvl;

	const int camera_speed_module = 4;

	Mix_Chunk* fx_shoot = nullptr;
	//////

	uint win_chain;

	Particle estela;


	vec_2d acceleration_vec = {0, 0};
	vec_2d speed_vec = { 0,0 };

	void check_map_limits();

	void move_camera_with_player();

	void updatePosition();

	void applyInertia();

	const float acceleration = 0.5f;
	const float max_speed = 5.0f;
	const float friction = 0.1f;

	const int map_margin = 300;

	int counter = 0;
	int max = 2;

	
	
	
};

#endif