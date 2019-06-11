#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Shader.h"
#include "ResourceManager.h"
class Light
{
public:
	Light(){}
	Light(unsigned int width, unsigned int height, glm::vec3 lightpos);

	// �����Ӱͼ
	unsigned int SHADOW_WIDTH;
	unsigned int SHADOW_HEIGHT;
	unsigned int depthMap;
	unsigned int depthMapFBO;
	// ���λ��
	glm::vec3 lightPos;
	// ת������ռ�ľ���
	glm::mat4 lightSpaceMatrix;
	// ��Ⱦ
	void Render(Shader shader);


	void BindFramebuffer();
	void BindTexture();
};

#endif