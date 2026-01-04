#pragma once
#include "GameObject2D.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

class Player : public GameObject2D {

private:
	float		mass;
	glm::vec2	velocity;
	float angularVelocity = 0.0f;
	float angularAcceleration = 0.0f;

	float momentOfInertia = 1.0f;
	float angularDamping = 0.98f;
	float maxAngularSpeed = glm::radians(1080.0f);

public:
	Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass);

	void update(double tDelta) override;

	void applyTorque(float torque);

};

