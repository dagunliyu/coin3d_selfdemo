/*
 * Events Example
 * Demonstrates event handling and user interaction in Coin3D
 * Includes: Mouse events, Keyboard events, Selection
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/nodes/SoSelection.h>

// Callback function for mouse button events
void mouseButtonCB(void* userData, SoEventCallback* eventCB)
{
    const SoMouseButtonEvent* mbe = (SoMouseButtonEvent*)eventCB->getEvent();
    
    if (mbe->getButton() == SoMouseButtonEvent::BUTTON1) {
        if (mbe->getState() == SoButtonEvent::DOWN) {
            // Left mouse button pressed
            // You can add custom behavior here
            eventCB->setHandled();
        }
    }
}

// Callback function for keyboard events
void keyboardCB(void* userData, SoEventCallback* eventCB)
{
    const SoKeyboardEvent* ke = (SoKeyboardEvent*)eventCB->getEvent();
    
    if (ke->getState() == SoButtonEvent::DOWN) {
        if (ke->getKey() == SoKeyboardEvent::SPACE) {
            // Space key pressed
            // You can add custom behavior here
            eventCB->setHandled();
        }
    }
}

// Selection callback
void selectionCB(void* userData, SoPath* path)
{
    // This callback is triggered when an object is selected
    // You can get the selected node and perform actions
}

// Deselection callback
void deselectionCB(void* userData, SoPath* path)
{
    // This callback is triggered when an object is deselected
}

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create root node with selection capability
    SoSelection* root = new SoSelection;
    root->ref();
    root->policy = SoSelection::SINGLE; // Allow single selection
    
    // Set selection callbacks
    root->addSelectionCallback(selectionCB, NULL);
    root->addDeselectionCallback(deselectionCB, NULL);
    
    // Add event callback node for custom event handling
    SoEventCallback* eventCB = new SoEventCallback;
    eventCB->addEventCallback(SoMouseButtonEvent::getClassTypeId(), mouseButtonCB, NULL);
    eventCB->addEventCallback(SoKeyboardEvent::getClassTypeId(), keyboardCB, NULL);
    root->addChild(eventCB);
    
    // Create interactive objects
    SoSeparator* sphere1Sep = new SoSeparator;
    SoTransform* sphere1Transform = new SoTransform;
    sphere1Transform->translation.setValue(-2, 0, 0);
    SoMaterial* sphere1Material = new SoMaterial;
    sphere1Material->diffuseColor.setValue(1.0, 0.0, 0.0); // Red
    SoSphere* sphere1 = new SoSphere;
    sphere1->radius = 0.8;
    sphere1Sep->addChild(sphere1Transform);
    sphere1Sep->addChild(sphere1Material);
    sphere1Sep->addChild(sphere1);
    root->addChild(sphere1Sep);
    
    SoSeparator* cubeSep = new SoSeparator;
    SoTransform* cubeTransform = new SoTransform;
    cubeTransform->translation.setValue(0, 0, 0);
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
    
    SoSeparator* sphere2Sep = new SoSeparator;
    SoTransform* sphere2Transform = new SoTransform;
    sphere2Transform->translation.setValue(2, 0, 0);
    SoMaterial* sphere2Material = new SoMaterial;
    sphere2Material->diffuseColor.setValue(0.0, 0.0, 1.0); // Blue
    SoSphere* sphere2 = new SoSphere;
    sphere2->radius = 0.8;
    sphere2Sep->addChild(sphere2Transform);
    sphere2Sep->addChild(sphere2Material);
    sphere2Sep->addChild(sphere2);
    root->addChild(sphere2Sep);
    
    // Create viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("Events Example - Click objects to select, press Space");
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
