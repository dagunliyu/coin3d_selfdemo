/*
 * @Description: 
 * @Author: lhc
 * @Date: 2025-09-22 17:30:06
 * @LastEditTime: 2025-09-23 10:56:16
 * @LastEditors: lhc
 * @Reference: 
 */
#include "GLSLChecker.h"

// 着色器运行时错误的常见结果是输出屏幕上完全空白，根本没有输出。即使是着色器中的一
// 个小拼写错误也可能导致这种结果，这样就很难断定是在哪个管线阶段发生了错误。在没有任
// 何输出的情况下，找到错误的成因就像大海捞针。

// 有一些技巧可以推测着色器代码运行错误的原因，其中一种就是暂时将片段着色器换成程序vertDis中的片段着色器。
// 片段着色器仅输出一个特定颜色，例如将其设置成蓝色，那么如果后来的输出中的几何形状正确，但是全显示为蓝色，那么顶点着色器应该是正确的，
// 错误应该发生在片段着色器；
// 如果输出的仍然是空白屏幕，那么错误很可能发生在管线的更早期，例如顶点着色器。
void printShaderLog(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	// 查询着色器对象的参数信息
	// GL_COMPILE_STATUS 编译状态
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

void printProgramLog(int prog)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char *)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}	
}

bool checkOpenGLError()
{
	bool foundError = false;
	int glErr = glGetError();
	while(glErr != GL_NO_ERROR)
	{
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}
