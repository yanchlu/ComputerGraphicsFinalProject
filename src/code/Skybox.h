#ifndef SKYBOX_H
#define SKYBOX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
class Skybox
{
public:
	Skybox() {};
	Skybox(glm::vec3 position);
	void initSkybox();
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;
	void BindVertexArray();
	glm::vec3 Position;
};

#endif