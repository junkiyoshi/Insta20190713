#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto size = 144;
	float noise_seed_1 = ofRandom(1000);
	float noise_seed_2 = ofRandom(1000);
	for (int z = size * -0.5; z <= size * 0.5; z += 4) {

		int start_param = ofMap(ofNoise(noise_seed_1, (ofGetFrameNum() + z) * 0.005), 0, 1, 0, 100);
		int end_param = start_param + ofMap(ofNoise(noise_seed_2, (ofGetFrameNum() + z) * 0.005), 0, 1, 25, 75);

		vector<glm::vec3> vertices;
		for (int param = start_param; param < end_param; param++) {

			vertices.push_back(glm::vec3(this->make_point(size * 0.95, param), z));
		}

		ofFill();
		ofSetColor(239);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}