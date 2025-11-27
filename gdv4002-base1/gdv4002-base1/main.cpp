#include "Engine.h"
#include "Keys.h" // setup in chapter 6

// Function prototypes
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods); // setup in chapter 6


// Globals


// Bit flags to track which keys are currently pressed - setup in chapter 6
std::bitset<5> keys{ 0x0 };


int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 512, 512, 5.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	// Setup game objects


	// Setup event handlers
	setKeyboardHandler(myKeyboardHandler);


	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
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

