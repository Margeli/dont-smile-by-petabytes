#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"

#include "ModuleParticles.h"
#include "GreenShooterSpaceship.h"
#include "LightShooterSpaceship.h"

#define MAX_ENEMIES 100


enum ENEMY_TYPES
{
	NO_TYPE,
	BACTERIA,
	PELITO,
	SINUS,
	GREENSHOOTER_SPACESHIP,
	LIGHTSHOOTER_SPACESHIP,
	MINE,
	HEAVY_SHOOTER,
	TANK,
	CANNON_TANK,
	MEGA_TANK,
	STATIC_CANNON,
	BOSS,
	
	BOSS_CANNON,
	BOSS_CANNON2,
	
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y, shots;
	bool right;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, int shots = 0, bool right = false);

	Enemy* enemies[MAX_ENEMIES];

	SDL_Texture* sprite_path_opt;

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__
