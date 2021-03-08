#include "ofApp.h"

ofFbo fbo;
ofShader shader;

ofVideoPlayer video;
ofVideoGrabber camera;

float soundLevel;
ofSoundStream micInput;

float elapsedTime;

float video1Alpha;
float video2Alpha;

//--------------------------------------------------------------
void ofApp::setup() {
    shader.load("fragShader");

    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    ofSetWindowTitle("Video thingies");
    ofSetWindowShape(1280, 720);
    ofSetFrameRate(30);
    ofBackground(ofColor::white);
    
    video.load("een.mov");
    video.play();
    
    camera.setDeviceID(0);
    camera.setDesiredFrameRate(30);
    camera.initGrabber(1280, 720);
    
    video1Alpha = 0.0;
    video2Alpha = 0.0;
    
    soundLevel = 0;
    
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
    video.update();
    if (camera.isInitialized()) camera.update();
    
    elapsedTime = ofGetElapsedTimef();

    video1Alpha = ofNoise(elapsedTime);
    if (video1Alpha > 1.0) video1Alpha = 1.0;
    video2Alpha = soundLevel * 40;
    if (video2Alpha > 1.0) video2Alpha = 1.0;
    // std::printf("Elapsed %f\n", elapsedTime);
    // std::printf("Noise %f\n", ofNoise(elapsedTime));
    // std::printf("RMS %f\n", video1Alpha);
}

//--------------------------------------------------------------
void ofApp::draw() {
    shader.begin();
    fbo.begin();

    ofDisableSmoothing();
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    if (camera.isInitialized()) {
        shader.setUniform1f("alphaVal", video2Alpha);
        camera.draw(0, 0, ofGetWidth(), ofGetHeight());
        camera.getTexturePtr();
        ofEnableAlphaBlending();
    }
    
    shader.setUniform1f("alphaVal", video1Alpha);
    video.draw(0, 0, ofGetWidth(), ofGetHeight());
    video.getTexturePtr();
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
