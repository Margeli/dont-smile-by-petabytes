#include "Application.h"
#include "Pelito.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePowerUps.h"

#include <stdlib.h>  
#include <time.h>  

Pelito::Pelito(int x, int y) : Enemy(x, y)
{

	//explosion  particle animation (2nd row particle spritesheet.)
	
	explosion.life = 1000;
	explosion.anim.loop = false;

	sprite_path = App->textures->Load("Assets/Images/Raiden_Spaceship.png");
	//GreenShooter Spaceship animations
	if (sprite_path == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}

	idle.PushBack({ 0, 561,179,274 });//box sprite
	idle.PushBack({ 179, 561,179,274 });
	idle.PushBack({ 358, 561,179,274 });
	idle.PushBack({ 537, 561,179,274 });

	idle.speed = 0.1f;//box sprite
	animation = &idle;
	hits_life = 2.0f;// 1.0f

	collider = App->collision->AddCollider({ 0, -100, 149, 280 }, COLLIDER_TYPE::COLLIDER_BOX, (Module*)App->enemies);


	position.x = x;
	position.y = y;
	srand(time(NULL));
}

void Pelito::Move() {	
}

void Pelito::OnCollision(Collider*collider, int num_enemy) {
	//if(collider->type == COLLIDER_PLAYER_SHOT) {
	//	hits_life -= App->player->hit_dmg;
	//}
	////else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
	////	hits_life -= App->player2->hit_dmg;

	////}
	//else if (collider->type == COLLIDER_BOMB|| collider->type == COLLIDER_BOMB2) {
	//	hits_life -= App->player->bomb_dmg;
	//}
	//if (hits_life <= 0) {
	//	int random_number = rand()%100;
	//	//if (random_number <5 ) {//5% of chances to drop dragon
	//	//	App->powerup->AddPowerUp(POWERUP_DRAGON, position.x + 4, position.y + 4);
	//	//}

	//	//else {//95% of chances to drop the medal
	//	//	App->powerup->AddPowerUp(POWERUP_MEDAL,position.x+4, position.y+4);
	//	//}
	//	App->particles->AddParticle(explosion, position.x+2, position.y+2, COLLIDER_EXPLOSION);
	//	delete App->enemies->enemies[num_enemy];
	//	App->enemies->enemies[num_enemy] = nullptr;

	//}

}

void Pelito::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
}