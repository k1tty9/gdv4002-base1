#pragma once
#include "GameObject2D.h"

class Bullet : public GameObject2D {
private:
	glm::vec2 velocity;
	float lifetime; // how long the bullet  lasts in the gameworld

public:
	Bullet(glm::vec2 pos, glm::vec2 vel, float life, glm::vec2 size, GLuint tex);
	void update(double tDelta) override;
};