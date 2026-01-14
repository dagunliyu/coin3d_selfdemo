/*
 * Transformations Example
 * Demonstrates various transformations in Coin3D
 * Includes: Translation, Rotation, Scale
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create root node
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // Original cube (no transformation)
    SoSeparator* originalSep = new SoSeparator;
    SoMaterial* originalMaterial = new SoMaterial;
    originalMaterial->diffuseColor.setValue(0.5, 0.5, 0.5); // Gray
    SoCube* originalCube = new SoCube;
    originalCube->width = 1.0;
    originalCube->height = 1.0;
    originalCube->depth = 1.0;
    originalSep->addChild(originalMaterial);
    originalSep->addChild(originalCube);
    root->addChild(originalSep);
    
    // Translation example
    SoSeparator* translatedSep = new SoSeparator;
    SoTransform* translationTransform = new SoTransform;
    translationTransform->translation.setValue(2.5, 0, 0);
    SoMaterial* translatedMaterial = new SoMaterial;
    translatedMaterial->diffuseColor.setValue(1.0, 0.0, 0.0); // Red
    SoCube* translatedCube = new SoCube;
    translatedCube->width = 1.0;
    translatedCube->height = 1.0;
    translatedCube->depth = 1.0;
    translatedSep->addChild(translationTransform);
    translatedSep->addChild(translatedMaterial);
    translatedSep->addChild(translatedCube);
    root->addChild(translatedSep);
    
    // Rotation example
    SoSeparator* rotatedSep = new SoSeparator;
    SoTransform* rotationTransform = new SoTransform;
    rotationTransform->translation.setValue(0, 2.5, 0);
    rotationTransform->rotation.setValue(SbVec3f(0, 0, 1), M_PI / 4); // 45 degrees around Z axis
    SoMaterial* rotatedMaterial = new SoMaterial;
    rotatedMaterial->diffuseColor.setValue(0.0, 1.0, 0.0); // Green
    SoCube* rotatedCube = new SoCube;
    rotatedCube->width = 1.0;
    rotatedCube->height = 1.0;
    rotatedCube->depth = 1.0;
    rotatedSep->addChild(rotationTransform);
    rotatedSep->addChild(rotatedMaterial);
    rotatedSep->addChild(rotatedCube);
    root->addChild(rotatedSep);
    
    // Scale example
    SoSeparator* scaledSep = new SoSeparator;
    SoTransform* scaleTransform = new SoTransform;
    scaleTransform->translation.setValue(-2.5, 0, 0);
    scaleTransform->scaleFactor.setValue(0.5, 1.5, 1.0); // Non-uniform scale
    SoMaterial* scaledMaterial = new SoMaterial;
    scaledMaterial->diffuseColor.setValue(0.0, 0.0, 1.0); // Blue
    SoCube* scaledCube = new SoCube;
    scaledCube->width = 1.0;
    scaledCube->height = 1.0;
    scaledCube->depth = 1.0;
    scaledSep->addChild(scaleTransform);
    scaledSep->addChild(scaledMaterial);
    scaledSep->addChild(scaledCube);
    root->addChild(scaledSep);
    
    // Combined transformations example
    SoSeparator* combinedSep = new SoSeparator;
    SoTransform* combinedTransform = new SoTransform;
    combinedTransform->translation.setValue(0, -2.5, 0);
    combinedTransform->rotation.setValue(SbVec3f(1, 1, 0), M_PI / 6); // Rotation around (1,1,0)
    combinedTransform->scaleFactor.setValue(1.2, 1.2, 1.2);
    SoMaterial* combinedMaterial = new SoMaterial;
    combinedMaterial->diffuseColor.setValue(1.0, 1.0, 0.0); // Yellow
    SoCube* combinedCube = new SoCube;
    combinedCube->width = 1.0;
    combinedCube->height = 1.0;
    combinedCube->depth = 1.0;
    combinedSep->addChild(combinedTransform);
    combinedSep->addChild(combinedMaterial);
    combinedSep->addChild(combinedCube);
    root->addChild(combinedSep);
    
    // Create viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("Transformations Example");
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
