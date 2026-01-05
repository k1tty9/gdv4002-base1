#include "Player.h"
#include "Keys.h"
#include <bitset>
#include "Engine.h"
#include <glm/gtc/constants.hpp>
#include <cmath>
#include "Bullet.h"

extern std::bitset<5> keys;
extern glm::vec2 playerGravity;
void Player::applyTorque(float torque) {
	angularAcceleration = torque / momentOfInertia;
}

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;

	velocity = glm::vec2(0.0f, 0.0f); // default to 0 velocity

}

void Player::update(double tDelta) {

	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	const float thrust = 0.25f;

	// 1. accumulate forces
	if (keys.test(Key::W) == true) {

		F += glm::vec2(0.0f, thrust);
	}
	if (keys.test(Key::S) == true) {

		F += glm::vec2(0.0f, -thrust);
	}
	if (keys.test(Key::A) == true) {

		F += glm::vec2(-thrust, 0.0f);
	}
	if (keys.test(Key::D) == true) {

		F += glm::vec2(thrust, 0.0f);

	}
	//adds gravity to the forces being applied
	F += playerGravity;

	// add impulse force
	if (position.y < -getViewplaneHeight() / 2.0f) {

		F += glm::vec2(0.0f, 20.0f);
	}
	if (position.y > getViewplaneHeight() / 2.0f) {
		F += glm::vec2(0.0f, -20.0f);
	}
	if (position.x < -getViewplaneHeight() / 2.0f) {
		F += glm::vec2(20.0f, 0.0f);
	}
	if (position.x > getViewplaneHeight() / 2.0f) {
		F += glm::vec2(-20.0f, 0.0f);
	}

	float dt = static_cast<float>(tDelta);
	const float torqueHold = 0.12f;
	float torque = 0.0f;
	if (keys[Key::A]) torque += torqueHold;
	if (keys[Key::D]) torque -= torqueHold;

	applyTorque(torque);
	angularVelocity += angularAcceleration * dt;

	float dampingFactor = std::pow(angularDamping, dt * 1.0f);
	angularVelocity *= dampingFactor;

	if (!keys[Key::A] && !keys[Key::D]) {
		const float stopThreshold = glm::radians(0.05f); // small rad/s threshold
		if (std::fabs(angularVelocity) < stopThreshold) angularVelocity = 0.0f;
	}

	if (angularVelocity > maxAngularSpeed) angularVelocity = maxAngularSpeed;
	else if (angularVelocity < -maxAngularSpeed) angularVelocity = -maxAngularSpeed;

	orientation += angularVelocity * dt;

	const float TWO_PI = glm::two_pi<float>();
	orientation = std::fmodf(orientation, TWO_PI);
	if (orientation < 0.0f) orientation += TWO_PI;

	GameObject2D::update(tDelta);
	
	
	// 2. calculate acceleration.  If f=ma, a = f/m
	glm::vec2 a = F * (1.0f / mass);

	// 3. integate to get new velocity
	velocity = velocity + (a * (float)tDelta);

	// 4. integrate to get new position
	position = position + (velocity * (float)tDelta);

	{
		float viewW = getViewplaneWidth();
		float viewH = getViewplaneHeight();
		float halfW = viewW * 0.5f;
		float halfH = viewH * 0.5f;
		while (position.x < -halfW) position.x += viewW;
		while (position.x > halfW)  position.x -= viewW;
		while (position.y < -halfH) position.y += viewH;
		while (position.y > halfH)  position.y -= viewH;
	}

	fireTimer -= dt;
	if (keys.test(Key::SPACE) && fireTimer <= 0.0f) {
		fireTimer = fireCooldown;

		glm::vec2 dir = glm::vec2(std::cos(orientation), std::sin(orientation));

		float forwardOffset = size.y * 0.5f + 0.05f;
		glm::vec2 spawnPos = position + dir * forwardOffset;

		glm::vec2 spawnVel = dir * bulletSpeed + velocity;

		GLuint bulletTex = loadTexture("Resources\\Textured\\Bullet.png");

		Bullet* b = new Bullet(spawnPos, spawnVel, 3.0f, glm::vec2(0.05f, 0.05f), bulletTex);
		addObject("bullet", b);
	}

}
