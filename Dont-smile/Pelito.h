#ifndef __PELITO_H__
#define __PELITO_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class Pelito : public Enemy
{
private:


	Animation idle;
	Particle explosion;	
	Mix_Chunk* fx_shoot = nullptr;
	void OnCollision(Collider* collider, int num_enemy);
	
	float hits_life;
	int shoot_number = 0;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	
public:

	Pelito(int x, int y);
	void Move();




};

#endif// __PELITO_H__