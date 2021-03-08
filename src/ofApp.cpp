#include "ofApp.h"

ofFbo fbo;
ofShader shader;

ofVideoPlayer video1;
// ofVideoPlayer video2;
ofVideoGrabber camera;
ofSoundStream micInput;

float soundLevel;
float elapsedTime;

//--------------------------------------------------------------
void ofApp::setup() {
    shader.load("fragShader");

    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    ofSetWindowTitle("Video thingies");
    ofSetWindowShape(1280, 720);
    ofSetFrameRate(30);
    ofBackground(ofColor::white);
    
    video1.load("een.mov");
//    video2.load("twee.mov");
    video1.play();
//    video2.play();
    
    camera.setDeviceID(0);
    camera.setDesiredFrameRate(30);
    camera.initGrabber(1280, 720);
    
    soundLevel = 0.0;
    
    ofSoundStreamSettings settings;
    auto devices = micInput.getMatchingDevices("default");
    if (!devices.empty()) {
        settings.setInDevice(devices[0]);
    }
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.bufferSize = 44100;
    micInput.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update() {
    video1.update();
    // video2.update();
    if (camera.isInitialized()) camera.update();
    
    elapsedTime = ofGetElapsedTimef();

    // std::printf("Elapsed %f\n", elapsedTime);
    // std::printf("Noise %f\n", ofNoise(elapsedTime));
    // std::printf("RMS %f\n", video1Alpha);
}

//--------------------------------------------------------------
void ofApp::draw() {
    //if (camera.isInitialized()) camera.getTexturePtr();
    // video1.getTexturePtr();
    
    shader.begin();
    fbo.begin();
    
    shader.setUniformTexture("texture0", camera.getTexture(), 0);
    shader.setUniformTexture("texture1", video1.getTexture(), 1);

    ofDisableSmoothing();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
        
    shader.setUniform1f("time", elapsedTime);
    shader.setUniform1f("alpahVal", soundLevel);
        
    video1.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofEnableAlphaBlending();
    
    camera.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofEnableAlphaBlending();
        
    ofEnableSmoothing();

    fbo.end();
    shader.end();
        
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255);
}

void ofApp::audioIn(ofSoundBuffer & buffer) {
    // std::printf("RMS %f\n", buffer.getRMSAmplitude());
    soundLevel = buffer.getRMSAmplitude();
}

void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if ( key == ' ' ) {
     ofImage image;
     image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
     image.save("screen.png");
    }
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
