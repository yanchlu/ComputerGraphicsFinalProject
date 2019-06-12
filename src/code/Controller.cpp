#include "Controller.h"


Controller::Controller(int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}
// ������ɫ����Դ��
void Controller::Init()
{
	// ������ɫ��,���ĸ�������shader������
	Shader objShader = ResourceManager::LoadShader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs",nullptr,"objShader");
	
	// ����������ɫ���Ĳ���
	objShader.use();
	objShader.setInt("texture_diffuse1", 0);
	objShader.setInt("shadowMap", 1);

	// ������Ӱ�����ɫ��
	ResourceManager::LoadShader("./resources/shaders/shader_depth.vs", "./resources/shaders/shader_depth.fs", nullptr, "simpleLightShader");

	// ������պе���ɫ��
	Shader skyboxShader = ResourceManager::LoadShader("./resources/shaders/skybox.vs", "./resources/shaders/skybox.fs", nullptr,"skyboxShader");
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	Skybox skybox(glm::vec3(0));
	mainskybox = skybox;
	mainskybox.initSkybox();
	// ������պ�
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

	// ���ز��ʣ��ڶ��������ǲ��ʵ�����
	ResourceManager::LoadTexture("./resources/textures/wood.png","wood");
	ResourceManager::LoadTexture("./resources/textures/glass.jpg", "glass");

	// ����ģ�� 
	Model nano = ResourceManager::LoadModel("./resources/objects/NOVELO_SHEEP/NOVELO_SHEEP.obj","sheep");
	nano.Position = glm::vec3(-3.0f, 0.0f, -2.0f);
	nano.Size = glm::vec3(0.003f);
	Models.push_back(nano);
	
	nano = ResourceManager::LoadModel("./resources/objects/nanosuit/nanosuit.obj", "nanosuit");
	nano.Position = glm::vec3(0.0f, -0.5f, -2.0f);
	nano.Size = glm::vec3(0.2f);
	Models.push_back(nano);


	// ���������λ��
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	maincamera = camera;


	// ����һ��ƽ��
	BasicObject plane(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	plane.initPlaneVertices();
	Planes.push_back(plane);

	// ����һ������
	BasicObject box1(glm::vec3(0.0f, 1.5f, 0.0), 0.0f, glm::vec3(0.5f));
	box1.initCubeVertices();
	Boxs.push_back(box1);

	// ����һ������
	BasicObject box2(glm::vec3(2.0f, 0.0f, 1.0), 0.0f, glm::vec3(0.5f));
	box2.initCubeVertices();
	Boxs.push_back(box2);

	// ����һ������
	BasicObject box3(glm::vec3(-1.0f, 0.0f, 2.0), glm::radians(60.0f), glm::vec3(0.25f));
	box3.initCubeVertices();
	Boxs.push_back(box3);

	// ������Դ
	Light light(1024,1024, glm::vec3(-2.0f, 4.0f, -1.0f));
	mainlight = light;
}
// ��������¼�
void Controller::ProcessKeyboradInput()
{

}
// ��������¼�
void Controller::ProcessMouseInput()
{

}

// ���³����е�����
void Controller::Update()
{

}
// ��Ⱦ����
void Controller::Render()
{
	// ���ȼ��������ͼ
	mainlight.Render(ResourceManager::GetShader("simpleLightShader"));
	glViewport(0, 0, mainlight.SHADOW_WIDTH, mainlight.SHADOW_HEIGHT);
	mainlight.BindFramebuffer();
	glClear(GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("glass"));
	// ��ƽ��ת������ռ�
	for (int i = 0; i < Planes.size(); i++)
	{
		Planes[i].Render(ResourceManager::GetShader("simpleLightShader"));
		Planes[i].BindVertexArray();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("wood"));
	// ������ת������ռ�
	for (int i = 0; i < Boxs.size(); i++)
	{
		Boxs[i].Render(ResourceManager::GetShader("simpleLightShader"));
		Boxs[i].BindVertexArray();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// ��ģ��ת������ռ�
	for (int i = 0; i < Models.size(); i++)
	{
		Models[i].Draw(ResourceManager::GetShader("simpleLightShader"));
	}

	// �����ӿ�
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �Գ�����ɫ��������Ⱦ
	Shader shader = ResourceManager::GetShader("objShader");
	ResourceManager::GetShader("objShader").use();
	glm::mat4 projection = glm::perspective(glm::radians(maincamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = maincamera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	// ���ù�Ĳ���
	shader.setVec3("viewPos", maincamera.Position);
	shader.setVec3("lightPos", mainlight.lightPos);
	shader.setMat4("lightSpaceMatrix", mainlight.lightSpaceMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("glass"));
	glActiveTexture(GL_TEXTURE1);
	mainlight.BindTexture();

	//������������Ⱦ
	for (int i = 0; i < Planes.size(); i++)
	{
		Planes[i].Render(shader);
		Planes[i].BindVertexArray();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("wood"));

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

	// ��Ⱦ��պ�
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
}