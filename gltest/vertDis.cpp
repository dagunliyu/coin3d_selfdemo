/*
 * @Description: 
 * @Author: lhc
 * @Date: 2025-09-16 15:41:24
 * @LastEditTime: 2025-09-23 10:42:33
 * @LastEditors: lhc
 * @Reference: 
 */
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <iostream>


// 顶点着色：
// 将vert送入管线，一次操作一个顶点的能力
// 
// 曲面细分着色：
// 
// 几何着色：
// 给programer 一次操作一个图元的能力. 可以同时访问每个三角形的所有顶点
// 
// 栅格化：
// 是在这个阶段，图元(点或三角形)转换成了像素的集合
// 
// 片段着色器
// 所有fragmentShader的目的都是给要显示的像素(栅格化之后的像素)赋予颜色
//  
// 像素操作(利用颜色缓冲区和深度缓冲区zbuffer)
// 隐藏面消除的步骤? 协调颜色和深度缓冲区完成


#define numVAOs 1 

GLuint renderingProgram; 
GLuint vao[numVAOs];

GLuint createShaderProgram()
{ 
    // 被声明为字符串数组
    // 顶点着色器. 每个顶点都会执行一次顶点着色器
    // 所有顶点着色器的主要目标: 都是将顶点发送给管线, 它会对每个顶点进行处理
    // 内置变量 gl_Position 用来设置顶点在 3D 空间中的坐标位置，并将其发送至下一个管线阶段。
    // 给 gl_Position 指定 out 标签不是必需的，因为 gl_Position 是预定义的输出变量
    const char *vshaderSource = 
    "#version 430 \n" 
    "void main(void) \n" 
    "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";


    // 顶点接下来将沿着管线移动到光栅着色器
    // 在这里被转换成像素位置（更精确地说是片段，后文会解释）
    // 最终这些像素（片段）到达片段着色器：

    // 片段着色器
    // 所有片段着色器的目的: 都是给为要展示的像素赋予颜色。
    // 指定的输出颜色值为(0.0, 0.0, 1.0, 1.0)，代表蓝色（第 4 个值 1.0 是不透明度）。注
    // 的 out 标签表明 color 变量是输出变量
    const char *fshaderSource = 
    "#version 430 \n" 
    "out vec4 color; \n" 
    "void main(void) \n" 
    "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

    // 预定义变量gl_FragCoord, 访问输入片段的坐标
    //x 坐标小于 200时是红色，否则就是蓝色
    const char* fshaderCoord = 
    "#version 430 \n"
    "out vec4 color; \n"
    "void main(void) \n"
    "{ if (gl_FragCoord.x < 295) color = vec4(1.0,0.0,0.0,1.0);"
    "  else color = vec4(0.0, 0.0, 1.0, 1.0);"
    "}";

    // “unsigned int”的平台无关简写
    // 创建每个着色器对象（初始值为空）的时候，会返回一个整数 ID 作为后面引用它的序号
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER); 
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 将 GLSL 代码从字符串载入空着色器对象中
    // para1:用来存放着色器的着色器对象、
    // para2:着色器源代码中的字符串数量、
    // para3:包含源代码的字符串 指针，
    // para4:以及一个此处没有用到的参数（我们会在补充说明中解释这个参数）。
    glShaderSource(vShader, 1, &vshaderSource, NULL); 
    glShaderSource(fShader, 1, &fshaderCoord/*fshaderSource*/, NULL); 
    

    // 编译各着色器. 捕获编译着色器时的错误
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;

    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1)
    {
        std::cout << "vertex compilation failed" << std::endl;
    }

    glCompileShader(fShader); 
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1)
    {
        std::cout << "fragment compilation failed" << std::endl;
    }



    // 创建了一个叫作 vfProgram 的程序对象，并储存指向它的整数 ID
    // OpenGL“程序”object, 包含一系列编译过的着色器
    GLuint vfProgram = glCreateProgram();
    
    // 将着色器加入程序对象. 捕获链接着色器时的错误
    glAttachShader(vfProgram, vShader); 
    glAttachShader(vfProgram, fShader);
    
    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1)
    {
        std::cout << "linking failed" << std::endl;
    }
     
    // 请求 GLSL 编译器，以确保它们的兼容性
    glLinkProgram(vfProgram); 

    return vfProgram; 
}

void init(GLFWwindow* window) 
{
    renderingProgram = createShaderProgram(); 

    // 当准备将数据集发送给管线时，数据集是以缓冲区形式发送的
    // 缓冲区最后都会被存入顶点数组对象（Vertex Array Object，VAO）
    // 即使应用程序完全没有用到任何缓冲区，OpenGL 仍然需要在使用着色器的时候拥有至少一个创建好的VAO
    
    // 这两行代码用来创建 OpenGL 要求的 VAO。
    glGenVertexArrays(numVAOs, vao); 
    glBindVertexArray(vao[0]); 
} 

void display(GLFWwindow* window, double currentTime) 
{
    // display()函数所做的事情中包含调用glUseProgram()，
    // 用于将含有两个已编译着色器的程序载入 OpenGL 管线阶段（在 GPU 上！）。
    // 注意，glUseProgram()并没有运行着色器，它只是将着色器加载进硬件。
    glUseProgram(renderingProgram); 
    
    // 栅格化阶段从顶点着色器收到顶点时，会设像素的颜色，组成一个尺寸为 30 像素的点
    //增大 glPointSize
    glPointSize(30.0f);


    // 呈现线框模型
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 发送给管线绘制的模型的顶点集
    // 调用了 glDrawArrays()用来启动管线处理过程。
    // 原始类型是GL_POINTS，仅用来显示一个点。
    glDrawArrays(GL_POINTS, 0, 1); 

} 


int main(void) 
{
    if (!glfwInit()) 
    { 
        exit(EXIT_FAILURE); 
    } 
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    
    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", NULL, NULL); 
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) 
    { 
        exit(EXIT_FAILURE); 
    } 
    
    glfwSwapInterval(1);
    
    init(window); 

    while (!glfwWindowShouldClose(window)) 
    {
        display(window, glfwGetTime()); 
        glfwSwapBuffers(window); 
        glfwPollEvents(); 
    }

    glfwDestroyWindow(window); 
    glfwTerminate(); 
    exit(EXIT_SUCCESS); 
}

// 颜色缓冲区和深度缓冲区(z-buffer)
// GL协调这2个缓冲区，完成隐藏面的消除(即前景挡住后面的物体)
// 这两个缓冲区的大小和屏幕栅格大小相同，屏幕上的每个像素都在这两个缓冲区里有对应的条目

// 绘制场景中的每个元素时, 片段着色器会生成像素颜色
// 像素颜色放在颜色缓冲区中， 最终颜色缓冲区被写入屏幕
// 
