#pragma once

#include "ofMain.h"
#include "Orb.h"
#include "ofxOculusDK2.h"
#include "Interact.h"
#include "ofxHoa.h"
//#include "ofxMyoB.h"
#include "ofxLeapMotion2.h"






class ofApp : public ofBaseApp
{
  public:
    
     int MODE; //STILL
	
	void setup();
	void update();
	void draw();
	
	void scene();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxOculusDK2		oculusRift;

	ofLight				light;
	ofEasyCam			cam;
	bool showOverlay;
	bool predictive;
    
    vector <Orb> orbs;
    vector <ofVec3f> orbPositions;
     
    Interact interact;
    
    //ofxLeapMotion leap;

    ofVec3f cursor2D;
    ofVec3f cursor3D;
    
    ofVec3f cursorRift;
    ofVec3f demoRift;
    ofVec3f cursorGaze;
    ofVec3f targetPosition;
    
    //sound//
    
    void audioOut(float *output,int bufferSize,int nChannels);
    void soundsetup();
    
    float getRiftAzimuth();
    float sendAzimuth();
    
    static const int order = 7;
    int nInputs, nOutputs;
    static const int bufferSize = 512;
    int sampleRate;
    int nBuffers;
    int maxOrbs = 4;
    
    //MOST HOA CLASSES REQUIRE ARGUMENTS FOR INITILIZATION, SO WE CREATE THEM AS POINTERS
    hoa::Encoder<Hoa2d, float>::DC hoaEncoder = Encoder<Hoa2d, float>::DC(order);
    hoa::Decoder<Hoa2d, float>::Binaural hoaDecoder = Decoder<Hoa2d, float>::Binaural(order);
    hoa::Optim<Hoa2d, float>::Basic hoaOptim = Optim<Hoa2d, float>::Basic(order);
    hoa::ofxHoaCoord<Hoa2d, float> hoaCoord = ofxHoaCoord<Hoa2d, float>(1);
    
    ofSoundStream soundStream;
    
    float input[1];
    float harmonicsBuffer[order*2+1];
    
    float * inputBuffer;
    
    float ** harmonicMatrix;
    float ** outputMatrix;
    
    
    //ofxMyoBeta myo;
    
   


};
