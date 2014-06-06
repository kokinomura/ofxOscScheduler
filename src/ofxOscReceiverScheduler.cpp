//
//  ofxOscReceiverScheduler.cpp
//
//  Created by nomura on 2014/06/06.
//
//

#include "ofxOscReceiverScheduler.h"

ofxOscReceiverScheduler::ofxOscReceiverScheduler() {
    ofAddListener(ofEvents().update, this, &ofxOscReceiverScheduler::update);
}

ofxOscReceiverScheduler::~ofxOscReceiverScheduler() {
    ofRemoveListener(ofEvents().update, this, &ofxOscReceiverScheduler::update);
}

void ofxOscReceiverScheduler::setup(int listen_port) {
    receiver.setup(listen_port);
}

bool ofxOscReceiverScheduler::hasWaitingMessages() {
    for (int i=0; i<messages.size(); i++) {
        if (!messages[i]->isMessageRead) {
            return true;
        }
    }
    return false;
}

bool ofxOscReceiverScheduler::getNextMessage(ofxOscMessage *m) {
    int firstUnreadIndex;
    for (int i=0; i<messages.size(); i++) {
        if (!messages[i]->isMessageRead) {
            firstUnreadIndex = i;
            break;
        }
    }
    ofPtr<ofxOscReceiveMessage> pm = messages[firstUnreadIndex];
    *m = pm->getMessage();
    pm->isMessageRead = true;
    return true;
}

bool ofxOscReceiverScheduler::getParameter(ofAbstractParameter &parameter) {
    return receiver.getParameter(parameter);
}

void ofxOscReceiverScheduler::setIgnoreTime(float s) {
    ignoreTime = s + 0.05;
}

//---------------------------------------------------------------
#pragma mark - Private Methods

void ofxOscReceiverScheduler::update(ofEventArgs &args) {

    // check ignore time
    float now = ofGetElapsedTimef();
    vector<ofPtr<ofxOscReceiveMessage> >::iterator it;
    for (it=messages.begin(); it!=messages.end(); ) {
        if ((*it)->getArrivalTime() + ignoreTime < ofGetElapsedTimef()) {
            (*it)->isIgnoreTimePassed = true;
        }
        if ((*it)->isIgnoreTimePassed && (*it)->isMessageRead) {
            it = messages.erase(it);
        } else {
            it++;
        }
    }
    
    // receive new messages
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        bool bIgnore = false;
        for (int i=0; i<messages.size(); i++) {
            ofPtr<ofxOscReceiveMessage> pm = messages[i];
            if (pm->getAddress() == m.getAddress() && !pm->isIgnoreTimePassed && pm->hasSameArgs(m)) {
                bIgnore = true;
            }
        }
        
        if (!bIgnore) {
            float now = ofGetElapsedTimef();
            ofPtr<ofxOscReceiveMessage> pm = ofPtr<ofxOscReceiveMessage>(new ofxOscReceiveMessage(m, now));
            messages.push_back(pm);
        }
    }
}








