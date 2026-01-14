/*
 * Rendering Pipeline Example
 * 演示 Coin3D 渲染流程：场景图遍历、状态累积、GPU数据传输
 * 
 * 本示例展示：
 * 1. 场景图的层次结构如何影响渲染状态
 * 2. SoSeparator 如何隔离状态
 * 3. 变换和材质如何累积
 * 4. 打印遍历过程（通过自定义回调）
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/SbMatrix.h>
#include <iostream>

// 回调函数：打印当前渲染状态
void printRenderState(void* userData, SoAction* action)
{
    const char* nodeName = (const char*)userData;
    
    if (action->isOfType(SoGLRenderAction::getClassTypeId())) {
        SoState* state = action->getState();
        
        // 获取当前的模型矩阵（累积的变换）
        const SbMatrix& matrix = SoModelMatrixElement::get(state);
        
        // 提取平移部分
        SbVec3f translation, scale;
        SbRotation rotation, scaleOrientation;
        matrix.getTransform(translation, rotation, scale, scaleOrientation);
        
        std::cout << "渲染节点: " << nodeName << std::endl;
        std::cout << "  累积变换 - 平移: (" 
                  << translation[0] << ", " 
                  << translation[1] << ", " 
                  << translation[2] << ")" << std::endl;
        std::cout << "  累积变换 - 缩放: (" 
                  << scale[0] << ", " 
                  << scale[1] << ", " 
                  << scale[2] << ")" << std::endl;
        std::cout << std::endl;
    }
}

int main(int argc, char** argv)
{
    // 初始化 SoQt
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    std::cout << "=== Coin3D 渲染流程演示 ===" << std::endl;
    std::cout << "本示例展示场景图如何组织数据并传输给GPU" << std::endl;
    std::cout << std::endl;
    
    // 创建根分隔符（场景图根节点）
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // ======= 演示1: 状态累积 =======
    std::cout << "--- 演示1: 状态累积（没有 SoSeparator 隔离）---" << std::endl;
    
    SoSeparator* demo1 = new SoSeparator;
    
    // 第一个变换：平移
    SoTransform* transform1 = new SoTransform;
    transform1->translation.setValue(-4, 2, 0);
    demo1->addChild(transform1);
    
    // 第一个材质：红色
    SoMaterial* material1 = new SoMaterial;
    material1->diffuseColor.setValue(1.0, 0.0, 0.0);
    demo1->addChild(material1);
    
    // 添加回调，打印状态
    SoCallback* callback1 = new SoCallback;
    callback1->setCallback(printRenderState, (void*)"球体1 (红色)");
    demo1->addChild(callback1);
    
    // 第一个球体（使用累积的变换和材质）
    SoSphere* sphere1 = new SoSphere;
    sphere1->radius = 0.5;
    demo1->addChild(sphere1);
    
    // 第二个变换：在前一个变换基础上继续平移
    SoTransform* transform2 = new SoTransform;
    transform2->translation.setValue(2, 0, 0);  // 相对平移
    demo1->addChild(transform2);
    
    // 添加回调
    SoCallback* callback2 = new SoCallback;
    callback2->setCallback(printRenderState, (void*)"球体2 (红色，累积变换)");
    demo1->addChild(callback2);
    
    // 第二个球体（累积了两个变换，继承红色材质）
    SoSphere* sphere2 = new SoSphere;
    sphere2->radius = 0.5;
    demo1->addChild(sphere2);
    
    root->addChild(demo1);
    
    // ======= 演示2: 使用 SoSeparator 隔离状态 =======
    std::cout << "--- 演示2: 使用 SoSeparator 隔离状态 ---" << std::endl;
    
    // 第一个独立的对象组
    SoSeparator* object1 = new SoSeparator;
    {
        SoTransform* trans = new SoTransform;
        trans->translation.setValue(0, 2, 0);
        object1->addChild(trans);
        
        SoMaterial* mat = new SoMaterial;
        mat->diffuseColor.setValue(0.0, 1.0, 0.0);  // 绿色
        object1->addChild(mat);
        
        SoCallback* cb = new SoCallback;
        cb->setCallback(printRenderState, (void*)"立方体 (绿色，独立状态)");
        object1->addChild(cb);
        
        SoCube* cube = new SoCube;
        cube->width = cube->height = cube->depth = 0.8;
        object1->addChild(cube);
    }
    root->addChild(object1);
    
    // 第二个独立的对象组（状态不会受第一个影响）
    SoSeparator* object2 = new SoSeparator;
    {
        SoTransform* trans = new SoTransform;
        trans->translation.setValue(4, 2, 0);
        object2->addChild(trans);
        
        SoMaterial* mat = new SoMaterial;
        mat->diffuseColor.setValue(0.0, 0.0, 1.0);  // 蓝色
        object2->addChild(mat);
        
        SoCallback* cb = new SoCallback;
        cb->setCallback(printRenderState, (void*)"圆锥 (蓝色，独立状态)");
        object2->addChild(cb);
        
        SoCone* cone = new SoCone;
        cone->bottomRadius = 0.5;
        cone->height = 1.2;
        object2->addChild(cone);
    }
    root->addChild(object2);
    
    // ======= 演示3: 自定义几何体（IndexedFaceSet）展示顶点数据 =======
    std::cout << "--- 演示3: 自定义几何体 (展示顶点数据传输) ---" << std::endl;
    
    SoSeparator* customGeometry = new SoSeparator;
    {
        SoTransform* trans = new SoTransform;
        trans->translation.setValue(-4, -2, 0);
        customGeometry->addChild(trans);
        
        SoMaterial* mat = new SoMaterial;
        mat->diffuseColor.setValue(1.0, 1.0, 0.0);  // 黄色
        customGeometry->addChild(mat);
        
        // 定义顶点坐标（一个金字塔）
        SoCoordinate3* coords = new SoCoordinate3;
        coords->point.set1Value(0, SbVec3f(0, 1, 0));      // 顶点
        coords->point.set1Value(1, SbVec3f(-0.5, 0, 0.5)); // 底面1
        coords->point.set1Value(2, SbVec3f(0.5, 0, 0.5));  // 底面2
        coords->point.set1Value(3, SbVec3f(0.5, 0, -0.5)); // 底面3
        coords->point.set1Value(4, SbVec3f(-0.5, 0, -0.5));// 底面4
        customGeometry->addChild(coords);
        
        std::cout << "创建自定义几何体（金字塔）:" << std::endl;
        std::cout << "  顶点数量: 5" << std::endl;
        std::cout << "  面数量: 5 (4个侧面 + 1个底面)" << std::endl;
        std::cout << "  这些数据将通过 OpenGL 传输到 GPU" << std::endl;
        std::cout << std::endl;
        
        // 定义面的索引（使用索引可以重用顶点数据）
        SoIndexedFaceSet* faceSet = new SoIndexedFaceSet;
        
        // 侧面1
        faceSet->coordIndex.set1Value(0, 0);
        faceSet->coordIndex.set1Value(1, 1);
        faceSet->coordIndex.set1Value(2, 2);
        faceSet->coordIndex.set1Value(3, -1);
        
        // 侧面2
        faceSet->coordIndex.set1Value(4, 0);
        faceSet->coordIndex.set1Value(5, 2);
        faceSet->coordIndex.set1Value(6, 3);
        faceSet->coordIndex.set1Value(7, -1);
        
        // 侧面3
        faceSet->coordIndex.set1Value(8, 0);
        faceSet->coordIndex.set1Value(9, 3);
        faceSet->coordIndex.set1Value(10, 4);
        faceSet->coordIndex.set1Value(11, -1);
        
        // 侧面4
        faceSet->coordIndex.set1Value(12, 0);
        faceSet->coordIndex.set1Value(13, 4);
        faceSet->coordIndex.set1Value(14, 1);
        faceSet->coordIndex.set1Value(15, -1);
        
        // 底面
        faceSet->coordIndex.set1Value(16, 1);
        faceSet->coordIndex.set1Value(17, 4);
        faceSet->coordIndex.set1Value(18, 3);
        faceSet->coordIndex.set1Value(19, 2);
        faceSet->coordIndex.set1Value(20, -1);
        
        customGeometry->addChild(faceSet);
    }
    root->addChild(customGeometry);
    
    // ======= 演示4: 复杂的嵌套场景图 =======
    std::cout << "--- 演示4: 嵌套场景图结构 ---" << std::endl;
    
    SoSeparator* nestedDemo = new SoSeparator;
    {
        // 父级变换
        SoTransform* parentTransform = new SoTransform;
        parentTransform->translation.setValue(2, -2, 0);
        nestedDemo->addChild(parentTransform);
        
        // 父级材质
        SoMaterial* parentMaterial = new SoMaterial;
        parentMaterial->diffuseColor.setValue(0.8, 0.4, 0.8);  // 紫色
        nestedDemo->addChild(parentMaterial);
        
        // 子分组1（继承父级状态并添加自己的变换）
        SoSeparator* child1 = new SoSeparator;
        {
            SoTransform* childTrans = new SoTransform;
            childTrans->translation.setValue(-0.8, 0, 0);
            child1->addChild(childTrans);
            
            SoCallback* cb = new SoCallback;
            cb->setCallback(printRenderState, (void*)"嵌套球体1 (继承父级状态)");
            child1->addChild(cb);
            
            SoSphere* sphere = new SoSphere;
            sphere->radius = 0.3;
            child1->addChild(sphere);
        }
        nestedDemo->addChild(child1);
        
        // 子分组2（独立状态）
        SoSeparator* child2 = new SoSeparator;
        {
            SoTransform* childTrans = new SoTransform;
            childTrans->translation.setValue(0.8, 0, 0);
            child2->addChild(childTrans);
            
            // 覆盖材质
            SoMaterial* childMat = new SoMaterial;
            childMat->diffuseColor.setValue(1.0, 0.5, 0.0);  // 橙色
            child2->addChild(childMat);
            
            SoCallback* cb = new SoCallback;
            cb->setCallback(printRenderState, (void*)"嵌套球体2 (覆盖材质)");
            child2->addChild(cb);
            
            SoSphere* sphere = new SoSphere;
            sphere->radius = 0.3;
            child2->addChild(sphere);
        }
        nestedDemo->addChild(child2);
    }
    root->addChild(nestedDemo);
    
    std::cout << "场景图构建完成！" << std::endl;
    std::cout << std::endl;
    std::cout << "场景图将在渲染时被遍历，" << std::endl;
    std::cout << "每个节点的状态会累积并通过 OpenGL 传输到 GPU。" << std::endl;
    std::cout << "请查看上方的状态打印输出。" << std::endl;
    std::cout << std::endl;
    
    // 创建 viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("Rendering Pipeline Demo - 渲染流程演示");
    viewer->show();
    
    // 显示主窗口
    SoQt::show(mainwin);
    
    std::cout << "窗口已打开，首次渲染时会看到状态打印。" << std::endl;
    std::cout << "旋转视图时会触发新的渲染遍历。" << std::endl;
    std::cout << std::endl;
    
    // 进入事件循环
    SoQt::mainLoop();
    
    // 清理
    delete viewer;
    root->unref();
    
    return 0;
}
