/*
 * Scene Graph Example
 * Demonstrates scene graph hierarchy and organization
 * Shows parent-child relationships and grouping
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSwitch.h>

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create root separator (top of scene graph)
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // Create first branch - parent node with children
    SoSeparator* branch1 = new SoSeparator;
    SoTransform* transform1 = new SoTransform;
    transform1->translation.setValue(-2, 0, 0);
    SoMaterial* material1 = new SoMaterial;
    material1->diffuseColor.setValue(1.0, 0.0, 0.0); // Red
    SoSphere* sphere1 = new SoSphere;
    sphere1->radius = 0.8;
    branch1->addChild(transform1);
    branch1->addChild(material1);
    branch1->addChild(sphere1);
    
    // Create second branch - demonstrates grouping
    SoSeparator* branch2 = new SoSeparator;
    SoTransform* transform2 = new SoTransform;
    transform2->translation.setValue(0, 0, 0);
    SoMaterial* material2 = new SoMaterial;
    material2->diffuseColor.setValue(0.0, 1.0, 0.0); // Green
    SoCube* cube = new SoCube;
    cube->width = 1.2;
    cube->height = 1.2;
    cube->depth = 1.2;
    branch2->addChild(transform2);
    branch2->addChild(material2);
    branch2->addChild(cube);
    
    // Create third branch with switch node (can toggle visibility)
    SoSwitch* switchNode = new SoSwitch;
    switchNode->whichChild.setValue(SO_SWITCH_ALL); // Show all children
    SoSeparator* branch3 = new SoSeparator;
    SoTransform* transform3 = new SoTransform;
    transform3->translation.setValue(2, 0, 0);
    SoMaterial* material3 = new SoMaterial;
    material3->diffuseColor.setValue(0.0, 0.0, 1.0); // Blue
    SoSphere* sphere2 = new SoSphere;
    sphere2->radius = 0.8;
    branch3->addChild(transform3);
    branch3->addChild(material3);
    branch3->addChild(sphere2);
    switchNode->addChild(branch3);
    
    // Add all branches to root (building the scene graph)
    root->addChild(branch1);
    root->addChild(branch2);
    root->addChild(switchNode);
    
    // Create viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("Scene Graph Example");
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
