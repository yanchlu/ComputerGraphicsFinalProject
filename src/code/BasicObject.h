#ifndef BASICOBJECT_H
#define BASICOBJECT_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Shader.h"
#include "Camera.h"

// ��OpenGL�л���������
class BasicObject
{
public:

	BasicObject(glm::vec3 position, float rotation, glm::vec3 size);
	// ��VAO
	void BindVertexArray();
	// VAO
	unsigned int VAO;
	// ��һ��ƽ����г�ʼ��
	void initPlaneVertices();
	// ��һ����������г�ʼ��
	void initCubeVertices();
	// �������ɫ������������Ⱦ
	void Render(Shader shader);

	// ����λ��
	glm::vec3   Position;
	// ������ת
	float     Rotation;
	// �����С
	glm::vec3   Size;
};

#endif