#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Camera.h"
#include "BasicObject.h"
#include "Light.h"
#include "ResourceManager.h"
#include "BasicObject.h"
#include "Model.h"
#include "Skybox.h"
#include "Text.h"

class Controller
{
public:
	Controller(int width, int height);
	// ������ɫ����Դ��
	void Init();
	// ��������¼�
	void ProcessKeyboradInput();
	// ��������¼�
	void ProcessMouseInput();
	// ���³����е�����
	void Update();
	// ��Ⱦ����
	void Render();

	// �����Դ
	Light mainlight;
	// �����
	Camera maincamera;
	// ��պ�
	Skybox mainskybox;
	// ����
	Text maintext;
	// ��Ļ�ĸ߿�
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	
	std::vector<BasicObject> Planes;
	std::vector<BasicObject> Boxs;
	std::vector<Model> Models;
};

#endif