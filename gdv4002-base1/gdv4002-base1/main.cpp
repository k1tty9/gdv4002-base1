#include "Engine.h"
#include "keys.h"
#include <bitset>

// Function prototypes
float enemyPhase[3] = { 0.0f, 0.0f, 0.0f };
float enemyPhaseVelocity[3] = { glm::radians(90.0f),
							   glm::radians(90.0f),
							   glm::radians(90.0f) };
void myUpdate(GLFWwindow* window, double tDelta);

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void) {

	std::bitset <5> keys{ 0x0 };

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}
	setUpdateFunction(myUpdate); // set the update function for the engine
	setKeyboardHandler(myKeyboardHandler); // set the keyboard handler function for the engine
	//
	// Setup game scene objects here
	//
	//GameObject2D* playerObject = getObject("player");
//	if(playerObject != nullptr) 
	//{
	//}
	//addObject("player", glm::vec2(1.0f, 1.0f), // adds the object and appoints it a position
	//	45.0f * 3.14159 / 180.0f, // adds the orientation to the player object (same as glm::radians(45.0f))
	//	glm::vec2(0.5f, 1.0f), // adjusts the sixe of the player object
	//	"Resources\\Textures\\mcblock01.png", // adds a sprite to the player object
	//	TextureProperties::NearestFilterTexture());
	

	//addObject("player2");
	//GameObject2D* player2Object = getObject("player2");
	//if (player2Object != nullptr)
	//{
		
	//}
	//player2Object->position = glm::vec2(-1.5f, 1.0f);
	//player2Object->orientation = 30.0f * 3.14159f / 180.0f;
	//player2Object->size = glm::vec2(0.5f, 1.0f);

	addObject("player", glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 
	0.5f), "Resources\\Textures\\player1_ship.png");

	addObject("enemy", glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.75f, 
	0.75f), "Resources\\Textures\\alien01.png");

	addObject("enemy", glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.75f, 
	0.75f), "Resources\\Textures\\alien01.png");

	addObject("enemy", glm::vec2(2.0f, 0.0f), 0.0f, glm::vec2(0.75f, 
	0.75f), "Resources\\Textures\\alien01.png");

	listGameObjectKeys();
	listObjectCounts();
		;	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}
//void myUpdate(GLFWwindow* window, double tDelta) {

//	float playerRotationSpeed = glm::radians(90.0f);
//	GameObject2D* player = getObject("player");
//	player -> orientation += playerRotationSpeed * tDelta;
//}
void myUpdate(GLFWwindow* window, double tDelta) 
{
	GameObjectCollection enemies = getObjectCollection("enemy");
	for (int i = 0; i < enemies.objectCount; i++) {
		enemies.objectArray[i]->position.y = sinf(enemyPhase[i]);
		enemyPhase[i] += enemyPhaseVelocity[i] * tDelta;
	}
}
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;

		case GLFW_KEY_W:
			printf("w pressed \n");
			keys [ Key::W ] = true;
			break;
			
		
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key)
		{
		case GLFW_KEY_W:
			printf("w released \n");
			keys [ Key::W ] = false;
			break;
		}
	}
}

