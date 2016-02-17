#include "Orb.h"

Orb::Orb(float _x,float _y,float _z)
{
    position.set(_x, _y, _z);
    orbColor = ofColor::white; //set position based on values given to constructors.
    
    //sound//
    file.openFile(ofToDataPath("Sound/ambience1.wav"));
    //behavior//
    acceleration.set(0,0,0);
    velocity.set(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1));
}

void Orb::draw()
{
    ofFill();
    ofSetColor(orbColor);
    ofDrawSphere(position.x,position.y,position.z, orbRadius);
}

void Orb::update(int _mode)
{
    switch (_mode)
    {
        case 1:
            still();
            break;
            
        case 2:
            disperse();
            break;
        case 3:
            fish();
            break;
        default:
            break;
    }
    
}

void Orb::setTargetPosition(ofVec3f _tp)
{
    targetPosition=_tp; //this is constantly updated.
}

void Orb::setAwareness(vector <ofVec3f> _awareness)
{
    awareness = _awareness;//set this vector of vectors equal to the set we were passed from ofApp.
}

void Orb::still(){
    
}

void Orb::disperse()
{
    maxSpeed = 1;
    velocity+=acceleration;
    velocity.limit(maxSpeed);
    
    position+=velocity;
    acceleration=acceleration*0;
}

void Orb::applyForce(ofVec3f force){
    // We could add mass here if we want A = F / M
    acceleration+=force;
}

void Orb::seek()
{
    ofVec3f desired = targetPosition-position;
    //scale to maximum speed//
    
    ofVec3f steer = desired-velocity;
    steer.limit(maxForce);
    applyForce(steer);
}

void Orb::separate()
{
    r=3;
    float desiredSeparation = r*2;
    ofVec3f sum;
    float count = 0;
    
    //become aware whether or not other orbs are too close.
    
    for(int i = 0; i <awareness.size();i++)
    {
        float d = position.distance(awareness[i]);
        if((d>0) && (d<desiredSeparation)) //if too close
        {
            //calculate vector pointing away from neighbor.
            
            ofVec3f diff = position -awareness[i];
            diff.normalize();
            diff=diff/d;
            sum+=diff;
            count++;
        } //end direction calculation
    }//end awareness check
    
    if(count>0)
    {
        ofVec3f steer = sum-velocity;
        steer.limit(maxForce);
        applyForce(steer);
        
    }
}

void Orb::fish()
{
    r = 30;
    maxForce = .03;
    maxSpeed = 30;
    velocity += acceleration;
    velocity.limit(this->maxSpeed);
    
    position+=velocity;
    acceleration = acceleration*0;
    
    this->separate();
    this->seek();
    
}
