#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include "Shader.h"
#include "Model.h"
class ResourceManager
{
public:
	// �洢���е���ɫ��
	static std::map<std::string, Shader> Shaders;
	// ������ɫ��
	static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
	// ��ȡ��ɫ��
	static Shader GetShader(std::string name);
	static void Clear();

	// ģ��
	static std::map<std::string, Model> Models;
	static Model LoadModel(const char *ModelPath, std::string name);
	static Model GetModel(std::string name);

	// ����
	static std::map<std::string, unsigned int> Texture2Ds;
	static unsigned int LoadTexture(char const * path, std::string name);
	static unsigned int GetTexture(std::string name);
private:
	ResourceManager() { }
	static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
	static unsigned int loadTexture(char const * path);
};

#endif