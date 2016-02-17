//
//  Interact.cpp
//  
//
//  Created by Garrett on 1/10/16.


#include "Interact.h"
#include "ofApp.h"
#include <iostream>



Interact :: Interact()
{
    ofSetWorkingDirectoryToDefault();
    selectorPosition.set(0,0,0);
    nord.loadFont("Fonts/Nord Medium.otf", 13);//loads fonts from the font directory.
    
    }

void Interact :: setSelector(ofVec3f vectorChange)
{
    selectorPosition = selectorPosition + vectorChange; //vector change based on keyboard input for the selector.
}

void Interact :: renderSelector()
{
    ofPushStyle();
    
    ofSetColor(ofColor::tomato);
    ofNoFill();
    ofSetSphereResolution(50);
    ofDrawSphere(selectorPosition,2);
    ofPopStyle();
}

void Interact :: update(int _mode)
{
    mode = _mode;
  
}

ofVec3f Interact :: getSelector()
{
    return selectorPosition;
}

void Interact::getAzimuth(float Azimuth)
{
    float x;
    x = ofDegToRad(Azimuth);
    x = ofRadToDeg(x);
    aziString = ofToString(x);
}


string Interact::overlay(ofPoint overlayCenter)
{
    ofPushMatrix();
    ofTranslate(0, 170);
    //ofRect(overlayRect);
    
    ofSetColor(ofColor::white);
    ofFill();
        nord.drawString("X: " +
                ofToString(selectorPosition.x)+"\t Y: "+
                ofToString(selectorPosition.y)+"\t Z: "+
                ofToString(selectorPosition.z), 160, 40);
    //nord.drawString("Hello"+ofToString(myo.getAccelameter().y), 300, 40);
               // nord.drawString(aziString, 360, 40);

    
    switch (mode)
    {
        case 1:
            nord.drawString("Still", 360, 40);
            break;
        case 2:
            nord.drawString("Disperse", 360, 40);
            break;
        case 3:
            nord.drawString("Gather", 360, 40);
            break;
            
        default:
            break;
    }
    
    ofBeginShape();
    
    for (unsigned int i = 0; i < 100; i++)
    {
        float x =  ofMap(i, 0, 100, 0, 900, true);
        ofVertex(x, 100 -input*180.0f);
    }
    
    ofEndShape(false);
    
    
   
    //ofSetColor(0, 255, 0);
    ofNoFill();
    ofCircle(overlayCenter, 20);
    ofPopMatrix();
}


