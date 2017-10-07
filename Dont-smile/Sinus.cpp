#include "Application.h"
#include "Sinus.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


Sinus::Sinus(int x, int y, int shoot_num) : Enemy(x, y)
{
	

	if (App->enemies->sprite_path_opt == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}
	sprite_path = App->enemies->sprite_path_opt;

	idle.PushBack({ 9,232,87,86 });
	idle.PushBack({ 97,232,87,86 });
	idle.PushBack({ 183,232,87,86 });
	idle.PushBack({ 269,232,87,86 });

	idle.speed = 0.1f;


	collider = App->collision->AddCollider({ 0, 0, 85, 83 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	
}


void Sinus::Move() {
	
	
	//speed = 3.0f;
	//if (to_negative) {
	//	iterator -= 0.05f;
	//	if (iterator == -1.0f) {
	//		to_negative = false;
	//	}
	//
	//}
	//else {
	//	iterator += 0.1f;
	//	if (iterator == 1.0f) {
	//		to_negative = true;
	//	}
	//
	//}
	//animation = &idle;
	//	position.y += speed;
	//	position.x +=10* sin(iterator);

}


void Sinus::OnCollision(Collider*collider, int num_enemy) {
	
	

}


void Sinus::Dead(Collider* shooter, int num_enemy) {

	
	delete App->enemies->enemies[num_enemy];
	App->enemies->enemies[num_enemy] = nullptr;

}



void Sinus::ShotVector(Particle& shot, iPoint velocity_vector, fPoint shot_initial_pos) {

	/*shot.speed.x = velocity_vector.x;
	shot.speed.y = velocity_vector.y;
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);*/

}

void Sinus::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
}