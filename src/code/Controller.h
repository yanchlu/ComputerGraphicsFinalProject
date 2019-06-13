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
	// 加载着色器资源等
	void Init();
	// 处理键盘事件
	void ProcessKeyboradInput();
	// 处理鼠标事件
	void ProcessMouseInput();
	// 更新场景中的物体
	void Update();
	// 渲染物体
	void Render();

	// 管理光源
	Light mainlight;
	// 摄像机
	Camera maincamera;
	// 天空盒
	Skybox mainskybox;
	// 字体
	Text maintext;
	// 屏幕的高宽
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	
	std::vector<BasicObject> Planes;
	std::vector<BasicObject> Boxs;
	std::vector<Model> Models;
};

#endif