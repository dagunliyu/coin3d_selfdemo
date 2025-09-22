/*
 * @Description: 
 * @Author: lhc
 * @Date: 2025-09-22 17:30:06
 * @LastEditTime: 2025-09-22 18:45:21
 * @LastEditors: lhc
 * @Reference: 
 */
#include "GLSLChecker.h"

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

void 
