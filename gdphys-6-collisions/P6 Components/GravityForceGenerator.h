#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator : public ForceGenerator
{
private:
	//CHANGE GRAVITY VALUE HERE
	PhysVector gravity = PhysVector(0, -9.8); // -9.8 means 9.8 m/s^2 down
public:
	GravityForceGenerator(PhysVector g) : gravity(g) {};
	GravityForceGenerator() {}

	void updateForce(PhysParticle* p, float time) override;
};

