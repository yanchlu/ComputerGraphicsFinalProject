#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include "Shader.h"
#include "Model.h"
class ResourceManager
{
public:
	// 存储所有的着色器
	static std::map<std::string, Shader> Shaders;
	// 加载着色器
	static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
	// 获取着色器
	static Shader GetShader(std::string name);
	static void Clear();

	// 模型
	static std::map<std::string, Model> Models;
	static Model LoadModel(const char *ModelPath, std::string name);
	static Model GetModel(std::string name);

	// 纹理
	static std::map<std::string, unsigned int> Texture2Ds;
	static unsigned int LoadTexture(char const * path, std::string name);
	static unsigned int GetTexture(std::string name);
private:
	ResourceManager() { }
	static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
	static unsigned int loadTexture(char const * path);
};

#endif