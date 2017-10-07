#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1();
	~ModuleLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();



public:
	
	SDL_Texture* graphics = nullptr;
	Mix_Music* music_lvl1 = nullptr;
	Mix_Music* boss_music = nullptr;
	SDL_Rect foreground;
	SDL_Rect background;
	SDL_Rect ship_launcher;
	bool fading = false;

	void SinusBacteriaSpawning(uint win_chain, float pos_x, float pos_y, int spawn_margin );

	bool jumped = false;
	int spawn_distance;

	Uint32 last_spawn_sinus=0;
	Uint32 last_spawn_bacteria = 0;
	Uint32 counter_spawn_timer;
	Uint32 difficulty_time;
	
	float foreground_pos;
	bool first_animation=false;
	bool forward;

	int counter_sc_spd= 0;
	int max_sc_sp = 1;
	float scroll_speed = 1;
	double inferior_limit = 200;

	void scroll();


	
};

#endif // __MODULELEVEL1_H__