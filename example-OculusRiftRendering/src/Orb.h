#ifndef ____Orb__
#define ____Orb__

#include "ofMain.h"
#include "ofxStk.h"

class Orb
{
public:
    ofVec3f position; //XYZ position of the current orb.
    ofVec3f acceleration;
    ofVec3f velocity;
    ofVec3f targetPosition;
    
    vector <ofVec3f> awareness;//stores ofVec3f positional data of all other    orbs in the system. 
    
    float maxSpeed=10;
    float maxForce;
    float r;
    
    float orbRadius = 2;
    int resolution;//sphere resolution
    float distanceFromCenter; //(0,0,0)
    ofColor orbColor;
    
    Orb(float _x, float _y, float _z);
    void update(int _mode);
    void draw();
    void setTargetPosition(ofVec3f _tp);
    void setAwareness(vector <ofVec3f> _awareness);
    
    //sound//
    stk::FileLoop file;
    
    //Behaviors//
    void still();
    void disperse();
    void seek();
    void separate();
    void applyForce(ofVec3f force);
    void fish();
};







#endif /* defined(____Orb__) */
