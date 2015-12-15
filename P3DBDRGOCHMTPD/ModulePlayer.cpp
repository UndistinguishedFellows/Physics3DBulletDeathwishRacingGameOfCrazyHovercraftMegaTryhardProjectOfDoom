#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	//s.SetPos(0, 0, 0);
	car = createHovercraft();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	/*mat4x4 m;
	car->GetTransform(&m);
	s.transform = m;
	s.Render();*/
	

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		car->base->SetPos(0, 2, 0);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{

	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{

	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{

	}

	char title[80];
	//sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

Hovercaft* ModulePlayer::createHovercraft()
{
	Hovercaft* h = new Hovercaft();
	h->base = App->physics->AddBody(h->p_base);
	h->fan = App->physics->AddBody(h->p_fan);
	//h->p_base.SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);


	App->physics->AddConstraintHinge(*h->base, *h->fan, { 1, 0.5f, 0 }, { 0, -3, 0 }, { 0, 1, 0 }, { 0, 1, 0 });
	//h->p_base.SetPos(0, 2, 0);
	//h->p_fan.SetPos(1.5f, 4, 0);

	return h;
}

Hovercaft::Hovercaft()
{
	p_base.size = vec3(5, 1, 2);
	p_base.SetPos(0, 0, 0);

	p_fan.radius = 3;
	p_fan.height = 0.5f;


}

