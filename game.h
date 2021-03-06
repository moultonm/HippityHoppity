#ifndef GAME_H_
#define GAME_H_
#include <exception>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "scene_graph.h"
#include "resource_manager.h"
#include "camera.h"
#include "laser.h"
#include "bomb.h"
#include "helicopter.h"
#include "enemy.h"
#include "doggy.h"
#include "mole.h"
#include "cat.h"
#include "defs.h"

namespace game {
	// Exception type for the game
	class GameException : public std::exception
	{
	private:
		std::string message_;
	public:
		GameException(std::string message) : message_(message) {};
		virtual const char* what() const throw() { return message_.c_str(); };
		virtual ~GameException() throw() {};
	};

	// Game application
	class Game {
	public:
		// Constructor and destructor
		Game(void);
		~Game();
		// Call Init() before calling any other method
		void Init(void);
		// Set up resources for the game
		void SetupResources(void);
		// Set up initial scene
		void SetupScene(void);
		// Run the game: keep the application active
		void MainLoop(void);

		GLuint prgm; //need this to cheesily draw the heli for now
		int game_state;
		SceneNode *title; //cube that displays the title screen
		int turning; //direction player is turning (left,right,up,down)

		// Player stuff
		glm::vec3 player_vel;
		float hp; //player's health
		bool sun; //tells the game if the sun has exploded
		bool tpCam; //third person camera switch

	private:
		// GLFW window
		GLFWwindow* window_;

		// Scene graph containing all nodes to render
		SceneGraph scene_;
		SceneNode* projectiles;

		// Resources available to the game
		ResourceManager resman_;

		// Camera abstraction
		Camera camera_;
		Helicopter heli_;

		// Flag to turn animation on/off
		bool animating_;
		int EnemyID = 0;
		int numEnemies = 0;
		int TreeID = 0;

		float time_since_spawn = 0;

		// Methods to initialize the game
		void InitWindow(void);
		void InitView(void);
		void InitEventHandlers(void);

		void FireLaser();
		void FireBomb();
		void FireTracer();

		std::string RaySphere(glm::vec3 raydir, glm::vec3 raypos);

		// Methods to handle events
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void ResizeCallback(GLFWwindow* window, int width, int height);

		//creates an instance of a 3d cube
		SceneNode *Cube(int type, std::string entity_name, std::string object_name, std::string material_name,
			glm::vec3 rgb = glm::vec3(0.8, 0.8, 0.8), double ttl = 4.0, std::string tex_name = "");
		SceneNode* CreateMole();
		SceneNode* CreateDog();
		SceneNode* CreateTree();
		SceneNode* CreateCat();
		SceneNode* SpawnMole();
		SceneNode* SpawnDog();
		SceneNode* SpawnTree();
		SceneNode* SpawnCat();


	}; // class Game
} // namespace game
#endif // GAME_H_
