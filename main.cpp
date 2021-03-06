//COMP3501 Final Project - Hippity Hoppity
#include <iostream>
#include <exception>
#include <time.h>
#include "game.h"

// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

// Main function that builds and runs the game
int main(void) {
	game::Game app; // Game application
	srand(time(NULL));
	try {
		// Initialize game
		app.Init();
		// Setup the main resources and scene in the game
		app.SetupResources();
		app.SetupScene();
		// Run game
		app.MainLoop();
	}
	catch (std::exception &e) {
		PrintException(e);
	}
	return 0;
}