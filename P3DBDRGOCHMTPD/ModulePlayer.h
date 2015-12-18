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

	btHingeConstraint* fanHinge;

	vec3 baseSize;
	vec2 fanSize;
	float force;
	vec3 fanTorque;
	Hovercaft(vec3, vec2);
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

	//Camera Variables
	mat4x4 pivot;
	float speed_cam;
	vec3 hovercraft_pos;
	btVector3 hovercraft_vector;
	vec3 hovercraft_f;
	vec3 dist_to_hovercraft;
	vec3 camera_new_pos;
	vec3 camera_pos;
	vec3 reference;
};