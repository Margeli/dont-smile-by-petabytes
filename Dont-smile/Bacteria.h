#ifndef __BACTERIA_H__
#define __BACTERIA_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class Bacteria : public Enemy
{
private:

	
	Animation idle;
	Animation forward;
	Animation boost;
	Particle color_rotatory_shot;

	int shoot_number;
	float hits_life;
	float speed;
	float increment_y;
	float initial_y;
	int counter_movement;
	bool right;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	//void ShotMovement();
	bool shooting ;
	uint score_points;
	void Dead(Collider* shooter, int num_enemy);

	void OnCollision(Collider* collider, int num_enemy);

	Particle explosion;

	Mix_Chunk* fx_shoot = nullptr;


public:

	Bacteria(int x, int y, int count=3);
	void Move();
	int shoots = 3;



	

};

#endif // __BACTERIA_H__