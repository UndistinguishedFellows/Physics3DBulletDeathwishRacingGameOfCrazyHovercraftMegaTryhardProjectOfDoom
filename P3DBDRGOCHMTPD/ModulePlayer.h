#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f


class Hovercaft
{
public:
	PhysBody3D* base = nullptr;
	PhysBody3D* fan = nullptr;

	Cube p_base;
	Cylinder p_fan;

	Hovercaft();
	~Hovercaft();
};


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	Hovercaft* createHovercraft();

public:

	float acceleration;
	float brake;


	//Testing variables

	Hovercaft* car;

};