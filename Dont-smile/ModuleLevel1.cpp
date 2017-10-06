#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"




ModuleLevel1::ModuleLevel1()
{

	// foreground
	foreground.x = 352;
	foreground.y = 134;
	foreground.w = 351;
	foreground.h = 2836;

	// Background / sky
	background.x = 0;
	background.y = 134;
	background.w = 351;
	background.h = 3265;

	ship_launcher.x = 352;
	ship_launcher.y = 2971;
	ship_launcher.w = 351;
	ship_launcher.h = 429;

	
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	/*App->level2->Disable();*/
	

	App->audio->Enable();
	App->collision->Enable();
	App->player->Enable();
	/*if (App->player2->player2 == true)
		App->player2->Enable();
	else if (App->player2->player2)
		App->player2->Disable();
	App->particles->Enable();*/
	
	App->enemies->Enable();

	//if (App->player2->player2 == false) {

	//	App->player->position.x = 111; //position if there's only 1 player
	//	App->player->position.y = 150;
	//}
	//else {

	//	App->player->position.x = 71; //position if there are 2 players
	//	App->player->position.y = 150;
	//}

//	if ((!App->player->godmode)&&(App->player->spaceship_collider->rect.w<-1000)){ //SOLVES AN ERROR THAT THE COLLIDER OF RAIDEN HAS -572662307 of x, y, w & h
//		App->player->spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, App->player);
//	App->player->spaceship_collider->SetPos(App->player->position.x, App->player->position.y);
//}
//
//	if ((App->player->spaceship_collider == nullptr) && (App->player->godmode == false)) {
//		App->player->spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, App->player);
//		App->player->spaceship_collider->SetPos(App->player->position.x, App->player->position.y);
//	}
//

	App->enemies->AddEnemy(BACTERIA, 50, -200);

	scroll_speed = 2;
	
	LOG("Loading level 1");

	music_lvl1 = App->audio->Load_Music("");// COMMENT TO STOP MUSIC
	if (!music_lvl1) {
	LOG("Error loading lvl1 music: %s",Mix_GetError)
	}
	App->audio->Play_Music(music_lvl1);
	
	graphics = App->textures->Load("Assets/Images/lvl1_tilemap.png");
	
	
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
	
	App->enemies->Disable();
	//App->collision->Disable();
	
	App->particles->Disable();

	first_animation = false;


	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	

	//ws
	// Draw everything --------------------------------------

	
	App->render->Blit(graphics, -50, -2965, &background); 

	App->render->Blit(graphics, -50, -2965, &foreground);
	
	App->render->Blit(graphics, -50, -150, &ship_launcher, 1.8f);


	if (App->player->position.y <= -2735) {

		scroll_speed = 0;
 		boss_music = App->audio->Load_Music("Assets/Audio/Boss_Music.ogg");
		if (!boss_music) {
			LOG("Error loading boss music: %s", Mix_GetError)
		}
		/*App->audio->Play_Music(boss_music);
		App->player->spaceship_speed = 0;
<<<<<<< HEAD
		/*if (App->player2->IsEnabled) 
			App->player2->spaceship_speed = 0;*/

		//if (App->player2->IsEnabled()) 
		//	App->player2->spaceship_speed = 0;



	/*if (App->input->keyboard[SDL_SCANCODE_TAB] && fading == false) {
	
		App->fade->FadeToBlack(this, App->stageCompleted);
		fading = true;
		*/
	}

	return UPDATE_CONTINUE;
}