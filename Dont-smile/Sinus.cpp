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
	
	sprite_path = App->textures->Load("Assets/Images/Raiden_Spaceship.png");

	if (sprite_path == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}

	idle.PushBack({ 13,205,113,110 });
	

	idle.speed = 0.3f;


	collider = App->collision->AddCollider({ 0, 0, 110, 105 }, COLLIDER_TYPE::COLLIDER_BOX, (Module*)App->enemies);

	
}

void Sinus::Move() {
	speed = 3.0f;
	if (to_negative) {
		iterator -= 0.05f;
		if (iterator == -1.0f) {
			to_negative = false;
		}
	
	}
	else {
		iterator += 0.1f;
		if (iterator == 1.0f) {
			to_negative = true;
		}
	
	}
	animation = &idle;
		position.y += speed;
		position.x +=10* sin(iterator);

}


void Sinus::OnCollision(Collider*collider, int num_enemy) {
	
	

}


void Sinus::Dead(Collider* shooter, int num_enemy) {

	if (shooter->type == COLLIDER_PLAYER_SHOT || shooter->type == COLLIDER_BOMB) {
		App->player->score += score_points;
	}
	/*else if (shooter->type == COLLIDER_PLAYER2_SHOT || shooter->type == COLLIDER_BOMB2) {
		App->player2->score += score_points;
	}
	ShotVector(color_rotatory_shot, { 2, 1 }, { position.x + 3, position.y + 3 });
	ShotVector(color_rotatory_shot, { -1, 1 }, { position.x + 3, position.y + 3 });
	ShotVector(color_rotatory_shot, { 3, 0 }, { position.x + 3, position.y + 3 });
	ShotVector(color_rotatory_shot, { -3, 0 }, { position.x + 3, position.y + 3 });
	ShotVector(color_rotatory_shot, { 1,-3 }, { position.x + 3, position.y + 3 });
	ShotVector(color_rotatory_shot, { -1, -3 }, { position.x + 3, position.y + 3 });
	ShotVector(color_rotatory_shot, { 3, -2 }, { position.x + 3, position.y + 3 });
	ShotVector(color_rotatory_shot, { -3, -2 }, { position.x + 3, position.y + 3 });

	App->particles->AddParticle(explosion, position.x , position.y , COLLIDER_EXPLOSION);
	fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_SmallSpaceship_Explosion.wav");
	if (!fx_shoot) {
		LOG("Error loading shoot's fx: %s", Mix_GetError)
	}*/
	App->audio->Play_Fx(fx_shoot);
	delete App->enemies->enemies[num_enemy];
	App->enemies->enemies[num_enemy] = nullptr;

}



void Sinus::ShotVector(Particle& shot, iPoint velocity_vector, fPoint shot_initial_pos) {

	shot.speed.x = velocity_vector.x;
	shot.speed.y = velocity_vector.y;
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);

}

void Sinus::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
}