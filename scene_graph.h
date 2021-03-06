#ifndef SCENE_GRAPH_H_
#define SCENE_GRAPH_H_
#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "scene_node.h"
#include "enemy.h"
#include "resource.h"
#include "bomb.h"
#include "camera.h"
#include "collision_manager.h"
#include "resource_manager.h"
#include <queue>

#define FRAME_BUFFER_WIDTH 1024
#define FRAME_BUFFER_HEIGHT 768

namespace game {
	// Class that manages all the objects in a scene
	class SceneGraph {
	private:
		// Background color
		glm::vec3 background_color_;

	public:
		// Root of the hierarchy
		SceneNode * root_;
		SceneNode* projectiles = NULL;

		SceneGraph(void);
		~SceneGraph();

		glm::vec3 world_tr_corner;
		glm::vec3 world_bl_corner;
		int exploCount = 0; //helps name our bombs for proper deletion

		// Background color
		void SetBackgroundColor(glm::vec3 color);
		glm::vec3 GetBackgroundColor(void) const;

		// Set root of the hierarchy
		void SetRoot(SceneNode *node);
		void AddProjectile(SceneNode* p);
		// Find a scene node with a specific name
		SceneNode *GetNode(std::string node_name) const;
		SceneNode *FindName(std::string node_name) const;

		// Draw the entire scene
		void Draw(Camera *camera);

		// Update entire scene
		void Update(double deltaTime);

		// run collisions on the children of node (the separate entities)
		void CheckCollisions();
		std::vector<std::pair<SceneNode*, glm::vec2*>> CheckRayCollisions(Ray r);

		void SetResourceManager(ResourceManager* rm);
		ResourceManager* rm_;

		// function for if an enemy has raised an attack flag
		void EnemyAttacking(Enemy* e);

		void Remove(std::string node_name); //remove a node with a given name

		glm::vec3 GetRandomBoundedPosition();

		void SetupDrawToTexture(void);
		GLuint frame_buffer_;
		GLuint quad_array_buffer_;
		GLuint texture_;
		GLuint depth_buffer_;
		// Draw the scene into a texture
		void DrawToTexture(Camera *camera, bool sun);
		// Process and draw the texture on the screen
		void DisplayTexture(GLuint program, float hp);

	}; // class SceneGraph
} // namespace game
#endif // SCENE_GRAPH_H_
