#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofBackground(30, 30, 130);
    
    receiver.setup(PORT);
    receiver.setIgnoreTime(0.6);
}

//--------------------------------------------------------------
void testApp::update(){
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        if (m.getAddress() == "/key/pressed") {
            ofLog() << m.getAddress() << ": " << m.getArgAsString(0);
        } else if (m.getAddress() == "/key/released") {
            ofLog() << m.getAddress() << ": " << m.getArgAsInt32(0) << " " << m.getArgAsFloat(1) << " " << m.getArgAsFloat(2);
        } else if (m.getAddress() == "/mouse/button") {
            ofLog() << m.getAddress() << ": " << m.getArgAsString(0);
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}