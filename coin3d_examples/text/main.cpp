/*
 * Text Example
 * Demonstrates text rendering in Coin3D
 * Includes: 2D text, 3D text, different fonts
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoText3.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>

int main(int argc, char** argv)
{
    // Initialize SoQt library
    QWidget* mainwin = SoQt::init(argc, argv, argv[0]);
    
    // Create root node
    SoSeparator* root = new SoSeparator;
    root->ref();
    
    // 2D Text Example
    SoSeparator* text2dSep = new SoSeparator;
    SoTransform* text2dTransform = new SoTransform;
    text2dTransform->translation.setValue(0, 2, 0);
    SoMaterial* text2dMaterial = new SoMaterial;
    text2dMaterial->diffuseColor.setValue(1.0, 0.0, 0.0); // Red
    SoFont* text2dFont = new SoFont;
    text2dFont->size = 1.0;
    SoText2* text2d = new SoText2;
    text2d->string.set1Value(0, "2D Text in Coin3D");
    text2dSep->addChild(text2dTransform);
    text2dSep->addChild(text2dMaterial);
    text2dSep->addChild(text2dFont);
    text2dSep->addChild(text2d);
    root->addChild(text2dSep);
    
    // 3D Text Example
    SoSeparator* text3dSep = new SoSeparator;
    SoTransform* text3dTransform = new SoTransform;
    text3dTransform->translation.setValue(0, 0, 0);
    SoMaterial* text3dMaterial = new SoMaterial;
    text3dMaterial->diffuseColor.setValue(0.0, 0.0, 1.0); // Blue
    SoFont* text3dFont = new SoFont;
    text3dFont->size = 0.8;
    SoText3* text3d = new SoText3;
    text3d->string.set1Value(0, "3D Text");
    text3d->parts.setValue(SoText3::ALL);
    text3dSep->addChild(text3dTransform);
    text3dSep->addChild(text3dMaterial);
    text3dSep->addChild(text3dFont);
    text3dSep->addChild(text3d);
    root->addChild(text3dSep);
    
    // Multiple lines of text
    SoSeparator* multilineSep = new SoSeparator;
    SoTransform* multilineTransform = new SoTransform;
    multilineTransform->translation.setValue(0, -2, 0);
    SoMaterial* multilineMaterial = new SoMaterial;
    multilineMaterial->diffuseColor.setValue(0.0, 1.0, 0.0); // Green
    SoFont* multilineFont = new SoFont;
    multilineFont->size = 0.5;
    SoText2* multilineText = new SoText2;
    multilineText->string.set1Value(0, "Line 1");
    multilineText->string.set1Value(1, "Line 2");
    multilineText->string.set1Value(2, "Line 3");
    multilineSep->addChild(multilineTransform);
    multilineSep->addChild(multilineMaterial);
    multilineSep->addChild(multilineFont);
    multilineSep->addChild(multilineText);
    root->addChild(multilineSep);
    
    // Create viewer
    SoQtExaminerViewer* viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->setTitle("Text Example");
    viewer->show();
    
    // Show main window
    SoQt::show(mainwin);
    SoQt::mainLoop();
    
    // Cleanup
    delete viewer;
    root->unref();
    
    return 0;
}
