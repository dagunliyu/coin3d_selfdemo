/*
 * Materials Example
 * Demonstrates material properties in Coin3D
 * Includes: Diffuse color, Specular color, Emissive color, Transparency
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoDirectionalLight.h>

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create root node
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // Add a light source for better material visualization
    SoDirectionalLight* light = new SoDirectionalLight;
    light->direction.setValue(0, 0, -1);
    root->addChild(light);
    
    // Material with diffuse color only
    SoSeparator* diffuseSep = new SoSeparator;
    SoTransform* diffuseTransform = new SoTransform;
    diffuseTransform->translation.setValue(-3, 1, 0);
    SoMaterial* diffuseMaterial = new SoMaterial;
    diffuseMaterial->diffuseColor.setValue(1.0, 0.0, 0.0); // Red
    SoSphere* diffuseSphere = new SoSphere;
    diffuseSphere->radius = 0.7;
    diffuseSep->addChild(diffuseTransform);
    diffuseSep->addChild(diffuseMaterial);
    diffuseSep->addChild(diffuseSphere);
    root->addChild(diffuseSep);
    
    // Material with specular highlights
    SoSeparator* specularSep = new SoSeparator;
    SoTransform* specularTransform = new SoTransform;
    specularTransform->translation.setValue(-1, 1, 0);
    SoMaterial* specularMaterial = new SoMaterial;
    specularMaterial->diffuseColor.setValue(0.0, 1.0, 0.0); // Green
    specularMaterial->specularColor.setValue(1.0, 1.0, 1.0); // White specular
    specularMaterial->shininess = 0.9; // High shininess
    SoSphere* specularSphere = new SoSphere;
    specularSphere->radius = 0.7;
    specularSep->addChild(specularTransform);
    specularSep->addChild(specularMaterial);
    specularSep->addChild(specularSphere);
    root->addChild(specularSep);
    
    // Material with emissive color (self-illuminated)
    SoSeparator* emissiveSep = new SoSeparator;
    SoTransform* emissiveTransform = new SoTransform;
    emissiveTransform->translation.setValue(1, 1, 0);
    SoMaterial* emissiveMaterial = new SoMaterial;
    emissiveMaterial->diffuseColor.setValue(0.0, 0.0, 1.0); // Blue
    emissiveMaterial->emissiveColor.setValue(0.3, 0.3, 1.0); // Blue glow
    SoSphere* emissiveSphere = new SoSphere;
    emissiveSphere->radius = 0.7;
    emissiveSep->addChild(emissiveTransform);
    emissiveSep->addChild(emissiveMaterial);
    emissiveSep->addChild(emissiveSphere);
    root->addChild(emissiveSep);
    
    // Material with transparency
    SoSeparator* transparentSep = new SoSeparator;
    SoTransform* transparentTransform = new SoTransform;
    transparentTransform->translation.setValue(3, 1, 0);
    SoMaterial* transparentMaterial = new SoMaterial;
    transparentMaterial->diffuseColor.setValue(1.0, 1.0, 0.0); // Yellow
    transparentMaterial->transparency = 0.5; // 50% transparent
    SoSphere* transparentSphere = new SoSphere;
    transparentSphere->radius = 0.7;
    transparentSep->addChild(transparentTransform);
    transparentSep->addChild(transparentMaterial);
    transparentSep->addChild(transparentSphere);
    root->addChild(transparentSep);
    
    // Complex material (combining multiple properties)
    SoSeparator* complexSep = new SoSeparator;
    SoTransform* complexTransform = new SoTransform;
    complexTransform->translation.setValue(0, -1, 0);
    SoMaterial* complexMaterial = new SoMaterial;
    complexMaterial->ambientColor.setValue(0.2, 0.0, 0.2); // Dark purple ambient
    complexMaterial->diffuseColor.setValue(0.8, 0.0, 0.8); // Purple
    complexMaterial->specularColor.setValue(1.0, 1.0, 1.0); // White specular
    complexMaterial->emissiveColor.setValue(0.1, 0.0, 0.1); // Slight glow
    complexMaterial->shininess = 0.7;
    complexMaterial->transparency = 0.2;
    SoSphere* complexSphere = new SoSphere;
    complexSphere->radius = 0.7;
    complexSep->addChild(complexTransform);
    complexSep->addChild(complexMaterial);
    complexSep->addChild(complexSphere);
    root->addChild(complexSep);
    
    // Create viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("Materials Example");
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
