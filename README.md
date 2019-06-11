# ComputerGraphicsFinalProject
ComputerGraphicsFinalProject

- 文件目录
```
- bin 存放资源以及可执行程序
  --- resources 存放项目所需要资源
      --- objects 存放项目的模型
      --- shaders 存放项目的着色器glsl
      --- textures 存放项目的纹理
- doc 存放项目文档
- src 存放项目代码以及库
  --- code 存放项目代码
  --- include 存放项目外部头文件
  --- lib 存放项目所需lib

```

- 代码结构
```
main.cpp 程序主要入口
Controller 整个场景的控制着，控制资源加载渲染以及物体，对外部输入可以进行特殊操作
BasicObject OpenGL中基础物体，可以进行顶点初始化、渲染等
Camera 摄像机
Light 光源，拥有自身的位置，初始化和渲染与其他物体不同
Mesh 网格类
Model 模型类，拥有很多网格以及纹理信息，可以进行渲染
ResourceManager 资源管理类，对着色器，模型，纹理进行加载与管理
Shader 着色器类，可以对属性进行设置

``