/*
 * Lighting Example
 * Demonstrates different light sources in Coin3D
 * Includes: Directional light, Point light, Spot light
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoSpotLight.h>

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create root node
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // Directional Light Example
    SoSeparator* directionalSep = new SoSeparator;
    SoDirectionalLight* directionalLight = new SoDirectionalLight;
    directionalLight->direction.setValue(0, -1, -1); // Light direction
    directionalLight->color.setValue(1.0, 1.0, 1.0); // White light
    directionalLight->intensity = 1.0;
    SoTransform* directionalTransform = new SoTransform;
    directionalTransform->translation.setValue(-3, 0, 0);
    SoMaterial* directionalMaterial = new SoMaterial;
    directionalMaterial->diffuseColor.setValue(0.8, 0.2, 0.2); // Red
    SoSphere* directionalSphere = new SoSphere;
    directionalSphere->radius = 0.8;
    directionalSep->addChild(directionalLight);
    directionalSep->addChild(directionalTransform);
    directionalSep->addChild(directionalMaterial);
    directionalSep->addChild(directionalSphere);
    root->addChild(directionalSep);
    
    // Point Light Example
    SoSeparator* pointSep = new SoSeparator;
    SoPointLight* pointLight = new SoPointLight;
    pointLight->location.setValue(0, 2, 0); // Light position
    pointLight->color.setValue(0.0, 1.0, 0.0); // Green light
    pointLight->intensity = 0.8;
    SoTransform* pointTransform = new SoTransform;
    pointTransform->translation.setValue(0, 0, 0);
    SoMaterial* pointMaterial = new SoMaterial;
    pointMaterial->diffuseColor.setValue(0.8, 0.8, 0.8); // Gray
    SoSphere* pointSphere = new SoSphere;
    pointSphere->radius = 0.8;
    pointSep->addChild(pointLight);
    pointSep->addChild(pointTransform);
    pointSep->addChild(pointMaterial);
    pointSep->addChild(pointSphere);
    root->addChild(pointSep);
    
    // Spot Light Example
    SoSeparator* spotSep = new SoSeparator;
    SoSpotLight* spotLight = new SoSpotLight;
    spotLight->location.setValue(3, 3, 3); // Light position
    spotLight->direction.setValue(0, -1, -1); // Light direction
    spotLight->color.setValue(1.0, 1.0, 0.0); // Yellow light
    spotLight->intensity = 1.0;
    spotLight->cutOffAngle = 0.5; // Spot angle
    SoTransform* spotTransform = new SoTransform;
    spotTransform->translation.setValue(3, 0, 0);
    SoMaterial* spotMaterial = new SoMaterial;
    spotMaterial->diffuseColor.setValue(0.2, 0.2, 0.8); // Blue
    SoSphere* spotSphere = new SoSphere;
    spotSphere->radius = 0.8;
    spotSep->addChild(spotLight);
    spotSep->addChild(spotTransform);
    spotSep->addChild(spotMaterial);
    spotSep->addChild(spotSphere);
    root->addChild(spotSep);
    
    // Additional sphere to show lighting effects
    SoSeparator* referenceSep = new SoSeparator;
    SoTransform* referenceTransform = new SoTransform;
    referenceTransform->translation.setValue(0, -2, 0);
    SoMaterial* referenceMaterial = new SoMaterial;
    referenceMaterial->diffuseColor.setValue(0.5, 0.5, 0.5); // Gray
    referenceMaterial->specularColor.setValue(1.0, 1.0, 1.0); // White specular
    referenceMaterial->shininess = 0.9;
    SoSphere* referenceSphere = new SoSphere;
    referenceSphere->radius = 1.0;
    referenceSep->addChild(referenceTransform);
    referenceSep->addChild(referenceMaterial);
    referenceSep->addChild(referenceSphere);
    root->addChild(referenceSep);
    
    // Create viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("Lighting Example");
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
