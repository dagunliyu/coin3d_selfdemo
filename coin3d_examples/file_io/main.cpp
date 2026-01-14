/*
 * File I/O Example
 * Demonstrates reading and writing 3D scene files in Coin3D
 * Includes: Writing Inventor files, Reading Inventor files
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>

// Function to create a sample scene
SoSeparator* createSampleScene()
{
    SoSeparator* root = new SoSeparator;
    
    // Create a sphere
    SoSeparator* sphereSep = new SoSeparator;
    SoTransform* sphereTransform = new SoTransform;
    sphereTransform->translation.setValue(-2, 0, 0);
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
    cubeTransform->translation.setValue(2, 0, 0);
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
    
    return root;
}

// Function to write scene to file
void writeSceneToFile(SoSeparator* root, const char* filename)
{
    SoOutput out;
    if (out.openFile(filename)) {
        SoWriteAction wa(&out);
        wa.apply(root);
        out.closeFile();
    }
}

// Function to read scene from file
SoSeparator* readSceneFromFile(const char* filename)
{
    SoInput in;
    if (in.openFile(filename)) {
        SoSeparator* root = SoDB::readAll(&in);
        in.closeFile();
        return root;
    }
    return NULL;
}

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create a sample scene
    SoSeparator* sceneToWrite = createSampleScene();
    sceneToWrite->ref();
    
    // Write scene to file (in /tmp directory to avoid committing)
    const char* filename = "/tmp/sample_scene.iv";
    writeSceneToFile(sceneToWrite, filename);
    
    // Read scene from file
    SoSeparator* root = readSceneFromFile(filename);
    
    // If reading failed, use the original scene
    if (!root) {
        root = sceneToWrite;
    } else {
        root->ref();
        sceneToWrite->unref();
    }
    
    // Create viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("File I/O Example - Scene loaded from file");
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
