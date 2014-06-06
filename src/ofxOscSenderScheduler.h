//
//  ofxOscSenderScheduler.h
//
//  Created by Koki Nomura on 2014/01/16.
//
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofxOscSendMessage {
public:
    ofxOscSendMessage(ofxOscMessage m, float sendtime_) {
        message = m;
        sendtime = sendtime_;
    }
    float getSendTime() {
        return sendtime;
    }
    const ofxOscMessage & getMessage() const {
        return message;
    }
private:
    ofxOscSendMessage(){};
    ofxOscMessage message;
    float sendtime;
};

class ofxOscSenderScheduler {
public:
    ofxOscSenderScheduler();
    ~ofxOscSenderScheduler();
    
    void setup(const string & ip, int port);
    void setRepeat(int num, float sec);
    
    // send methods
    void sendMessage(ofxOscMessage & m);
    void sendMessageRepeat(ofxOscMessage & m);  // send a same message <num> times in <sec> seconds.

    // reserve methods (send a message after delay)
    void reserveMessage(ofxOscMessage & m, float delay_sec);
    void reserveMessageRepeat(ofxOscMessage & m, float delay_sec);
    
    // clear all reserved messages after <secs> seconds.
    void clearAfter(float secs);

private:
    void update(ofEventArgs & args);
    
    ofxOscSender sender;
    vector<ofPtr<ofxOscSendMessage> > messages;
    
    int numRepeat = 5;
    float repeatSec = 0.3;
};
