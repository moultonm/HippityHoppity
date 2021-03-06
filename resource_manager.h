#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_
#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "resource.h"
#include "CImg-2.1.6_pre110917\CImg.h"
#include "model_loader.h"

// Default extensions for different shader source files
#define VERTEX_PROGRAM_EXTENSION "_vp.glsl"
#define FRAGMENT_PROGRAM_EXTENSION "_fp.glsl"
#define GEOMETRY_PROGRAM_EXTENSION "_gp.glsl"

namespace game {
	// Class that manages all resources
	class ResourceManager {
	public:
		// Generic methods
		ResourceManager(void);
		~ResourceManager();
		// Add a resource that was already loaded and allocated to memory
		void AddResource(ResourceType type, const std::string name, GLuint resource, GLsizei size);
		void AddResource(ResourceType type, const std::string name, GLuint array_buffer, GLuint element_array_buffer, GLsizei size, Hitbox _hb = Hitbox());
		// Load a resource from a file, according to the specified type
		void LoadResource(ResourceType type, const std::string name, const char *filename);
		// Get the resource with the specified name
		Resource *GetResource(const std::string name) const;

		// Methods to create specific resources
		void CreateTorus(std::string object_name, float loop_radius = 0.6, float circle_radius = 0.2, int num_loop_samples = 90, int num_circle_samples = 30);
		void CreateSphere(std::string object_name, float radius = 0.6, int num_samples_theta = 90, int num_samples_phi = 45);
		void CreateCube(std::string object_name);
		void CreateGround(std::string object_name); //terrain mesh
		void CreateCylinder(std::string object_name, float cylinder_height = 1, float circle_radius = 1, int num_circle_samples = 90);
		void CreateSphereParticles(std::string object_name, int num_particles = 20000);
		void CreateLineParticles(std::string object_name, int num_particles = 20000, float loop_radius = 0.6, float circle_radius = 0.2);

		Hitbox genHitbox(std::vector<glm::vec3> points);

	private:
		// List storing all resources
		std::vector<Resource*> resource_;

		// Load shaders programs
		void LoadMaterial(const std::string name, const char *prefix);
		// Load a text file into memory (could be source code)
		std::string LoadTextFile(const char *filename);
		void LoadTexture(const std::string name, const char *filename);
		void LoadMesh(const std::string name, const char *filename);
	}; // class ResourceManager
} // namespace game
#endif // RESOURCE_MANAGER_H_
