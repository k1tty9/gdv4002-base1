#include "Snowflake.h"
#include "Engine.h"


extern glm::vec2 snowflakeGravity;
Snowflake::Snowflake(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond, glm::vec2 initVelocity) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;
	velocity = initVelocity;

	this->angleChangePerSecond = angleChangePerSecond;
}
void Snowflake::update(double tDelta) {

	// 1. Physics bit for movement

	// 1.1. Sum forces - only add gravity for now
	glm::vec2 accel = snowflakeGravity;

	velocity += accel * (float)tDelta;
	position += velocity * (float)tDelta;

	// wrap anound screen rather than bounce
	{
		float viewW = getViewplaneWidth();
		float viewH = getViewplaneHeight();
		float halfW = viewW * 0.5f;
		float halfH = viewH * 0.5f;

		float spawnMargin = viewH * 0.12f;

		float outX = halfW + (size.x * 0.5f);
		float outY = halfH + (size.y * 0.5f);

		while (position.x < -outX) position.x += viewW;
		while (position.x > outX)  position.x -= viewW;
		while (position.y < -outY) position.y += viewH;
		while (position.y > outY)  position.y -= viewH;
	}

	// 2. Non-physics bit for rotation
	orientation += angleChangePerSecond * (float)tDelta;
}
