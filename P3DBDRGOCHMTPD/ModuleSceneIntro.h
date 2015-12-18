#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	Timer* time;
	float chrono;
	float last_time;
	float best_time;

	Cube s;
	PhysBody3D* sensor;

	Cube floor;

	// CIRCUITO
	//start
	Cube start_left;
	Cube start_right;

	//curve 1
	Cube curve1_left;
	Cube curve1_right_a;
	Cube curve1_right_b;

	//hall 1
	Cube hall1_left;
	Cube hall1_right;

	//room 1
	Cube room1_left_a;
	Cube room1_right_a;

	Cube room1_left_b;
	Cube room1_right_b;

	Cube room1_left_c;
	Cube room1_right_c;

	Sphere room1_obstacle_a;
	Sphere room1_obstacle_b;
	Sphere room1_obstacle_c;
	Sphere room1_obstacle_d;
	Sphere room1_obstacle_e;
	Sphere room1_obstacle_f;
	Sphere room1_obstacle_g;
	Sphere room1_obstacle_h;
	Sphere room1_obstacle_i;

	//hall 2
	Cube hall2_left;
	Cube hall2_right;

	//curve 2
	Cube curve2_left_a;
	Cube curve2_left_b;
	Cube curve2_right;

	//hall 3
	Cube hall3_left;
	Cube hall3_right;

	//room 2
	Cube room2_left_a;
	Cube room2_right_a;

	Cube room2_left_b;
	Cube room2_right_b;

	Sphere room2_obstacle;

	//finish
	Cube finish_left;
	Cube finish_right;

	//###################
};
