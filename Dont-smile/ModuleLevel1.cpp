#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStageCompleted.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleLevel2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIntro.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePowerUps.h"

#include <time.h>  
#include <stdlib.h>  
#include "SDL/include/SDL_timer.h"

ModuleLevel1::ModuleLevel1()
{

	// foreground
	foreground.x = 0;
	foreground.y = 0;
	foreground.w = 0;
	foreground.h = 0;

	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 2333;
	background.h = 6399;

	ship_launcher.x = 0;
	ship_launcher.y = 0;
	ship_launcher.w = 0;
	ship_launcher.h = 0;

	
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	App->level2->Disable();
	App->stageCompleted->Disable();

	App->audio->Enable();
	App->collision->Enable();
	App->player->Enable();
	if (App->player2->player2 == true)
		App->player2->Enable();
	else if (App->player2->player2)
		App->player2->Disable();
	App->particles->Enable();
	
	App->enemies->Enable();

	if (App->player2->player2 == false) {

		App->player->position.x = App->player->map_margin + 50; //position if there's only 1 player
		App->player->position.y = -350;
	}
	else {

		App->player->position.x = 71; //position if there are 2 players
		App->player->position.y = 150;
	}

	if ((!App->player->godmode)&&(App->player->spaceship_collider->rect.w<-1000)){ //SOLVES AN ERROR THAT THE COLLIDER OF RAIDEN HAS -572662307 of x, y, w & h
		App->player->spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, App->player);
	App->player->spaceship_collider->SetPos(App->player->position.x, App->player->position.y);
}
	
	if ((App->player->spaceship_collider == nullptr) && (App->player->godmode == false)) {
		App->player->spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, App->player);
		App->player->spaceship_collider->SetPos(App->player->position.x, App->player->position.y);
	}

	
	LOG("Loading level 1");

	music_lvl1 = App->audio->Load_Music("Assets/Audio/00_Raiden.ogg");// COMMENT TO STOP MUSIC
	if (!music_lvl1) {
	LOG("Error loading lvl1 music: %s",Mix_GetError)
	}
	//App->audio->Play_Music(music_lvl1); 
	
	graphics = App->textures->Load("Assets/Images/lvl1_tilemap.png");

	spawn_distance = 900;

	
	last_spawn_sinus = SDL_GetTicks();
	last_spawn_bacteria = SDL_GetTicks();
	srand(time(NULL));
	
	/*App->enemies->AddEnemy(SINUS, 600, 300);
	App->enemies->AddEnemy(BACTERIA, 600, 350);*/

	CreatePelitos();


	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading level 1");

	

	if (graphics != nullptr)	
		App->textures->Unload(graphics);
	if (music_lvl1 != nullptr) 	
		App->audio->Unload_Music(music_lvl1);
	App->player->Disable();
	App->player2->Disable();
	App->enemies->Disable();
	//App->collision->Disable();
	App->powerup->Disable();
	App->particles->Disable();

	first_animation = false;


	return true;
}

void ModuleLevel1::scroll()
{


	if (App->player->position.y > inferior_limit) {
		App->player->position.y = inferior_limit;
	}

	if (counter_sc_spd > max_sc_sp) {
		inferior_limit -= scroll_speed;
		counter_sc_spd = 0;
	}

	//if (counter_sc_spd > max_sc_sp) {
	//	inferior_limit -= scroll_speed;
	//	counter_sc_spd = 0;
	//}
	else {
		counter_sc_spd++;
	}
}

	


// Update: draw background
update_status ModuleLevel1::Update()
{
	SinusBacteriaSpawning(App->player->win_chain, App->player->position.x, App->player->position.y, spawn_distance);
	
	if (jumped) {

		App->player->win_chain++;
		
	}




	//if (App->render->camera.y < 100) {
	//	
	//	App->player->position.y += 1;
	//	App->player2->position.y += 1;
	//	App->render->camera.y += 1;
	//	first_animation = true;

	//}

		//App->render->camera.y += scroll_speed;
		
		if ((App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) && (App->fade->IsFading() == false))//DIRECT WIN/LOSE
		{
			App->fade->FadeToBlack(this, App->stageCompleted);

		}
	
	

	// Draw everything --------------------------------------


	
	App->render->Blit(graphics, 0, -6399 + SCREEN_HEIGHT, &background); 




	if (App->player->position.y <= -2735) {       //////////------------------------------------


		if (App->player2->IsEnabled())
			App->player2->spaceship_speed = 0;
	}

	return UPDATE_CONTINUE;
}



void ModuleLevel1::SinusBacteriaSpawning(uint win_chain, float pos_x, float pos_y, int spawn_margin) {

	

	int x = pos_x;
	int y =pos_y - spawn_margin;

	difficulty_time = win_chain * 150;	

	Uint32 spawntime_sinus=2500;
	counter_spawn_timer = SDL_GetTicks() - last_spawn_sinus;

	if ((spawntime_sinus - difficulty_time) < counter_spawn_timer) {
	
		App->enemies->AddEnemy(SINUS, x, y);
		//counter_spawn_timer = 0; //reestart timer
		last_spawn_sinus = SDL_GetTicks();
	}

	Uint32 spawntime_bacteria = 1500;
	counter_spawn_timer = SDL_GetTicks() - last_spawn_bacteria;

	if ((spawntime_bacteria - difficulty_time) < counter_spawn_timer) {

		App->enemies->AddEnemy(BACTERIA, x, y);
		//counter_spawn_timer = 0; //reestart timer
		last_spawn_bacteria= SDL_GetTicks();
	}




}

void ModuleLevel1::CreatePelitos()
{
	int x_pelito; 
	int y_pelito;
	for (int i = 0; i > -6000; i -= 400) {
		x_pelito = (rand() % 1800) + 200;
		y_pelito = rand() % 100;
		App->enemies->AddEnemy(PELITO, x_pelito, i + y_pelito);
	}
}




