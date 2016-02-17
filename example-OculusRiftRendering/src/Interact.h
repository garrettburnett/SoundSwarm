//
//  Interact.h
//  
//
//  Created by Garrett on 1/10/16.
//
//The interact class handles all interaction and display.

#ifndef ____Interact__
#define ____Interact__

#include <stdio.h>
#include "ofMain.h"

class Interact
{
    
public:
int mode;
    
ofVec3f selectorPosition;
Interact();
    
void setSelector(ofVec3f vectorChange);
void renderSelector();
ofVec3f getSelector();
void update(int _mode);
    
    void setupHands();

    
    
void getAzimuth(float Azimuth);
    
string overlay(ofPoint overlayCenter);
    ofTrueTypeFont nord;
    
    
string aziString;

    
    
    float input;
    
};


#endif /* defined(____Interact__) */
