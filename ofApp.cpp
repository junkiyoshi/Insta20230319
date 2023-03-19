#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->noise_value = ofRandom(1000);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 90 < 15) {

		this->noise_value += ofMap(ofGetFrameNum() % 30, 0, 15, 0.2, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	
	for (int x = -360; x <= 360; x += 10) {

		for (int y = -360; y <= 360; y += 10) {

			vector<glm::vec2> vertices;
			vertices.push_back(glm::vec2(x, y));
			for (int i = 0; i < 50; i++) {

				auto deg = ofMap(ofNoise(vertices.back().x * 0.0015, vertices.back().y * 0.0015, this->noise_value), 0, 1, -360, 360);
				auto vertex = vertices.back() + glm::vec2(4 * cos(deg * DEG_TO_RAD), 4 * sin(deg * DEG_TO_RAD));
				vertices.push_back(vertex);
			}

			ofColor color;
			color.setHsb(ofRandom(0, 255), 255, 40);
			ofSetColor(color);

			ofNoFill();
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape();
		}
	}

	ostringstream os;
	os << setw(4) << setfill('0') << ofGetFrameNum();
	ofImage image;
	image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	image.saveImage("image/img_" + os.str() + ".jpg");
	if (ofGetFrameNum() >= 30 * 20 + 1) {

		std::exit(1);
	}

	// > ffmpeg -i img_%04d.jpg -r 30 out.mp4
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}