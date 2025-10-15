#pragma once

#include <GL/glew.h> 

//当 GLSL 代码编译失败时，显示 OpenGL 日志内容
void printShaderLog(GLuint shader);

//当 GLSL 链接失败时，显示 OpenGL 日志内容
void printProgramLog(int prog);

//检查 OpenGL 错误标志，即是否发生 OpenGL 错误
//checkOpenGLError()既用于检测 GLSL 代码编译错误，又用于检测 OpenGL 运行时的错误
//以确保捕获到所有拼写错误和编译错误，同时知道错误原因
bool checkOpenGLError();