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

void ModulePlayer::updatePosition()
{
	position.x += speed_vec.x;
	position.y += speed_vec.y;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	position.y ;
		
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || App->input->gamepad[0] == KEY_STATE::KEY_REPEAT) //---UP
	{
		speed_vec.y -= speed;
		updatePosition();
		App->render->camera.y += 2;
		if (-position.y*SCREEN_SIZE > App->render->camera.y) {
			position.y = -App->render->camera.y / SCREEN_SIZE; //upper player limit. ------->The relation between camera.y and position.y is camera.y=-position.y*SCREEN_SIZE
		}

	}
		

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || App->input->gamepad[1] == KEY_STATE::KEY_REPEAT)//---DOWN
	{
		speed_vec.y += speed;
		updatePosition();
		if ((-(position.y - SCREEN_HEIGHT + 27)*SCREEN_SIZE) < App->render->camera.y) { //lower player limit (27 is height of spaceship)
			position.y = ((-App->render->camera.y / SCREEN_SIZE) - 27 + SCREEN_HEIGHT);
		}


	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->gamepad[2] == KEY_STATE::KEY_REPEAT)//---RIGHT
	{
		speed_vec.x += speed;
		updatePosition();

		App->render->camera.x -= 2;

		if (App->render->camera.x <= -154) {//right camera limit
			App->render->camera.x = -154;
			if (position.x >= 275) { //right player limit
				position.x = 275;
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->gamepad[3] == KEY_STATE::KEY_REPEAT)//---LEFT

	{
		speed_vec.x -= speed;
		updatePosition();

		App->render->camera.x += 2;

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


	if (speed_vec.x > 0)
		speed_vec.x--;
	if (speed_vec.x < 0)
		speed_vec.x++;

	if (speed_vec.y > 0)
		speed_vec.y--;
	if (speed_vec.y < 0)
		speed_vec.y++;

	spaceship_collider->SetPos(position.x, position.y);

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));


		return UPDATE_CONTINUE;
	

}



//void ModulePlayer::shoot()
//{
//	//direction = aim_to_player();
//	speed_vec.y = sin(direction);
//	App->particles->enemy_bullet.speed.x = cos(shoot_direction) * ENEMY_BULLET_SPEED;
//
//	//App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);
//
//	if (shot_current_delay < ENEMY_SHOT_DELAY)
//		shot_current_delay++;
//	else {
//		App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);
//		shot_current_delay = 0;
//	}
//
//}

//void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
//{
//	
//}

//void ModulePlayer::Dead() {
//
//	
//	
//}