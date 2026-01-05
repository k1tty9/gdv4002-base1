#include "Snowflake.h"
#include "Engine.h"


extern glm::vec2 gravity;
Snowflake::Snowflake(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f);

	this->angleChangePerSecond = angleChangePerSecond;
}
void Snowflake::update(double tDelta) {

	// 1. Physics bit for movement

	// 1.1. Sum forces - only add gravity for now
	glm::vec2 impulse = glm::vec2(0.0f, 0.0f);

	// Add the same impulse behaviour the Player uses when crossing the viewplane bounds
// (use width for x-tests, height for y-tests)
	float halfViewH = getViewplaneHeight() / 2.0f;
	float halfViewW = getViewplaneWidth() / 2.0f;

	if (position.y < -halfViewH) {
		impulse += glm::vec2(0.0f, 20.0f);
	}
	if (position.y > halfViewH) {
		impulse += glm::vec2(0.0f, -20.0f);
	}
	if (position.x < -halfViewW) {
		impulse += glm::vec2(20.0f, 0.0f);
	}
	if (position.x > halfViewW) {
		impulse += glm::vec2(-20.0f, 0.0f);
	}

	const float fallSpeed = 1.0f; 
	velocity.y = -fallSpeed;

	velocity += impulse.x * (float)tDelta;

	// 1.4. Update position
	position += velocity * (float)tDelta;

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
