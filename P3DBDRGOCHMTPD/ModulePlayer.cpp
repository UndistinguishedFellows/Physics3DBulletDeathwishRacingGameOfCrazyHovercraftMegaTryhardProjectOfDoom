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
	
	speed_cam = 1.09f;
	dist_to_hovercraft = { -15.0f, 28.0f, -15.0f };

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

	//Camara
	/*car->base->GetBody.SetPos->GetTransform(&pivot);
	hovercraft_pos.Set(pivot.M[0], pivot.M[4], pivot.M[8]);
	//hovercraft_vector = car->base->GetTransform->getForwardVector();
	car->base->GetRotationTransform(&pivot);
	hovercraft_f.Set(pivot.M[3], pivot.M[4], pivot.M[5]);
	
	//camera_new_pos = { hovercraft_pos.x + (hovercraft_f.x * dist_to_hovercraft.x), hovercraft_pos.y + hovercraft_f.y + dist_to_hovercraft.y, hovercraft_pos.z + (hovercraft_f.z * dist_to_hovercraft.z) };
	camera_new_pos = { hovercraft_pos.x + (dist_to_hovercraft.x), hovercraft_pos.y + dist_to_hovercraft.y, hovercraft_pos.z + (dist_to_hovercraft.z) };

	camera_pos = camera_new_pos - App->camera->Position;
	reference.Set(hovercraft_pos.x, hovercraft_pos.y, hovercraft_pos.z);

	App->camera->Look(App->camera->Position + (speed_cam * camera_pos), reference);
	App->camera->Position.Set(hovercraft_pos.x, hovercraft_pos.y + 30, hovercraft_pos.z);*/

	car->base->GetTransform(&car->p_base.transform);
	car->fan->GetTransform(&car->p_fan.transform);
	car->p_base.Render();
	car->p_fan.Render();

	
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		car->base->activate(true);
		mat4x4 m;
		car->fan->GetTransform(&m);

		car->fan->Push(-m.M[0] * car->force, -m.M[1] * car->force, -m.M[2] * car->force);

		//car->fan->Push(0.5f, 0.5f, 0.5f);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		car->fan->activate(true);
		car->fanHinge->enableMotor(true);
		btRigidBody* b = car->fan->GetBody();
		b->applyTorque({ car->fanTorque.x, -car->fanTorque.y, car->fanTorque.z});
		car->fanHinge->enableMotor(false);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		car->fan->activate(true);
		car->fanHinge->enableMotor(true);
		btRigidBody* b = car->fan->GetBody();
		b->applyTorque({ car->fanTorque.x, car->fanTorque.y, car->fanTorque.z });
		car->fanHinge->enableMotor(false);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		car->base->activate(true);
		mat4x4 m;
		car->fan->GetTransform(&m);

		//car->fan->Push(m[2]*0.5f, m[6]*0.5f, m[10]*0.5f);
		car->fan->Push(m.M[0] * car->force, m.M[1] * car->force, m.M[2] * car->force);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		btRigidBody* b = car->fan->GetBody();
		b->setAngularVelocity({ 0, 0, 0 });
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		btRigidBody* b = car->fan->GetBody();
		b->setAngularVelocity({ 0, 0, 0 });
	}

	mat4x4 m;
	car->fan->GetTransform(&m);

	//car->fan->Push(m[2]*0.5f, m[6]*0.5f, m[10]*0.5f);
	//car->fan->Push(-m.M[0] * 0.5f, -m.M[1] * 0.5f, -m.M[2] * 0.5f);

	return UPDATE_CONTINUE;
}

Hovercaft* ModulePlayer::createHovercraft()
{
	mat4x4 rotation;
	
	Hovercaft* h = new Hovercaft({6, 1, 3 }, {2, 0.5f});

	

	h->base = App->physics->AddBody(h->p_base, 100);
	h->fan = App->physics->AddBody(h->p_fan, 10);

	h->base->SetPos(0, 2, 0);
	h->fan->SetPos(0, 4, 0);

	h->base->GetTransform(&rotation);
	rotation.rotate(90, { 0, 1, 0 });
	h->base->SetTransform(&rotation);

	h->fan->GetTransform(&rotation);
	rotation.rotate(90, { 0, 1, 0 });
	h->fan->SetTransform(&rotation);

	h->base->SetFriction(1);

	//btRigidBody* b = car->base->GetBody();
	
	//h->fan->SetPos()
	//h->p_base.SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	
	h->fanHinge = App->physics->AddConstraintHinge(*h->base, *h->fan, { h->baseSize.x/2, h->baseSize.x/2, 0 }, { 0, h->fanSize.x/2-0.5f, 0 }, { 0, 1, 0 }, { 0, 1, 0 });
	h->fanHinge->setLimit(-0.349f, 0.349, 0.0f, 0.0f);
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

	force = 10.0f;
	fanTorque = { 0, 100, 0 };


}

