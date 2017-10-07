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
	sprite_path = App->textures->Load("Assets/Images/Bonus_Spaceship.png");

	explosion.anim.PushBack({ 0, 466, 77, 68 });
	
	
	
	idle.PushBack({ 45, 29,64,65 });
	idle.PushBack({ 114,29,64,65 });
	idle.PushBack({ 183,29,64,65 });
	idle.PushBack({ 252,29,64,65 });
	idle.PushBack({ 318,29,64,65 });
	idle.PushBack({ 252,29,64,65 });
	idle.PushBack({ 183,29,64,65 });
	idle.PushBack({ 114,29,64,65 });
	idle.PushBack({ 45, 29,64,65 });

	
	
	animation = &forward;
	idle.speed = 0.03f;
	speed = 3;
	collider = App->collision->AddCollider({ 0, 0, 64, 65 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	
	
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