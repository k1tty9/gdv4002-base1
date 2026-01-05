#include "Emitter.h"
#include "Engine.h"
#include "Snowflake.h"


using namespace std;


Emitter::Emitter(glm::vec2 initPosition, glm::vec2 initSize, float emitTimeInterval) : GameObject2D(initPosition, 0.0f, initSize, 0) {

	this->emitTimeInterval = emitTimeInterval;
	emitCounter = emitTimeInterval;

	particleNumber = 0;

	string path = "Resources\\Textures\\asteroid.png";
		snowflakeTexture = loadTexture(path.c_str());

		if (snowflakeTexture > 0)
			cout << "successfully loaded texture " << path << endl;
		else
			cout << "failed to load texture " << path << endl;
	

	// Obtain a seed for the random number engine
	random_device rd;

	// Standard mersenne_twister_engine seeded with rd() - mt19937 is a high-quality pseudo-random number generator
	gen = mt19937(rd());

	normDist = uniform_real_distribution<float>(-1.0f, 1.0f);
	massDist = uniform_real_distribution<float>(0.005f, 0.08f);
	scaleDist = uniform_real_distribution<float>(0.1f, 0.5f);

}

void Emitter::render() {
	// Do nothing, as the emitter does not render anything.
}

void Emitter::update(double tDelta) {

	emitCounter += (float)tDelta;

	string key = string("snowflake");
	if (particleNumber == 0) {
		key += to_string(particleNumber);
	}

	while (emitCounter >= emitTimeInterval) {

		int currentCount = getObjectCounts("snowflake");
		if (currentCount >= (int)maxParticles) {

			break;
		}

		// decrease emitCounter by emitTimeInterval - don't set to 0 as this would ignore the case where multiple particles are needed.
		emitCounter -= emitTimeInterval;

		// Create new particle

		float x = position.x + normDist(gen) * size.x;
		float y = position.y + normDist(gen) * size.y;
		float scale = 0.25f;
		float mass = 1.0f;
		float rotationSpeed = glm::radians(normDist(gen) * 45.0f);

		string key = string("snowflake") + to_string(particleNumber++);
		Snowflake* s1 = new Snowflake(glm::vec2(x, y), 0.0f, glm::vec2(scale, scale), snowflakeTexture, mass, rotationSpeed);
		addObject(key.c_str(), s1);
	}

}
