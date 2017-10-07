#include "Application.h"
#include "Bacteria.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include "math.h"
#include "ModulePowerUps.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

Bacteria::Bacteria(int x, int y, int count) : Enemy(x, y)
{
	sprite_path = App->textures->Load("Assets/Images/Raiden_Spaceship.png");

	explosion.anim.PushBack({ 0, 466, 77, 68 });
	
	
	
	idle.PushBack({ 0, 871,181,497 });
	idle.PushBack({ 181, 871,181,497 });
	idle.PushBack({ 362, 871,181,497 });
	idle.PushBack({ 543, 871,181,497 });

	
	
	animation = &idle;
	idle.speed = 0.1f;
	speed = 3;
	collider = App->collision->AddCollider({ 0, 0, 179, 495 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	
	
}

void Bacteria::Move() {
	
	
position.y += speed;
collider->SetPos(position.x, position.y);
}

void Bacteria::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
	
	
}


void Bacteria::OnCollision(Collider*collider, int num_enemy) {
	
}

void Bacteria::Dead(Collider* shooter, int num_enemy) {
	
	

}