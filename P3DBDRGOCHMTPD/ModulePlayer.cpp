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
	mat4x4 mBase;
	car->fan->GetTransform(&mBase);
	//car->base->Push(0, 0.1f, 0);

	car->base->GetTransform(&car->p_base.transform);
	car->fan->GetTransform(&car->p_fan.transform);
	car->p_base.Render();
	car->p_fan.Render();

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		mat4x4 m;
		car->fan->GetTransform(&m);

		//car->fan->Push(m[2]*0.5f, m[6]*0.5f, m[10]*0.5f);
		car->fan->Push(-m.M[0] * 5, -m.M[1] * 5, -m.M[2] * 5);

		//car->fan->Push(0.5f, 0.5f, 0.5f);
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

	mat4x4 m;
	car->fan->GetTransform(&m);

	//car->fan->Push(m[2]*0.5f, m[6]*0.5f, m[10]*0.5f);
	//car->fan->Push(-m.M[0] * 0.5f, -m.M[1] * 0.5f, -m.M[2] * 0.5f);

	return UPDATE_CONTINUE;
}

Hovercaft* ModulePlayer::createHovercraft()
{
	mat4x4 rotation;

	Hovercaft* h = new Hovercaft({3, 1, 6 }, {2, 0.5f});
	h->base = App->physics->AddBody(h->p_base, 10.0f);
	h->fan = App->physics->AddBody(h->p_fan);
	
	h->fan->GetTransform(&rotation);
	rotation.rotate(90, { 0, 1, 0 });
	h->fan->SetTransform(&rotation);

	h->base->SetPos(0, 5, 0);
	h->fan->SetPos(0, 7, 0);
	//h->fan->SetPos()
	//h->p_base.SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	
	//App->physics->AddConstraintHinge(*h->base, *h->fan, { 0, h->baseSize.y / 2 + 0.5f, -h->baseSize.z / 2 - 0.5f }, { h->fanSize.x, , 0 }, { 0, 1, 0 }, { 0, 1, 0 })->setLimit(0, 0);
	App->physics->AddConstraintHinge(*h->base, *h->fan, { 0, h->baseSize.y / 2, -h->baseSize.z / 2 }, { 0, -h->fanSize.x - 0.1f, 0 }, { 0, 1, 0 }, { 0, 1, 0 })->setLimit(4, 3.14f*1.5f + 3.14 / 6);
	//h->p_base.SetPos(0, 2, 0);
	//h->p_fan.SetPos(1.5f, 4, 0);

	return h;
}

Hovercaft::Hovercaft(vec3 _baseSize, vec2 _fanSize)
{
	p_base.size = _baseSize;
	p_base.SetPos(0, 0, 0);

	p_fan.radius = _fanSize.x;
	p_fan.height = _fanSize.y;

	baseSize = _baseSize;
	fanSize = _fanSize;


}

