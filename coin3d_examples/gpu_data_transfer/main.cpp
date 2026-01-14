/*
 * GPU Data Transfer Example
 * GPU 数据传输示例
 * 
 * 本示例演示：
 * 1. 不同的几何数据传输方式（SoFaceSet vs SoIndexedFaceSet）
 * 2. 顶点数据的优化（索引重用）
 * 3. 大量对象的性能对比
 * 4. 渲染缓存的使用
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <cmath>
#include <iostream>
#include <chrono>

// 全局计数器用于性能测试
int frameCount = 0;
auto startTime = std::chrono::high_resolution_clock::now();

// 创建一个立方体使用 SoFaceSet（无索引，顶点重复）
SoSeparator* createCubeWithFaceSet()
{
    SoSeparator* sep = new SoSeparator;
    
    // 定义立方体的8个顶点（但我们需要为每个面重复定义）
    SoCoordinate3* coords = new SoCoordinate3;
    
    // 立方体有6个面，每个面4个顶点，共24个顶点（大量重复）
    float vertices[][3] = {
        // 前面 (z = 0.5)
        {-0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, 
        { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
        // 后面 (z = -0.5)
        {-0.5f, -0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f},
        // 顶面 (y = 0.5)
        {-0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f},
        // 底面 (y = -0.5)
        {-0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f},
        // 右面 (x = 0.5)
        { 0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f,  0.5f},
        // 左面 (x = -0.5)
        {-0.5f, -0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}
    };
    
    for (int i = 0; i < 24; i++) {
        coords->point.set1Value(i, vertices[i][0], vertices[i][1], vertices[i][2]);
    }
    sep->addChild(coords);
    
    // 创建面集（6个面，每个面4个顶点）
    SoFaceSet* faceSet = new SoFaceSet;
    for (int i = 0; i < 6; i++) {
        faceSet->numVertices.set1Value(i, 4);
    }
    sep->addChild(faceSet);
    
    std::cout << "SoFaceSet 立方体:" << std::endl;
    std::cout << "  顶点数: 24 (有重复)" << std::endl;
    std::cout << "  内存使用: 24 * 3 * sizeof(float) = " << (24 * 3 * sizeof(float)) << " 字节" << std::endl;
    
    return sep;
}

// 创建一个立方体使用 SoIndexedFaceSet（使用索引，顶点重用）
SoSeparator* createCubeWithIndexedFaceSet()
{
    SoSeparator* sep = new SoSeparator;
    
    // 只定义8个唯一的顶点
    SoCoordinate3* coords = new SoCoordinate3;
    coords->point.set1Value(0, -0.5f, -0.5f,  0.5f); // 0
    coords->point.set1Value(1,  0.5f, -0.5f,  0.5f); // 1
    coords->point.set1Value(2,  0.5f,  0.5f,  0.5f); // 2
    coords->point.set1Value(3, -0.5f,  0.5f,  0.5f); // 3
    coords->point.set1Value(4, -0.5f, -0.5f, -0.5f); // 4
    coords->point.set1Value(5,  0.5f, -0.5f, -0.5f); // 5
    coords->point.set1Value(6,  0.5f,  0.5f, -0.5f); // 6
    coords->point.set1Value(7, -0.5f,  0.5f, -0.5f); // 7
    sep->addChild(coords);
    
    // 使用索引定义面（通过索引重用顶点）
    SoIndexedFaceSet* faceSet = new SoIndexedFaceSet;
    
    // 前面
    faceSet->coordIndex.set1Value(0, 0);
    faceSet->coordIndex.set1Value(1, 1);
    faceSet->coordIndex.set1Value(2, 2);
    faceSet->coordIndex.set1Value(3, 3);
    faceSet->coordIndex.set1Value(4, -1); // 面结束标记
    
    // 后面
    faceSet->coordIndex.set1Value(5, 4);
    faceSet->coordIndex.set1Value(6, 7);
    faceSet->coordIndex.set1Value(7, 6);
    faceSet->coordIndex.set1Value(8, 5);
    faceSet->coordIndex.set1Value(9, -1);
    
    // 顶面
    faceSet->coordIndex.set1Value(10, 3);
    faceSet->coordIndex.set1Value(11, 2);
    faceSet->coordIndex.set1Value(12, 6);
    faceSet->coordIndex.set1Value(13, 7);
    faceSet->coordIndex.set1Value(14, -1);
    
    // 底面
    faceSet->coordIndex.set1Value(15, 0);
    faceSet->coordIndex.set1Value(16, 4);
    faceSet->coordIndex.set1Value(17, 5);
    faceSet->coordIndex.set1Value(18, 1);
    faceSet->coordIndex.set1Value(19, -1);
    
    // 右面
    faceSet->coordIndex.set1Value(20, 1);
    faceSet->coordIndex.set1Value(21, 5);
    faceSet->coordIndex.set1Value(22, 6);
    faceSet->coordIndex.set1Value(23, 2);
    faceSet->coordIndex.set1Value(24, -1);
    
    // 左面
    faceSet->coordIndex.set1Value(25, 0);
    faceSet->coordIndex.set1Value(26, 3);
    faceSet->coordIndex.set1Value(27, 7);
    faceSet->coordIndex.set1Value(28, 4);
    faceSet->coordIndex.set1Value(29, -1);
    
    sep->addChild(faceSet);
    
    std::cout << "SoIndexedFaceSet 立方体:" << std::endl;
    std::cout << "  顶点数: 8 (无重复)" << std::endl;
    std::cout << "  索引数: 30 (包括面结束标记)" << std::endl;
    std::cout << "  内存使用: 8 * 3 * sizeof(float) + 30 * sizeof(int) = " 
              << (8 * 3 * sizeof(float) + 30 * sizeof(int)) << " 字节" << std::endl;
    std::cout << "  节省内存: " 
              << (24 * 3 * sizeof(float) - (8 * 3 * sizeof(float) + 30 * sizeof(int))) 
              << " 字节 (约 " 
              << (100.0 * (1.0 - (8 * 3 * sizeof(float) + 30 * sizeof(int)) / (24 * 3 * sizeof(float))))
              << "%)" << std::endl;
    
    return sep;
}

// 创建复杂网格用于性能测试
SoSeparator* createComplexMesh(bool useIndexed, int subdivisions)
{
    SoSeparator* sep = new SoSeparator;
    
    // 启用渲染缓存以提高性能
    sep->renderCaching = SoSeparator::ON;
    
    SoCoordinate3* coords = new SoCoordinate3;
    
    // 创建一个细分的平面网格
    int gridSize = subdivisions;
    float step = 2.0f / gridSize;
    
    if (useIndexed) {
        // 使用索引方式：只存储唯一顶点
        int vertexIndex = 0;
        for (int i = 0; i <= gridSize; i++) {
            for (int j = 0; j <= gridSize; j++) {
                float x = -1.0f + j * step;
                float z = -1.0f + i * step;
                float y = 0.2f * sin(x * 3.14f) * cos(z * 3.14f); // 波浪形状
                coords->point.set1Value(vertexIndex++, x, y, z);
            }
        }
        sep->addChild(coords);
        
        // 创建索引面
        SoIndexedFaceSet* faceSet = new SoIndexedFaceSet;
        int indexCount = 0;
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                int v0 = i * (gridSize + 1) + j;
                int v1 = v0 + 1;
                int v2 = v0 + (gridSize + 1) + 1;
                int v3 = v0 + (gridSize + 1);
                
                faceSet->coordIndex.set1Value(indexCount++, v0);
                faceSet->coordIndex.set1Value(indexCount++, v1);
                faceSet->coordIndex.set1Value(indexCount++, v2);
                faceSet->coordIndex.set1Value(indexCount++, v3);
                faceSet->coordIndex.set1Value(indexCount++, -1);
            }
        }
        sep->addChild(faceSet);
        
        std::cout << "IndexedFaceSet 网格 (" << subdivisions << "x" << subdivisions << "):" << std::endl;
        std::cout << "  顶点数: " << (gridSize + 1) * (gridSize + 1) << std::endl;
        std::cout << "  面数: " << gridSize * gridSize << std::endl;
        std::cout << "  索引数: " << indexCount << std::endl;
        
    } else {
        // 不使用索引：每个面重复存储顶点
        int vertexIndex = 0;
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                float x0 = -1.0f + j * step;
                float x1 = x0 + step;
                float z0 = -1.0f + i * step;
                float z1 = z0 + step;
                
                float y0 = 0.2f * sin(x0 * 3.14f) * cos(z0 * 3.14f);
                float y1 = 0.2f * sin(x1 * 3.14f) * cos(z0 * 3.14f);
                float y2 = 0.2f * sin(x1 * 3.14f) * cos(z1 * 3.14f);
                float y3 = 0.2f * sin(x0 * 3.14f) * cos(z1 * 3.14f);
                
                coords->point.set1Value(vertexIndex++, x0, y0, z0);
                coords->point.set1Value(vertexIndex++, x1, y1, z0);
                coords->point.set1Value(vertexIndex++, x1, y2, z1);
                coords->point.set1Value(vertexIndex++, x0, y3, z1);
            }
        }
        sep->addChild(coords);
        
        SoFaceSet* faceSet = new SoFaceSet;
        for (int i = 0; i < gridSize * gridSize; i++) {
            faceSet->numVertices.set1Value(i, 4);
        }
        sep->addChild(faceSet);
        
        std::cout << "FaceSet 网格 (" << subdivisions << "x" << subdivisions << "):" << std::endl;
        std::cout << "  顶点数: " << gridSize * gridSize * 4 << " (有大量重复)" << std::endl;
        std::cout << "  面数: " << gridSize * gridSize << std::endl;
    }
    
    return sep;
}

int main(int argc, char** argv)
{
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    std::cout << "=== GPU 数据传输示例 ===" << std::endl;
    std::cout << "本示例展示不同的几何数据组织方式及其对 GPU 传输的影响" << std::endl;
    std::cout << std::endl;
    
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // ===== 演示1: 简单立方体对比 =====
    std::cout << "--- 演示1: 立方体数据对比 ---" << std::endl;
    
    // 左侧：使用 FaceSet（顶点重复）
    SoSeparator* leftCube = new SoSeparator;
    {
        SoTransform* trans = new SoTransform;
        trans->translation.setValue(-2, 2, 0);
        leftCube->addChild(trans);
        
        SoMaterial* mat = new SoMaterial;
        mat->diffuseColor.setValue(1.0, 0.3, 0.3);
        leftCube->addChild(mat);
        
        leftCube->addChild(createCubeWithFaceSet());
    }
    root->addChild(leftCube);
    
    std::cout << std::endl;
    
    // 右侧：使用 IndexedFaceSet（索引重用）
    SoSeparator* rightCube = new SoSeparator;
    {
        SoTransform* trans = new SoTransform;
        trans->translation.setValue(2, 2, 0);
        rightCube->addChild(trans);
        
        SoMaterial* mat = new SoMaterial;
        mat->diffuseColor.setValue(0.3, 1.0, 0.3);
        rightCube->addChild(mat);
        
        rightCube->addChild(createCubeWithIndexedFaceSet());
    }
    root->addChild(rightCube);
    
    std::cout << std::endl;
    
    // ===== 演示2: 复杂网格性能对比 =====
    std::cout << "--- 演示2: 复杂网格性能对比 ---" << std::endl;
    
    int subdivisions = 50; // 50x50 网格
    
    // 左下：不使用索引的复杂网格
    SoSeparator* leftMesh = new SoSeparator;
    {
        SoTransform* trans = new SoTransform;
        trans->translation.setValue(-2, -2, 0);
        trans->scaleFactor.setValue(1.5, 1.5, 1.5);
        leftMesh->addChild(trans);
        
        SoMaterial* mat = new SoMaterial;
        mat->diffuseColor.setValue(0.8, 0.4, 0.8);
        leftMesh->addChild(mat);
        
        leftMesh->addChild(createComplexMesh(false, subdivisions));
    }
    root->addChild(leftMesh);
    
    std::cout << std::endl;
    
    // 右下：使用索引的复杂网格
    SoSeparator* rightMesh = new SoSeparator;
    {
        SoTransform* trans = new SoTransform;
        trans->translation.setValue(2, -2, 0);
        trans->scaleFactor.setValue(1.5, 1.5, 1.5);
        rightMesh->addChild(trans);
        
        SoMaterial* mat = new SoMaterial;
        mat->diffuseColor.setValue(0.4, 0.8, 0.8);
        rightMesh->addChild(mat);
        
        rightMesh->addChild(createComplexMesh(true, subdivisions));
    }
    root->addChild(rightMesh);
    
    std::cout << std::endl;
    std::cout << "===== 总结 =====" << std::endl;
    std::cout << "使用 SoIndexedFaceSet 的优势:" << std::endl;
    std::cout << "1. 减少内存使用（顶点数据不重复）" << std::endl;
    std::cout << "2. 减少 CPU 到 GPU 的数据传输量" << std::endl;
    std::cout << "3. 提高 GPU 缓存效率（顶点重用）" << std::endl;
    std::cout << "4. 特别适合复杂网格和大规模场景" << std::endl;
    std::cout << std::endl;
    std::cout << "Coin3D 内部会将这些数据传输到 GPU:" << std::endl;
    std::cout << "- 传统方式: 使用 glVertex* 立即模式" << std::endl;
    std::cout << "- 现代方式: 使用 VBO (Vertex Buffer Objects)" << std::endl;
    std::cout << "- 索引数据: 使用 IBO (Index Buffer Objects)" << std::endl;
    std::cout << std::endl;
    
    // 创建 viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("GPU Data Transfer Demo - GPU数据传输演示");
    viewer->show();
    
    SoQt::show(mainwin);
    
    std::cout << "场景已创建！" << std::endl;
    std::cout << "- 左上: FaceSet 立方体 (红色，顶点重复)" << std::endl;
    std::cout << "- 右上: IndexedFaceSet 立方体 (绿色，索引优化)" << std::endl;
    std::cout << "- 左下: FaceSet 网格 (紫色，" << subdivisions << "x" << subdivisions << ")" << std::endl;
    std::cout << "- 右下: IndexedFaceSet 网格 (青色，" << subdivisions << "x" << subdivisions << ")" << std::endl;
    std::cout << std::endl;
    std::cout << "提示: 旋转视图时，您可能会注意到右侧对象的渲染更流畅" << std::endl;
    std::cout << "（尤其在更高细分度的网格上）" << std::endl;
    
    SoQt::mainLoop();
    
    delete viewer;
    root->unref();
    
    return 0;
}
