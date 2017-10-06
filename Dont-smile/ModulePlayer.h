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
	Particle left_basic_shot;
	Particle right_basic_shot;
	Particle triple_shot;
	Particle left_triple_shot;
	Particle right_triple_shot;
	Particle ext_left_triple_shot;
	Particle ext_right_triple_shot;
	Particle bomb;

	Particle misile_left;
	Particle misile_mid;
	Particle misile_right;

	Particle laser_shot;
	Particle big_laser_shot;


public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;

	Animation idle;

	Particle dead_explosion;
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
	Uint32 bomb_thrown;
	Uint32 bomb_life;
	Uint32 last_bomb;
	int spaceship_speed;

	char score_text[10];
	char high_score_text[10];
	char *user_interface;
	char *godmode_activated;

	int red_font_score = 0;
	int yellow_font_score = 0;

	uint Red_Powerup_Lvl;
	uint Blue_Powerup_Lvl;
	uint M_Powerup_Lvl;

	const int camera_speed_module = 4;

	Mix_Chunk* fx_shoot = nullptr;
	//////

	vec_2d speed_vec = {0, 0};

	void updatePosition();

	const float acceleration = 0.5f;
	const float max_speed = 5.0f;
	const float friction = 0.1f;

	int counter = 0;
	int max = 2;
	
	
};

#endif