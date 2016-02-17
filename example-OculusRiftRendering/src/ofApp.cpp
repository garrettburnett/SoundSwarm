#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    cam.setPosition(0, 0, 0);
	ofBackground(0);
	ofSetVerticalSync( true );

	showOverlay = false;
	predictive = true;
	
	ofHideCursor();
	
	oculusRift.baseCamera = &cam;
	oculusRift.setup();
    oculusRift.setUsePredictedOrientation(true);
    light.setPointLight();
    light.setPosition(0, 100, 100);
    light.enable();
 
	//enable mouse;
	cam.begin();
	cam.end();
    
    MODE =1;
    
    soundsetup();
    //input = 0;
    
   // myo.setup("cc.openFrameworks.myoTest");
}

//--------------------------------------------------------------
void ofApp::update()
{
    
    if(oculusRift.isSetup())
    {
        ofRectangle viewport = oculusRift.getOculusViewport();
    }
    
    interact.update(MODE);
    //interact.setWaveform(input[1]);
    targetPosition = interact.getSelector();
    
    for(int i=0;i<orbs.size();i++)
    {
        orbs[i].update(MODE);
        orbs[i].setTargetPosition(targetPosition); //feed the target.
        orbs[i].setAwareness(orbPositions);
        hoaCoord.setSourcePosition(i, orbs[i].position * 10);
    }
    
   // myo.update();
    
    
    
//  //  if( //)
//    {
//        //look up how to make a
//        
//        Orb tempOrb(interface.getSelector().x,interface.getSelector().y,interface.getSelector().z);
//        orbs.push_back(tempOrb);//using vector
//        
//        //push awareness.
//        //temp.
//        
//        for(int i=0;i<orbs.size();i++)
//        {
//            orbPositions.push_back(orbs[i].position); //create vector or orb positions.
//        }
//        
//        
//    }

}



//--------------------------------------------------------------
void ofApp::draw()
{
	if(oculusRift.isSetup())
    {
		if(true)
        {
			oculusRift.beginOverlay(-230, 620,240);
			ofRectangle overlayRect = oculusRift.getOverlayRectangle();
            ofPoint center = overlayRect.getCenter();
			
			ofPushStyle();
			ofEnableAlphaBlending();
			ofFill();
            ofSetColor(ofColor::white);
            interact.overlay(center);
            
            ofPopStyle();
			oculusRift.endOverlay();
		}
        
        ofSetColor(255);
		glEnable(GL_DEPTH_TEST);

		oculusRift.beginLeftEye();
		scene();
		oculusRift.endLeftEye();
		
		oculusRift.beginRightEye();
		scene();
		oculusRift.endRightEye();
		
		oculusRift.draw();
		
		glDisable(GL_DEPTH_TEST);
    }
    
	else
    {
		cam.begin();
		scene();
		cam.end();
	}
}

//--------------------------------------------------------------
void ofApp::scene()
{
   // ofBackground(255,237,67);
    ofBackgroundHex(0x008ddb);
    
     //ofBackgroundGradient(ofColor(255, 0, 0), ofColor(0, 0, 0), OF_GRADIENT_BAR);
    
    cam.setPosition(0, 0, 0);
    for(int i=0;i<orbs.size();i++)
    {
        orbs[i].draw();
    }
    
    interact.renderSelector();
    
   // cout<<"\n"<<"\n"<<myo.collector.pitch_w<<"\n";
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if( key == 'f' )
	{
		ofToggleFullscreen();
	}
	
    if(key == '1')
    {
        MODE =1;
    }
    
    if(key == '2')
    {
        MODE =2;
    }
    
    if(key == '3')
    {
        MODE =3;
    }
    
//    if(key == ' ' || myo.collector.pitch_w>1)
     if(key == ' ')
    {
       
        Orb tempOrb(interact.getSelector().x,interact.getSelector().y,interact.getSelector().z);
        orbs.push_back(tempOrb);//using vector
        
        //push awareness.
        //temp.
        
        for(int i=0;i<orbs.size();i++)
        {
            orbPositions.push_back(orbs[i].position); //create vector or orb positions.
        }
    }
    
    if(key == OF_KEY_DOWN)
    {
        interact.setSelector(ofVec3f(0,0,1));
    }
    
    if(key == OF_KEY_UP)
    {
        interact.setSelector(ofVec3f(0,0,-1));
    }
    
    if(key == OF_KEY_LEFT)
    {
        interact.setSelector(ofVec3f(-1,0,0));
    }
    
    if(key == OF_KEY_RIGHT)
    {
        interact.setSelector(ofVec3f(1,0,0));
    }
    
    
}

float ofApp::getRiftAzimuth()
{
    ofQuaternion rotation = oculusRift.getOrientationQuat();
    ofVec3f rVector = rotation.getEuler();
    float a = ofMap(rVector.y,-180,180,0,360);
    
    interact.getAzimuth(a);
    
    return a;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

void ofApp::soundsetup()
{
    nOutputs = 2;
    nInputs = 0;
    sampleRate = 44100;
    nBuffers = (nInputs+nOutputs)*2;
    
   // input = 0;
    
    harmonicMatrix = new float * [order * 2+1];
    
    for (int i = 0; i< order*2+1;++i) harmonicMatrix[i] = new float[bufferSize];
    
    outputMatrix = new float * [2];
    outputMatrix[0] = new float[bufferSize];
    outputMatrix[1] = new float[bufferSize];
    hoaDecoder.setCropSize(256);
    
    hoaDecoder.computeRendering(bufferSize);
    
    hoaCoord.setAmbisonicCenter(ofVec3f(0,0,0));
    hoaCoord.setAmbisonicRadius(100);
    
    hoaCoord.setRamp(50, sampleRate);
    
    //hoaCoord.setSourcePositionDirect(0, ofVec3f(10000,10000));
    
    soundStream.setup(this, nOutputs, nInputs, sampleRate, bufferSize, nBuffers);
}


void ofApp::audioOut(float * output, int bufferSize, int nChannels)//audio loop
{
    
    
    
    for (int i = 0; i<bufferSize; i++)
    {
        
        hoaCoord.process();
        
        if(orbs.size()>0)
        {
            for(int i = 0; i<orbs.size(); i++)
            {
                input[i] = (orbs[i].file.tick()/4)*.3 ;
                hoaEncoder.setRadius(hoaCoord.getRadius(i));
                hoaEncoder.setAzimuth(ofDegToRad(-1*(getRiftAzimuth()+180)));
                hoaEncoder.process(&input[i], harmonicsBuffer);
                hoaOptim.process(harmonicsBuffer, harmonicsBuffer);
            }
      
        }
        
        for (int j = 0; j<order*2+1; j++)
        {
            harmonicMatrix[j][i] = harmonicsBuffer[j];
        }
    }
    hoaDecoder.processBlock(const_cast<const float **>(harmonicMatrix), outputMatrix);
    
    for (int i = 0; i<bufferSize; ++i)
    {
        output[i*nChannels] = outputMatrix[0][i];
        output[i*nChannels+1] = outputMatrix[1][i];
    }

}