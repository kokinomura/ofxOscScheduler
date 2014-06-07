ofxOscScheduler
=========
An OSC scheduler addon for openFrameworks.

ofxOscScheduler is an addon for openFrameworks that allows you to send OSC messages with delay and send a message multiple times. You can use ofxOscSenderScheduler and ofxOscReceiverScheduler with same grammer as ofxOscSender and ofxOscReceiver.


In addition to being a scheduler, it intends to somehow guarantee delivery of OSC messages by sending them multiple times since UDP which OSC is based on does not guarantee. For sure, the ultimate solution is to use TCP instead of UDP while most of OSC libraries do not support TCP. ofxOscScheduler helps you to avoid unapparent trouble with OSC.


- In this example, you will send "hello" 5 times in 0.5 seconds with 2.0 seconds delay.
```cpp
void testApp::sendOSC() {
    ofxOscMessage m;
    m.setAddress("/address");
    m.addStringArg("hello");
    sender.reserveMessageRepeat(m, 2.0);
} 
```

 

Dependency
------------

- ofxOsc


Usage
---------------------------
### 1. Sender

#### Setup

```cpp
#include "ofxOscScheduler.h"

const string HOST = "localhost";
const int PORT = 12345;

class testApp : public ofBaseApp {
public:
    // definitions
    
    ofxOscSenderScheduler sender;
}
```

```
void testApp::setup() {
    sender.setup(HOST, PORT);
    sender.setRepeat(5, 0.5);  // sender will send a message 5 times in 0.5 seconds
}
```

#### Send

```cpp
void testApp::sendOSC() {
    ofxOscMessage m;
    m.setAddress("/address");
    m.addFloatArg("hello");
    sender.sendMessage(m);  // sends a message once regardless of setRepeat()
}   
```

#### With Delay

```cpp
void testApp::sendOSC() {
    ofxOscMessage m;
    m.setAddress("/address");
    m.addStringArg(3.0);
    sender.reserveMessage(m, 2.0);  // sends a message with 2.0 seconds delay
}   
```

#### Multiple Times

```cpp
void testApp::sendOSC() {
    ofxOscMessage m;
    m.setAddress("/address");
    m.addStringArg(3.0);
    sender.sendMessageRepeat(m);  // sends a message multiple times
}   
```

#### Multiple Times With Delay

```cpp
void testApp::sendOSC() {
    ofxOscMessage m;
    m.setAddress("/address");
    m.addStringArg(3.0);
    sender.reserveMessageRepeat(m, 2.0);  // sends a message multiple times with 2.0 seconds delay
}   
```

### 2. Receiver
To deal with multiple messages sent by ofxOscSenderScheduler, this addon offers ofxOscReceiverScheduler, which ignores any redundant messages.

\*\* Obviously it has a big drawback that you can't receive multiple messages that have a same address and values within a short time. When you need fast communication, I recommend you to implement your program with ofxOscReceiver.

```cpp
class testApp : public ofBaseApp {
public:
    // definitions
    
    ofxOscReceiverScheduler receiver;
}
```

```cpp
void testApp::setup(){
    receiver.setup(PORT);
    receiver.setIgnoreTime(0.5);
}

void testApp::update(){
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        if (m.getAddress() == "/address") {
            ofLog() << m.getArgAsString(0);
        }
    }
}
```
