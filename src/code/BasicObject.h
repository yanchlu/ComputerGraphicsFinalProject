#ifndef BASICOBJECT_H
#define BASICOBJECT_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Shader.h"
#include "Camera.h"

// 在OpenGL中基础的物体
class BasicObject
{
public:

	BasicObject(glm::vec3 position, float rotation, glm::vec3 size);
	// 绑定VAO
	void BindVertexArray();
	// VAO
	unsigned int VAO;
	// 对一个平面进行初始化
	void initPlaneVertices();
	// 对一个正方体进行初始化
	void initCubeVertices();
	// 物体对着色器进行设置渲染
	void Render(Shader shader);

	// 物体位置
	glm::vec3   Position;
	// 物体旋转
	float     Rotation;
	// 物体大小
	glm::vec3   Size;
};

#endif