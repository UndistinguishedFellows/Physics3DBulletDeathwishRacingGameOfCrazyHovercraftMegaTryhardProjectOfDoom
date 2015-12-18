#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	win_lose = 0;

	//timer
	time = new Timer();
	time_to_win = 90.0f;
	chrono = 0.0f;
	last_time = 0.0f;
	best_time = 0.0f;
	time->Start();

	App->camera->Move(vec3(0.0f, 50.0f, -10.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	s.size = vec3(20, 5, 1);
	s.SetPos(0, 2.5f, 270);
	s.color = Color(0, 0.6, 0, 1);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	floor.size = vec3(100,0,1100);
	floor.color = Color(0.1,0.7,1,1);
	App->physics->AddBody(floor, 0.0f);

	// ###### CIRCUITO ######

	wall_altitude = 1;

	// start
	start_back.size = vec3(2, 10, 22);
	start_back.SetPos(0, wall_altitude, -8);
	start_back.SetRotation(90, vec3(0, 1, 0));
	App->physics->AddBody(start_back, 0.0f);

	start_left.size = vec3(2, 10, 58);
	start_left.SetPos(10, wall_altitude, 21);
	App->physics->AddBody(start_left, 0.0f);

	start_right.size = vec3(2, 10, 58);
	start_right.SetPos(-10, wall_altitude, 21);
	App->physics->AddBody(start_right, 0.0f);

	// curve 1
	curve1_left.size = vec3(50, 10, 50);
	curve1_left.SetPos(10, wall_altitude, 83);
	curve1_left.SetRotation(45, vec3(0, 1, 0));
	App->physics->AddBody(curve1_left, 0.0f);

	curve1_right_a.size = vec3(2, 10, 50);
	curve1_right_a.SetPos(-27.5f, wall_altitude, 67);
	curve1_right_a.SetRotation(-45, vec3(0, 1, 0));
	App->physics->AddBody(curve1_right_a, 0.0f);

	curve1_right_b.size = vec3(2, 10, 50);
	curve1_right_b.SetPos(-27.5f, wall_altitude, 101);
	curve1_right_b.SetRotation(45, vec3(0, 1, 0));
	App->physics->AddBody(curve1_right_b, 0.0f);

	// hall 1
	hall1_left.size = vec3(2, 10, 30);
	hall1_left.SetPos(10, wall_altitude, 132);
	App->physics->AddBody(hall1_left, 0.0f);

	hall1_right.size = vec3(2, 10, 29.5f);
	hall1_right.SetPos(-10, wall_altitude, 132.5f);
	App->physics->AddBody(hall1_right, 0.0f);

	// room 1
	//a
	room1_left_a.size = vec3(2, 10, 50);
	room1_left_a.SetPos(27.5f, wall_altitude, 164);
	room1_left_a.SetRotation(45, vec3(0, 1, 0));
	App->physics->AddBody(room1_left_a, 0.0f);

	room1_right_a.size = vec3(2, 10, 50);
	room1_right_a.SetPos(-27.5f, wall_altitude, 164);
	room1_right_a.SetRotation(-45, vec3(0, 1, 0));
	App->physics->AddBody(room1_right_a, 0.0f);

	//b
	room1_left_b.size = vec3(2, 10, 50);
	room1_left_b.SetPos(45, wall_altitude, 205);
	App->physics->AddBody(room1_left_b, 0.0f);

	room1_right_b.size = vec3(2, 10, 50);
	room1_right_b.SetPos(-45, wall_altitude, 205);
	App->physics->AddBody(room1_right_b, 0.0f);

	//c
	room1_left_c.size = vec3(2, 10, 50);
	room1_left_c.SetPos(27.5f, wall_altitude, 247);
	room1_left_c.SetRotation(-45, vec3(0, 1, 0));
	App->physics->AddBody(room1_left_c, 0.0f);

	room1_right_c.size = vec3(2, 10, 50);
	room1_right_c.SetPos(-27.5f, wall_altitude, 247);
	room1_right_c.SetRotation(45, vec3(0, 1, 0));
	App->physics->AddBody(room1_right_c, 0.0f);

	//obstacles room 1

	room1_obstacle_a.radius = 5;
	room1_obstacle_a.SetPos(0,0,165);
	App->physics->AddBody(room1_obstacle_a, 0.0f);

	room1_obstacle_b.radius = 5;
	room1_obstacle_b.SetPos(20, 0, 185);
	App->physics->AddBody(room1_obstacle_b, 0.0f);

	room1_obstacle_c.radius = 5;
	room1_obstacle_c.SetPos(-20, 0, 185);
	App->physics->AddBody(room1_obstacle_c, 0.0f);

	room1_obstacle_d.radius = 5;
	room1_obstacle_d.SetPos(0, 0, 205);
	App->physics->AddBody(room1_obstacle_d, 0.0f);

	room1_obstacle_e.radius = 5;
	room1_obstacle_e.SetPos(40, 0, 205);
	App->physics->AddBody(room1_obstacle_e, 0.0f);

	room1_obstacle_f.radius = 5;
	room1_obstacle_f.SetPos(-40, 0, 205);
	App->physics->AddBody(room1_obstacle_f, 0.0f);

	room1_obstacle_g.radius = 5;
	room1_obstacle_g.SetPos(20, 0, 225);
	App->physics->AddBody(room1_obstacle_g, 0.0f);

	room1_obstacle_h.radius = 5;
	room1_obstacle_h.SetPos(-20, 0, 225);
	App->physics->AddBody(room1_obstacle_h, 0.0f);

	room1_obstacle_i.radius = 5;
	room1_obstacle_i.SetPos(0, 0, 245);
	App->physics->AddBody(room1_obstacle_i, 0.0f);


	// hall 2
	hall2_left.size = vec3(2, 10, 30);
	hall2_left.SetPos(10, wall_altitude, 279);
	App->physics->AddBody(hall2_left, 0.0f);

	hall2_right.size = vec3(2, 10, 30);
	hall2_right.SetPos(-10, wall_altitude, 279);
	App->physics->AddBody(hall2_right, 0.0f);

	// curve 2
	curve2_left_a.size = vec3(2, 10, 50);
	curve2_left_a.SetPos(-27.5f, wall_altitude, 311);
	curve2_left_a.SetRotation(-45, vec3(0, 1, 0));
	App->physics->AddBody(curve2_left_a, 0.0f);

	curve2_left_b.size = vec3(2, 10, 50);
	curve2_left_b.SetPos(-27.5f, wall_altitude, 345);
	curve2_left_b.SetRotation(45, vec3(0, 1, 0));
	App->physics->AddBody(curve2_left_b, 0.0f);

	curve2_right.size = vec3(50, 10, 50);
	curve2_right.SetPos(10, wall_altitude, 328);
	curve2_right.SetRotation(45, vec3(0, 1, 0));
	App->physics->AddBody(curve2_right, 0.0f);

	// hall 3
	hall3_left.size = vec3(2, 10, 30);
	hall3_left.SetPos(10, wall_altitude, 377);
	App->physics->AddBody(hall3_left, 0.0f);

	hall3_right.size = vec3(2, 10, 30);
	hall3_right.SetPos(-10, wall_altitude, 377);
	App->physics->AddBody(hall3_right, 0.0f);

	// room 2
	//a
	room2_left_a.size = vec3(2, 10, 50);
	room2_left_a.SetPos(27.5f, wall_altitude, 409);
	room2_left_a.SetRotation(45, vec3(0, 1, 0));
	App->physics->AddBody(room2_left_a, 0.0f);

	room2_right_a.size = vec3(2, 10, 50);
	room2_right_a.SetPos(-27.5f, wall_altitude, 409);
	room2_right_a.SetRotation(-45, vec3(0, 1, 0));
	App->physics->AddBody(room2_right_a, 0.0f);

	//b
	room2_left_b.size = vec3(2, 10, 50);
	room2_left_b.SetPos(27.5f, wall_altitude, 443);
	room2_left_b.SetRotation(-45, vec3(0, 1, 0));
	App->physics->AddBody(room2_left_b, 0.0f);

	room2_right_b.size = vec3(2, 10, 50);
	room2_right_b.SetPos(-27.5f, wall_altitude, 443);
	room2_right_b.SetRotation(45, vec3(0, 1, 0));
	App->physics->AddBody(room2_right_b, 0.0f);

	room2_obstacle.radius = 15;
	room2_obstacle.SetPos(0, 0, 425);
	App->physics->AddBody(room2_obstacle, 0.0f);

	// finish
	finish_left.size = vec3(2, 10, 50);
	finish_left.SetPos(10, wall_altitude, 485);
	App->physics->AddBody(finish_left, 0.0f);

	finish_right.size = vec3(2, 10, 50);
	finish_right.SetPos(-10, wall_altitude, 485);
	App->physics->AddBody(finish_right, 0.0f);

	//###########################

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	//Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();

	//loss update
	if (chrono > time_to_win){
		win_lose = 2;
		time->Stop();
		App->player->car->base->SetPos(0, 3, 0);
		App->player->car->fan->SetPos(0, 4, -2);
		time->Start();
	}


	chrono = time->Read()/1000.0f;

	char title[80];
	switch (win_lose)
	{
	case 0:
		sprintf_s(title, "TO WIN: %.2f s  TIME: %.2f s  LAST: %.2f s  BEST: %.2f s", time_to_win, chrono, last_time, best_time);
		break;
	case 1:
		sprintf_s(title, "TO WIN: %.2f s  TIME: %.2f s  LAST: %.2f s  BEST: %.2f s  ### YOU WIN! ###", time_to_win, chrono, last_time, best_time);
		break;
	case 2:
		sprintf_s(title, "TO WIN: %.2f s  TIME: %.2f s  LAST: %.2f s  BEST: %.2f s  ### YOU LOSE! ###", time_to_win, chrono, last_time, best_time);
		break;
	}

	App->window->SetTitle(title);

	sensor->GetTransform(&s.transform);
	s.Render();

	floor.Render();

	// ###### CIRCUITO ######

	// start
	start_back.Render();
	start_left.Render();
	start_right.Render();
	
	// curve 1
	curve1_left.Render();
	curve1_right_a.Render();
	curve1_right_b.Render();

	// hall 1
	hall1_left.Render();
	hall1_right.Render();

	// room 1
	room1_left_a.Render();
	room1_right_a.Render();

	room1_left_b.Render();
	room1_right_b.Render();

	room1_left_c.Render();
	room1_right_c.Render();

	room1_obstacle_a.Render();
	room1_obstacle_b.Render();
	room1_obstacle_c.Render();
	room1_obstacle_d.Render();
	room1_obstacle_e.Render();
	room1_obstacle_f.Render();
	room1_obstacle_g.Render();
	room1_obstacle_h.Render();
	room1_obstacle_i.Render();

	// hall 2
	hall2_left.Render();
	hall2_right.Render();

	// curve2 
	curve2_left_a.Render();
	curve2_left_b.Render();
	curve2_right.Render();

	// hall 3
	hall3_left.Render();
	hall3_right.Render();

	// room 2
	room2_left_a.Render();
	room2_right_a.Render();

	room2_left_b.Render();
	room2_right_b.Render();

	room2_obstacle.Render();

	//finish
	finish_left.Render();
	finish_right.Render();

	//###########################

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
	win_lose = 1;
	time->Stop();
	last_time = chrono;
	if (last_time < best_time || best_time == 0) best_time = last_time;
	time->Start();
	App->player->car->base->SetPos(0, 3, 0);
	App->player->car->fan->SetPos(0, 4, -2);
}

