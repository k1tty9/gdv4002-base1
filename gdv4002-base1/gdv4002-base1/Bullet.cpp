#include "Bullet.h"
#include "Engine.h"

Bullet::Bullet(glm::vec2 pos, glm::vec2 vel, float life, glm::vec2 size, GLuint tex) : GameObject2D(pos, 0.0f, size, tex), velocity(vel), lifetime(life) {}

void Bullet::update(double tDelta) {
	position += velocity * (float)tDelta;
	lifetime -= (float)tDelta;

	float halfH = getViewplaneHeight() * 0.5f;
	if (lifetime <= 0.0f || position.y < -halfH - 1.0f || position.y > halfH + 1.0f) {
		deleteObject(this);
		return;
	}
}
	
