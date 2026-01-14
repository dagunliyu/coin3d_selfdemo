/*
 * Basic Shapes Example
 * Demonstrates how to create primitive shapes using Coin3D
 * Includes: Sphere, Cube, Cone, Cylinder
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create root node
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // Create a sphere
    SoSeparator* sphereSep = new SoSeparator;
    SoTransform* sphereTransform = new SoTransform;
    sphereTransform->translation.setValue(-3, 0, 0);
    SoMaterial* sphereMaterial = new SoMaterial;
    sphereMaterial->diffuseColor.setValue(1.0, 0.0, 0.0); // Red
    SoSphere* sphere = new SoSphere;
    sphere->radius = 1.0;
    sphereSep->addChild(sphereTransform);
    sphereSep->addChild(sphereMaterial);
    sphereSep->addChild(sphere);
    root->addChild(sphereSep);
    
    // Create a cube
    SoSeparator* cubeSep = new SoSeparator;
    SoTransform* cubeTransform = new SoTransform;
    cubeTransform->translation.setValue(-1, 0, 0);
    SoMaterial* cubeMaterial = new SoMaterial;
    cubeMaterial->diffuseColor.setValue(0.0, 1.0, 0.0); // Green
    SoCube* cube = new SoCube;
    cube->width = 1.5;
    cube->height = 1.5;
    cube->depth = 1.5;
    cubeSep->addChild(cubeTransform);
    cubeSep->addChild(cubeMaterial);
    cubeSep->addChild(cube);
    root->addChild(cubeSep);
    
    // Create a cone
    SoSeparator* coneSep = new SoSeparator;
    SoTransform* coneTransform = new SoTransform;
    coneTransform->translation.setValue(1, 0, 0);
    SoMaterial* coneMaterial = new SoMaterial;
    coneMaterial->diffuseColor.setValue(0.0, 0.0, 1.0); // Blue
    SoCone* cone = new SoCone;
    cone->bottomRadius = 0.8;
    cone->height = 2.0;
    coneSep->addChild(coneTransform);
    coneSep->addChild(coneMaterial);
    coneSep->addChild(cone);
    root->addChild(coneSep);
    
    // Create a cylinder
    SoSeparator* cylinderSep = new SoSeparator;
    SoTransform* cylinderTransform = new SoTransform;
    cylinderTransform->translation.setValue(3, 0, 0);
    SoMaterial* cylinderMaterial = new SoMaterial;
    cylinderMaterial->diffuseColor.setValue(1.0, 1.0, 0.0); // Yellow
    SoCylinder* cylinder = new SoCylinder;
    cylinder->radius = 0.6;
    cylinder->height = 2.0;
    cylinderSep->addChild(cylinderTransform);
    cylinderSep->addChild(cylinderMaterial);
    cylinderSep->addChild(cylinder);
    root->addChild(cylinderSep);
    
    // Create viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
