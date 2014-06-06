//
//  ofxOscSenderScheduler.cpp
//
//  Created by Koki Nomura on 2014/01/16.
//
//

#include "ofxOscSenderScheduler.h"

#pragma mark - Setup
ofxOscSenderScheduler::ofxOscSenderScheduler() {
    
}

ofxOscSenderScheduler::~ofxOscSenderScheduler() {
    ofRemoveListener(ofEvents().update, this, &ofxOscSenderScheduler::update);
}

void ofxOscSenderScheduler::setup(const string & ip, int port) {
    sender.setup(ip, port);
    ofAddListener(ofEvents().update, this, &ofxOscSenderScheduler::update);
}

void ofxOscSenderScheduler::setRepeat(int num, float sec) {
    numRepeat = num;
    repeatSec = sec;
}

#pragma mark - Send Methods

void ofxOscSenderScheduler::sendMessage(ofxOscMessage &m) {
    reserveMessage(m, 0.0);
}

void ofxOscSenderScheduler::sendMessageRepeat(ofxOscMessage &m) {
    reserveMessageRepeat(m, 0.0);
}

#pragma mark - Reserve Methods

void ofxOscSenderScheduler::reserveMessage(ofxOscMessage &m, float delay_sec) {
    ofPtr<ofxOscSendMessage> message = ofPtr<ofxOscSendMessage>(new ofxOscSendMessage(m, ofGetElapsedTimef() + delay_sec));
    messages.push_back(message);
}

void ofxOscSenderScheduler::reserveMessageRepeat(ofxOscMessage & m, float delay_sec) {
    
    for (int i=0; i<numRepeat; i++) {
        float offsetTime = repeatSec * i / (numRepeat-1.0);
        reserveMessage(m, offsetTime + delay_sec);
    }
}

#pragma mark 

void ofxOscSenderScheduler::clearAfter(float secs) {
    vector<ofPtr<ofxOscSendMessage> >::iterator mit;
    for (mit=messages.begin(); mit!=messages.end();) {
        float time = ofGetElapsedTimef() + secs;
        if (time < (*mit)->getSendTime()) {
            mit = messages.erase(mit);
        } else {
            mit++;
        }
    }
}

void ofxOscSenderScheduler::update(ofEventArgs &args) {
    
    float now = ofGetElapsedTimef();
    
    vector<ofPtr<ofxOscSendMessage> >::iterator mit;
    for (mit=messages.begin(); mit!=messages.end();) {
        ofPtr<ofxOscSendMessage> m = *mit;
        if (now < m->getSendTime()) {
            mit++;
            continue;
        }
        
        sender.sendMessage(const_cast<ofxOscMessage &>((*m).getMessage()));
        
        // delete sent messages
        mit = messages.erase(mit);
    }
}
