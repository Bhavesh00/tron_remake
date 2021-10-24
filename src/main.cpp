// Created by Bhaveshkumar Manivannan (bm12).

#include "ofMain.h"
#include "ofApp.h"

#define DISPLAY_MODE OF_FULLSCREEN // Can be OF_WINDOW or OF_FULLSCREEN

int main() {
	ofSetupOpenGL(1024, 480, DISPLAY_MODE); // setup the GL context
	ofSetFrameRate(60);
	
	// This starts the game.
	ofRunApp(new ofApp());
}
