#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(40, 100, 40);
    
    sender.setup(HOST, PORT);
    sender.setRepeat(5, 0.5);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'a' || key == 'A'){
        ofxOscMessage m;
        m.setAddress("/key/pressed");
        m.addStringArg("hello");
        sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(key == 'a' || key == 'A'){
		ofxOscMessage m;
		m.setAddress("/key/released");
		m.addIntArg(1);
		m.addFloatArg(3.5f);
		m.addFloatArg(ofGetElapsedTimef());
		sender.sendMessageRepeat(m);
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addStringArg("down");
	sender.reserveMessage(m, 2.0);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addStringArg("up");
	sender.reserveMessageRepeat(m, 2.0);
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