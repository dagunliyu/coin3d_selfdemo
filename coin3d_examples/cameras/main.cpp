/*
 * Cameras Example
 * Demonstrates camera setup and manipulation in Coin3D
 * Includes: Perspective camera, Orthographic camera
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create root node
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // Add a perspective camera to the scene graph
    SoPerspectiveCamera* camera = new SoPerspectiveCamera;
    camera->position.setValue(0, 0, 10); // Camera position
    camera->orientation.setValue(SbVec3f(0, 1, 0), 0); // Camera orientation
    camera->heightAngle = M_PI / 4; // 45 degree field of view
    camera->nearDistance = 1.0;
    camera->farDistance = 100.0;
    root->addChild(camera);
    
    // Create some objects to view
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            SoSeparator* objSep = new SoSeparator;
            SoTransform* transform = new SoTransform;
            transform->translation.setValue(i * 2.0, j * 2.0, 0);
            
            SoMaterial* material = new SoMaterial;
            float r = (i + 2) / 4.0;
            float g = (j + 2) / 4.0;
            float b = 0.5;
            material->diffuseColor.setValue(r, g, b);
            
            SoSphere* sphere = new SoSphere;
            sphere->radius = 0.5;
            
            objSep->addChild(transform);
            objSep->addChild(material);
            objSep->addChild(sphere);
            root->addChild(objSep);
        }
    }
    
    // Create viewer (the viewer has its own camera which will override ours,
    // but this demonstrates how to set up cameras in scene graph)
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("Cameras Example");
    
    // You can switch between perspective and orthographic cameras
    // viewer->setCameraType(SoPerspectiveCamera::getClassTypeId());
    // viewer->setCameraType(SoOrthographicCamera::getClassTypeId());
    
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
