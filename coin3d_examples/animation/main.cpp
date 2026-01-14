/*
 * Animation Example
 * Demonstrates animation in Coin3D using engines and timers
 * Includes: Rotation animation, Oscillating movement
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/sensors/SoTimerSensor.h>

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create root node
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // Create time source for animations
    SoElapsedTime* timer = new SoElapsedTime;
    
    // Rotating sphere
    SoSeparator* rotatingSep = new SoSeparator;
    SoTransform* rotatingTransform = new SoTransform;
    rotatingTransform->translation.setValue(-3, 0, 0);
    
    // Connect timer to rotation
    SoCalculator* rotationCalc = new SoCalculator;
    rotationCalc->a.connectFrom(&timer->timeOut);
    rotationCalc->expression = "oA = vec3f(0, 1, 0); oB = a * 2.0"; // Rotate around Y axis
    rotatingTransform->rotation.connectFrom(&rotationCalc->oA);
    
    SoMaterial* rotatingMaterial = new SoMaterial;
    rotatingMaterial->diffuseColor.setValue(1.0, 0.0, 0.0); // Red
    SoSphere* rotatingSphere = new SoSphere;
    rotatingSphere->radius = 0.8;
    rotatingSep->addChild(rotatingTransform);
    rotatingSep->addChild(rotatingMaterial);
    rotatingSep->addChild(rotatingSphere);
    root->addChild(rotatingSep);
    
    // Oscillating cube (moving up and down)
    SoSeparator* oscillatingSep = new SoSeparator;
    SoTransform* oscillatingTransform = new SoTransform;
    
    // Connect timer to translation
    SoCalculator* translationCalc = new SoCalculator;
    translationCalc->a.connectFrom(&timer->timeOut);
    translationCalc->expression = "oA = vec3f(0, sin(a * 3.0) * 2.0, 0)";
    oscillatingTransform->translation.connectFrom(&translationCalc->oA);
    
    SoMaterial* oscillatingMaterial = new SoMaterial;
    oscillatingMaterial->diffuseColor.setValue(0.0, 1.0, 0.0); // Green
    SoCube* oscillatingCube = new SoCube;
    oscillatingCube->width = 1.2;
    oscillatingCube->height = 1.2;
    oscillatingCube->depth = 1.2;
    oscillatingSep->addChild(oscillatingTransform);
    oscillatingSep->addChild(oscillatingMaterial);
    oscillatingSep->addChild(oscillatingCube);
    root->addChild(oscillatingSep);
    
    // Scaling sphere
    SoSeparator* scalingSep = new SoSeparator;
    SoTransform* scalingTransform = new SoTransform;
    scalingTransform->translation.setValue(3, 0, 0);
    
    // Connect timer to scale
    SoCalculator* scaleCalc = new SoCalculator;
    scaleCalc->a.connectFrom(&timer->timeOut);
    scaleCalc->expression = "ta = abs(sin(a * 2.0)) * 0.5 + 0.5; oA = vec3f(ta, ta, ta)";
    scalingTransform->scaleFactor.connectFrom(&scaleCalc->oA);
    
    SoMaterial* scalingMaterial = new SoMaterial;
    scalingMaterial->diffuseColor.setValue(0.0, 0.0, 1.0); // Blue
    SoSphere* scalingSphere = new SoSphere;
    scalingSphere->radius = 0.8;
    scalingSep->addChild(scalingTransform);
    scalingSep->addChild(scalingMaterial);
    scalingSep->addChild(scalingSphere);
    root->addChild(scalingSep);
    
    // Combined animation - rotation + translation
    SoSeparator* combinedSep = new SoSeparator;
    SoTransform* combinedTransform = new SoTransform;
    
    // Translation in circular pattern
    SoCalculator* circularCalc = new SoCalculator;
    circularCalc->a.connectFrom(&timer->timeOut);
    circularCalc->expression = "oA = vec3f(cos(a) * 2.0, sin(a) * 2.0, 0)";
    combinedTransform->translation.connectFrom(&circularCalc->oA);
    
    // Rotation
    SoCalculator* combinedRotCalc = new SoCalculator;
    combinedRotCalc->a.connectFrom(&timer->timeOut);
    combinedRotCalc->expression = "oA = vec3f(0, 0, 1); oB = a * 3.0";
    combinedTransform->rotation.connectFrom(&combinedRotCalc->oA);
    
    SoMaterial* combinedMaterial = new SoMaterial;
    combinedMaterial->diffuseColor.setValue(1.0, 1.0, 0.0); // Yellow
    SoCube* combinedCube = new SoCube;
    combinedCube->width = 0.8;
    combinedCube->height = 0.8;
    combinedCube->depth = 0.8;
    combinedSep->addChild(combinedTransform);
    combinedSep->addChild(combinedMaterial);
    combinedSep->addChild(combinedCube);
    root->addChild(combinedSep);
    
    // Create viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("Animation Example");
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
