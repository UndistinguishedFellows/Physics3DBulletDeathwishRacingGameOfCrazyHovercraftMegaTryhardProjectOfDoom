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
	Cube s;
	PhysBody3D* sensor;

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

	//finish
	Cube finish_left;
	Cube finish_right;

	//###################
};
