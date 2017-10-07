#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleStageCompleted.h"
#include "ModuleLevel1.h"

#include<stdio.h>
#include "SDL/include/SDL_timer.h"

ModulePlayer::ModulePlayer()
{
	
	
	graphics = NULL;
	current_animation = NULL;
	

	

	//Player image

	idle.PushBack({ 0, 14, 150, 158 });
	idle.PushBack({ 151, 14, 150, 158 });
	idle.PushBack({ 302, 14, 150, 158 });
	idle.PushBack({ 453, 14, 150, 158 });
	idle.PushBack({ 604, 14, 150, 158 });
	idle.PushBack({ 755, 14, 150, 158 });
	idle.speed = 0.1f;



}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::CleanUp()
{

	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(yellow_font_score);
	App->fonts->UnLoad(red_font_score);
	/*if (spaceship_collider != nullptr) {
	spaceship_collider->to_delete = true;
	}*/

	return true;
}

// Load assets
bool ModulePlayer::Start()
{
	
	App->collision->Enable();
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/Raiden_Spaceship.png"); 
	if (graphics == nullptr) {
		LOG("Error loading player textures %s", SDL_GetError);
		ret = false;
	}
	spaceship_speed = 1;

	win_chain = 0;
	
	if (App->player2->player2==false) { 

		position.x = 111; //position if there's only 1 player
		position.y = 150;


		
	}
	else {

		position.x = 71; //position if there are 2 players
		position.y = 150;

	}
	current_animation = &idle;
	
	godmode_activated = " G ";
	user_interface = "    1UP   HI.SCORE    2UP ";
	red_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}/0123456789:", 3);
	yellow_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}/0123456789:", 3);
	// * -> "
	// [ -> tm
	//	]. -> Pts
	//	{. -> Cts
	//	}. -> Pcs

	if (spaceship_collider==nullptr)
	spaceship_collider = App->collision->AddCollider({ 0,0, 145, 150 }, COLLIDER_PLAYER, this);

	total_bombs = 3;
	bomb_thrown = 0;
	bomb_life = 0;
	last_bomb = 0;



	return ret;
}

void ModulePlayer::check_map_limits()
{
	

	if (position.x < 10 + map_margin)  //LEFT
		position.x = 10 + map_margin;

	if (position.x >(MAP1_WIDTH - 170) -map_margin) //RIGhT
		position.x = (MAP1_WIDTH - 170) - map_margin;

	if (position.y < -MAP1_HEIGHT + (SCREEN_HEIGHT+20) + map_margin)
		position.y = (-MAP1_HEIGHT + (SCREEN_HEIGHT + 20)) + map_margin;

	if (position.y > (400) - map_margin)
		position.y = (400) - map_margin;

}

void ModulePlayer::move_camera_with_player()
{
	if ((App->render->camera.x + position.x) < +map_margin)  //Camera Left
		App->render->camera.x = -position.x + map_margin;

	if ((position.x) > ((SCREEN_WIDTH - 150) - App->render->camera.x)  - map_margin)  //Camera Right
		App->render->camera.x = -(position.x - (SCREEN_WIDTH - 150) ) - map_margin;

	if ((App->render->camera.y + position.y) < map_margin)  //Camera UP
		App->render->camera.y = -position.y + map_margin;

	if ((position.y) > ((SCREEN_HEIGHT - 150) - App->render->camera.y) - map_margin)  //Camera Down
		App->render->camera.y = -(position.y - (SCREEN_HEIGHT - 150)) - map_margin;
}

void ModulePlayer::updatePosition()
{
	
	position.x += acceleration_vec.x;
	position.y -= acceleration_vec.y;
	
}

void ModulePlayer::applyInertia()
{
	if (acceleration_vec.y > 0 && acceleration_vec.y < friction) {
		acceleration_vec.y = 0;
	}
	else if (acceleration_vec.y < 0 && acceleration_vec.y > friction) {
		acceleration_vec.y = 0;
	}
	else if (acceleration_vec.y > 0) {
		acceleration_vec.y -= friction;
	}
	else if (acceleration_vec.y < 0) {
		acceleration_vec.y += friction;
	}
	if (acceleration_vec.x > 0 && acceleration_vec.x < friction) {
		acceleration_vec.x = 0;
	}
	else if (acceleration_vec.x < 0 && acceleration_vec.x > friction) {
		acceleration_vec.x = 0;
	}
	else if (acceleration_vec.x > 0) {
		acceleration_vec.x -= friction;
	}
	else if (acceleration_vec.x < 0) {
		acceleration_vec.x += friction;
	}
}

// Update: draw background
update_status ModulePlayer::Update()
{
	App->level1->scroll();

	applyInertia();
	if (!App->level1->first_animation) {// not able to move during first animation
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
			applyInertia();
			updatePosition();
		}
		else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || App->input->gamepad[1] == KEY_STATE::KEY_REPEAT) //---DOWN
		{
			
			if (acceleration_vec.y > -max_speed && acceleration_vec.y < max_speed)
				acceleration_vec.y -= acceleration;
			updatePosition();
			//App->render->camera.y += 4;


		}
		else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || App->input->gamepad[0] == KEY_STATE::KEY_REPEAT)//---UP
		{
			if (acceleration_vec.y > -max_speed && acceleration_vec.y < max_speed)
				acceleration_vec.y += acceleration;
			updatePosition();
			//App->render->camera.y -= camera_speed_module;
		}
		else {
			applyInertia();
			updatePosition();
		}

		//HORITZONTAL

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
			applyInertia();
			updatePosition();
		}
		else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->gamepad[2] == KEY_STATE::KEY_REPEAT)//---RIGHT
		{
			if (acceleration_vec.x > -max_speed && acceleration_vec.x < max_speed)
			acceleration_vec.x += acceleration;
			updatePosition();
			//App->render->camera.x -= camera_speed_module;
		}
		else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->gamepad[3] == KEY_STATE::KEY_REPEAT)//---LEFT

		{
			if (acceleration_vec.x > -max_speed && acceleration_vec.x < max_speed)
			acceleration_vec.x -= acceleration;
			updatePosition();
			//App->render->camera.x += 4;
		}
		else {
			applyInertia();
			updatePosition();
		}


		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->gamepad[4] == KEY_STATE::KEY_DOWN)// --SPACE SHOT
		{
			

		}

		//if ((App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN || App->input->gamepad[8] == KEY_STATE::KEY_REPEAT) && total_bombs > 0 && SDL_GetTicks() - last_bomb > 5000) //-----BOMB! (only when ur player has bombs and passed 5s from the last bomb)
		//{
		//	bomb_thrown = SDL_GetTicks();
		//	App->particles->AddParticle(bomb, position.x + 8, position.y, COLLIDER_EXPLOSION, 0, "Assets/Audio/Fx_Drop_Bomb");
		//	saved_position = position;
		//	total_bombs--;
		//	last_bomb = SDL_GetTicks();
		//}
		//if (bomb_thrown != 0 && SDL_GetTicks() - bomb_thrown > 1300) {// 1.3s to generate the explosion of the bomb(damaging collider)
		//	App->particles->AddParticle(bomb_explosion, saved_position.x - 70, saved_position.y - 250, COLLIDER_BOMB, 0, "Assets/Audio/Fx_Bomb_Explosion");
		//	bomb_thrown = 0;
		//	bomb_life = SDL_GetTicks();
		//	saved_position = { 0,0 };

		//}
		//if (bomb_life != 0 && SDL_GetTicks() - bomb_life > 3000) {// bomb life 3s then delete particle
		//	bomb_life = 0;
		//	bomb_explosion.to_delete;
		//}




		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE //check error
			&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE && !App->level1->first_animation) {
			current_animation = &idle;			
		}


	}


		if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN || App->input->gamepad[5] == KEY_STATE::KEY_REPEAT)//GOD MODE (press right stick on controller)

		{
			if (!godmode) {
				godmode = true;
			}
			else {
				godmode = false;
			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) && (App->fade->IsFading() == false))//DIRECT WIN/LOSE
		{
			App->fade->FadeToBlack(this, App->stageCompleted);

		}

		

		if (spaceship_collider != nullptr)
			spaceship_collider->SetPos(position.x+5, position.y);

		// Draw everything --------------------------------------
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

		
		// Draw UI (score) --------------------------------------

		if (score > high_score)
			high_score = score;

		if (App->player2->score > high_score&&App->player2->IsEnabled()) {
			high_score = App->player2->score;
		
		}
		


		sprintf_s(score_text, 10, "%8d", score);
		sprintf_s(high_score_text, 10, "%7d", high_score);

		App->fonts->BlitText(0, 1, red_font_score, user_interface);
		App->fonts->BlitText(0, 9, yellow_font_score, score_text);
		App->fonts->BlitText(88, 9, yellow_font_score, high_score_text);
		if (godmode) {
			App->fonts->BlitText(0, 1, yellow_font_score, godmode_activated);// Yellow "G" in left upper corner when godmode activated.
		}


		move_camera_with_player();

		check_map_limits();

		LOG("%d", App->render->camera.x);

		////////////////////PARTICLE

		estela.position.x = position.x;
		estela.position.y = position.y;
		
		estela.section.h *= estela.scale;
		estela.section.w *= estela.scale;


		estela.scale -= 0.0000000000001f;



		App->render->Blit(graphics, estela.position.x, estela.position.y, &estela.section, 0);

		return UPDATE_CONTINUE;
	}




void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	switch (c2->type) {
	//case COLLIDER_POWERUP_MEDAL:
	//	//App->particles->AddParticle(bonus_medal, position.x + 9, position.y, COLLIDER_PLAYER, 0, "Assets/Audio/Fx_Medal_Bonus.wav");
	//	score += 500;	
	//	fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_Medal_Bonus.wav");
	//		if (!fx_shoot) {
	//			LOG("Error loading shoot's fx: %s", Mix_GetError)
	//		}
	//		App->audio->Play_Fx(fx_shoot);
	//		
	//	
	//	break;

	//case COLLIDER_POWERUP_B:
	//	total_bombs++;
	//	if (total_bombs >= 6) {
	//		total_bombs = 6;		
	//	}
	//	break;

	/*case COLLIDER_ENEMY_SHOT :
		if (c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false&&godmode==false) {
			Dead();
		}*/
	case COLLIDER_ENEMY:
		if (c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false && godmode==false ) {
			Dead();
		}

	}
}

void ModulePlayer::Dead() {

	
	Red_Powerup_Lvl = 0;
	M_Powerup_Lvl = 0;
	Blue_Powerup_Lvl = 0;
	sprintf_s(score_text, 10, "%8d", score);
	sprintf_s(high_score_text, 10, "%7d", high_score);

	//if (App->player2->IsEnabled()) {
	//	App->player2->Red_Powerup_Lvl = 0;
	//	App->player2->M_Powerup_Lvl = 0;
	//	App->player2->Blue_Powerup_Lvl = 0;
	//	App->player2->destroyed = true;
	//
	//}
	
	destroyed = true;
	
	App->player2->player2 = false;
	App->fade->FadeToBlack((Module*)App->level1, (Module*)App->intro);
	App->particles->AddParticle(dead_explosion, position.x, position.y, COLLIDER_EXPLOSION,0, "Assets/Audio/Fx_Player_Explosion.wav");
	App->textures->Unload(graphics);
		
}


