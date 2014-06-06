//
//  ofxOscReceiverScheduler.h
//
//  Created by nomura on 2014/06/06.
//
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofxOscReceiveMessage {
public:
    ofxOscReceiveMessage(ofxOscMessage m, float arrivalTime_){
        message = m;
        arrivalTime = arrivalTime_;
    }
    inline float getArrivalTime() {
        return arrivalTime;
    }
    string getAddress() {
        return message.getAddress();
    }
    const ofxOscMessage & getMessage() const {
        return message;
    }
    bool hasSameArgs(ofxOscMessage m) {
        if (m.getNumArgs() != message.getNumArgs()) {
            return false;
        }
        for (int i=0; i<m.getNumArgs(); i++) {
            ofxOscArgType type1 = m.getArgType(i);
            ofxOscArgType type2 = message.getArgType(i);
            
            if (type1 != type2) {
                return false;
            }
            
            switch (type1) {
                case OFXOSC_TYPE_INT32: {
                    int32_t v1 = m.getArgAsInt32(i);
                    int32_t v2 = message.getArgAsInt32(i);
                    if (v1 != v2) { return false; }
                    break;
                }
                case OFXOSC_TYPE_INT64: {
                    uint64_t v1 = m.getArgAsInt64(i);
                    uint64_t v2 = message.getArgAsInt64(i);
                    if (v1 != v2) { return false; }
                    break;
                }
                case OFXOSC_TYPE_FLOAT: {
                    float v1 = m.getArgAsFloat(i);
                    float v2 = message.getArgAsFloat(i);
                    if (v1 != v2) { return false; }
                    break;
                }
                case OFXOSC_TYPE_STRING: {
                    string v1 = m.getArgAsString(i);
                    string v2 = message.getArgAsString(i);
                    if (v1 != v2) { return false; }                    
                    break;
                }
                default:
                    break;
            }
        }
        return true;
    }
    bool isMessageRead = false;
    bool isIgnoreTimePassed = false;
private:
    ofxOscReceiveMessage(){}
    ofxOscMessage message;
    float arrivalTime;
};

class ofxOscReceiverScheduler {
public:
    ofxOscReceiverScheduler();
    ~ofxOscReceiverScheduler();
    
    void setup(int listen_port);
    bool hasWaitingMessages();
    
    bool getNextMessage(ofxOscMessage*);
    bool getParameter(ofAbstractParameter & parameter);
    
    void setIgnoreTime(float s);
    
private:
    ofxOscReceiver receiver;
    vector<ofPtr<ofxOscReceiveMessage> > messages;
    float ignoreTime;
    
    void update(ofEventArgs & args);
};