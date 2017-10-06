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

#include "ModuleLevel1.h"

#include<stdio.h>
#include "SDL/include/SDL_timer.h"

ModulePlayer::ModulePlayer()
{
	
	
	graphics = NULL;
	current_animation = NULL;
	

	

	//Player image

	idle.PushBack({ 80, 13, 24, 27 });


	

	

	

}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	

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
	

	position.x = 111; //position if there's only 1 player
	position.y = 150;


	//else {

	//	position.x = 71; //position if there are 2 players
	//	position.y = 150;

	//}
	current_animation = &idle;
	
	godmode_activated = " G ";
	

	if (spaceship_collider==nullptr)
	spaceship_collider = App->collision->AddCollider({ 0,0, 24, 26 }, COLLIDER_PLAYER, this);

	total_bombs = 3;
	bomb_thrown = 0;
	bomb_life = 0;
	last_bomb = 0;

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	position.y ;
	int speed = 2;
		
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || App->input->gamepad[0] == KEY_STATE::KEY_REPEAT) //---UP
	{
		position.y -= speed;
		App->render->camera.y += 4;
		if (-position.y*SCREEN_SIZE > App->render->camera.y) {
			position.y = -App->render->camera.y / SCREEN_SIZE; //upper player limit. ------->The relation between camera.y and position.y is camera.y=-position.y*SCREEN_SIZE
		}

	}
		

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || App->input->gamepad[1] == KEY_STATE::KEY_REPEAT)//---DOWN
	{
		position.y += speed;
		if ((-(position.y - SCREEN_HEIGHT + 27)*SCREEN_SIZE) < App->render->camera.y) { //lower player limit (27 is height of spaceship)
			position.y = ((-App->render->camera.y / SCREEN_SIZE) - 27 + SCREEN_HEIGHT);
		}


	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->gamepad[2] == KEY_STATE::KEY_REPEAT)//---RIGHT
	{
		position.x += speed;
		App->render->camera.x -= 4;

		if (App->render->camera.x <= -154) {//right camera limit
			App->render->camera.x = -154;
			if (position.x >= 275) { //right player limit
				position.x = 275;
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->gamepad[3] == KEY_STATE::KEY_REPEAT)//---LEFT

	{
		position.x -= speed;
		App->render->camera.x += 4;

		if (App->render->camera.x >= 100) {//left camera limit
			App->render->camera.x = 100;
			if (position.x <= -48) { //left player limit
				position.x = -48;
			}
		}
	}
		//if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->gamepad[4] == KEY_STATE::KEY_DOWN)// --SPACE SHOT
		//{

		//}

		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));


		return UPDATE_CONTINUE;
	

}


//void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
//{
//	
//}

//void ModulePlayer::Dead() {
//
//	
//	
//}