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

	// 光的阴影图
	unsigned int SHADOW_WIDTH;
	unsigned int SHADOW_HEIGHT;
	unsigned int depthMap;
	unsigned int depthMapFBO;
	// 光的位置
	glm::vec3 lightPos;
	// 转换到光空间的矩阵
	glm::mat4 lightSpaceMatrix;
	// 渲染
	void Render(Shader shader);


	void BindFramebuffer();
	void BindTexture();
};

#endif