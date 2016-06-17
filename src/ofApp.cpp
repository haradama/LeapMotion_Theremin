#include "ofApp.h"


int radius_1 = 0;
int height = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    cam.setOrientation(ofPoint(-20, 0, 0));
    
    ofSetLineWidth(50);
    ofSetCircleResolution(100);
    
    glEnable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    leap.open();
    
    sound.loadSound("sound.wav");
    sound.setLoop(true);
    
    sound.play();

    
}

//--------------------------------------------------------------
void ofApp::update(){
    simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};

    }
    
    leap.markFrameAsOld();
    
    ofNoFill();
    player.loadImage(ofToString(height)+".png");
    note.loadImage("note.png");
    theremin.loadImage("theremin.png");
    
    ofBackground(100);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    ofPushMatrix();
    ofRotate(90, 0, 0, 1);
    ofSetColor(20);
    ofDrawGridPlane(800, 20, false);
    ofPopMatrix();
    
    fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
    
    for(int i = 0; i < simpleHands.size(); i++){
        bool isLeft        = simpleHands[i].isLeft;
        ofPoint handPos    = simpleHands[i].handPos;
        ofPoint handNormal = simpleHands[i].handNormal;
        
        ofSetColor(0, 0, 255);
        ofDrawSphere(handPos.x, handPos.y, handPos.z, 20);
        
        height = handPos.y;
        
    }
    cam.end();
    
    if(height < -400){
        height = -400;
    }
    else if(height > 150){
        height = 150;
    }
    
    height = ofMap(height, -400, 150, 1, 7);
    

    ofBackground(ofColor::fromHsb(ofMap(height, 1, 7, 0, 255), 255, 255, 100));
    
    ofSetColor(255, 255, 255, 100);
    note.draw(ofGetWidth()/2-note.getWidth()/2, ofGetHeight()/2-note.getHeight()/2);
    
    ofSetColor(255, 255, 255);
    ofCircle(ofGetWidth()/2, ofGetHeight()/2, radius_1);
    radius_1 += (20 + height*5);
    if(radius_1 > ofGetWidth()/2){
        radius_1 = 0;
    }
    player.draw(ofGetWidth()-600,ofGetHeight()-700);
    theremin.draw(30,ofGetHeight()-600);
    
    sound.setSpeed(ofMap(height, 1, 8, 1.0, 2.0));
    
    ofDrawBitmapStringHighlight(ofToString(height), 30, 10);
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    sound.stop();
    leap.close();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
