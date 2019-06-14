﻿#include "Controller.h"


Controller::Controller(int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}
// 加载着色器资源等
void Controller::Init()
{
	// 加载着色器,第四个参数是shader的名字
	Shader objShader = ResourceManager::LoadShader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs",nullptr,"objShader");
	
	// 设置物体着色器的参数
	objShader.use();
	objShader.setInt("texture_diffuse1", 0);
	objShader.setInt("shadowMap", 1);

	// 加载阴影深度着色器
	ResourceManager::LoadShader("./resources/shaders/shader_depth.vs", "./resources/shaders/shader_depth.fs", nullptr, "simpleLightShader");

	// 加载天空盒的着色器
	Shader skyboxShader = ResourceManager::LoadShader("./resources/shaders/skybox.vs", "./resources/shaders/skybox.fs", nullptr,"skyboxShader");
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	Skybox skybox(glm::vec3(0));
	mainskybox = skybox;
	mainskybox.initSkybox();
	// 加载天空盒
	vector<std::string> faces
	{
		"resources/textures/ely_hills/right.tga",
		"resources/textures/ely_hills/left.tga",
		"resources/textures/ely_hills/top.tga",
		"resources/textures/ely_hills/bottom.tga",
		"resources/textures/ely_hills/front.tga",
		"resources/textures/ely_hills/back.tga"
	};
	ResourceManager::loadCubemap(faces,"skybox");

	// 加载材质，第二个参数是材质的名字
	ResourceManager::LoadTexture("./resources/textures/wood.png","wood");
	ResourceManager::LoadTexture("./resources/textures/glass.jpg", "glass");

	// 加载模型 
	Model nano = ResourceManager::LoadModel("./resources/objects/NOVELO_SHEEP/NOVELO_SHEEP.obj","sheep");
	nano.Position = glm::vec3(-3.0f, 1.0f, -2.0f);
	nano.Size = glm::vec3(0.003f);
	Models.push_back(nano);
	
	nano = ResourceManager::LoadModel("./resources/objects/nanosuit/nanosuit.obj", "nanosuit");
	nano.Position = glm::vec3(0.0f, -0.5f, -2.0f);
	nano.Size = glm::vec3(0.2f);
	Models.push_back(nano);


	// 设置摄像机位置
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	maincamera = camera;


	// 创建一个平地
	BasicObject plane(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	plane.initPlaneVertices();
	Planes.push_back(plane);

	// 创建一个盒子
	BasicObject box1(glm::vec3(0.0f, 1.5f, 0.0), 0.0f, glm::vec3(0.5f));
	box1.initCubeVertices();
	Boxs.push_back(box1);

	// 创建一个盒子
	BasicObject box2(glm::vec3(2.0f, 0.0f, 1.0), 0.0f, glm::vec3(0.5f));
	box2.initCubeVertices();
	Boxs.push_back(box2);

	// 创建一个盒子
	BasicObject box3(glm::vec3(-1.0f, 0.0f, 2.0), glm::radians(60.0f), glm::vec3(0.25f));
	box3.initCubeVertices();
	Boxs.push_back(box3);

	// 创建光源
	Light light(1024,1024, glm::vec3(-2.0f, 4.0f, -1.0f));
	mainlight = light;


	// 加载字体着色器
	Shader shader = ResourceManager::LoadShader("./resources/shaders/text.vs", "./resources/shaders/text.fs", nullptr, "text");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SCR_WIDTH), 0.0f, static_cast<GLfloat>(SCR_HEIGHT));
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// 加载英文字体
	Text text(SCR_WIDTH, SCR_HEIGHT);
	maintext = text;
	maintext.InitText();

	// 加载模板测试着色器
	ResourceManager::LoadShader("./resources/shaders/stencil_testing.vs", "./resources/shaders/stencil_testing.fs",nullptr,"stencil");
	stencilScale = 1.06;           // 模板测试的边框粗细
	isOpenStencilTest = false;      // 开启模板测试

}
// 处理键盘事件
void Controller::ProcessKeyboradInput()
{

}
// 处理鼠标事件
void Controller::ProcessMouseInput()
{

}

// 更新场景中的物体
void Controller::Update()
{

}
// 渲染物体
void Controller::Render()
{
	// 关闭模板测试效果
	glStencilMask(0x00);

	// --------------------------------------对场景中物体进行光空间转换-----------------------------
	// 首先计算光的深度图
	mainlight.Render(ResourceManager::GetShader("simpleLightShader"));
	glViewport(0, 0, mainlight.SHADOW_WIDTH, mainlight.SHADOW_HEIGHT);
	mainlight.BindFramebuffer();
	glClear(GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("glass"));
	// 将平面转换到光空间
	for (int i = 0; i < Planes.size(); i++)
	{
		Planes[i].Render(ResourceManager::GetShader("simpleLightShader"));
		Planes[i].BindVertexArray();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("wood"));
	// 将盒子转换到光空间
	for (int i = 0; i < Boxs.size(); i++)
	{
		Boxs[i].Render(ResourceManager::GetShader("simpleLightShader"));
		Boxs[i].BindVertexArray();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
	// 将模型转换到光空间
	for (int i = 0; i < Models.size(); i++)
	{
		Models[i].Draw(ResourceManager::GetShader("simpleLightShader"));
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 重置视口
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// --------------------------------------对场景中物体进行渲染-----------------------------
	// 对场景着色器进行渲染
	Shader shader = ResourceManager::GetShader("objShader");
	ResourceManager::GetShader("objShader").use();
	glm::mat4 projection = glm::perspective(glm::radians(maincamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = maincamera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	// 设置光的参数
	shader.setVec3("viewPos", maincamera.Position);
	shader.setVec3("lightPos", mainlight.lightPos);
	shader.setMat4("lightSpaceMatrix", mainlight.lightSpaceMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("glass"));
	glActiveTexture(GL_TEXTURE1);
	mainlight.BindTexture();

	// 进行平面真正的渲染
	for (int i = 0; i < Planes.size(); i++)
	{
		Planes[i].Render(shader);
		Planes[i].BindVertexArray();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("wood"));


	//--------------------------------------进行场景摆放物体的渲染---------------------
	if (isOpenStencilTest)        // 进行模板测试的配置
	{
		Shader shaderSingleColor = ResourceManager::GetShader("stencil");
		shaderSingleColor.use();
		shaderSingleColor.setMat4("view", view);
		shaderSingleColor.setMat4("projection", projection);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
	}

	for (int i = 0; i < Boxs.size(); i++)
	{
		Boxs[i].Render(shader);
		Boxs[i].BindVertexArray();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	
	for (int i = 0; i < Models.size(); i++)
	{
		Models[i].Draw(shader);
	}

	glStencilMask(0x00);
	// -------------------------------渲染天空盒-------------------------------------------------------
	// draw skybox as last
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	Shader skyboxShader = ResourceManager::GetShader("skyboxShader");
	skyboxShader.use();
	view = glm::mat4(glm::mat3(maincamera.GetViewMatrix())); // remove translation from the view matrix
	skyboxShader.setMat4("view", view);
	skyboxShader.setMat4("projection", projection);
	// skybox cube
	mainskybox.BindVertexArray();
	//glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ResourceManager::GetTexture("skybox"));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default



	// --------------------------------显示文字------------------------------------------------------------------
	Shader text = ResourceManager::GetShader("text");
	maintext.RenderText(text, L"按下 W/A/S/D 键开始漫游", 25.0f, 62.0, 0.6f, glm::vec3(0.968f, 0.917f, 0.639f));
	maintext.RenderText(text, L"拖动鼠标进行视角移动", 25.0f, 25.0, 0.6f, glm::vec3(0.968f, 0.917f, 0.639f));


	// --------------------------------渲染模板测试--------------------------------------------------------
	if (isOpenStencilTest)
	{
		// 在模板着色器中显示各个物体的边框
		Shader shaderSingleColor = ResourceManager::GetShader("stencil");
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		shaderSingleColor.use();

		for (int i = 0; i < Boxs.size(); i++)
		{
			Boxs[i].Render(shaderSingleColor, stencilScale);     // 设置线条粗细
			Boxs[i].BindVertexArray();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}

		for (int i = 0; i < Models.size(); i++)
		{
			Models[i].Draw(shaderSingleColor, stencilScale);
		}

		glBindVertexArray(0);
		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);
	}
}