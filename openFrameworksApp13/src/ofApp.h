#pragma once

#include "ofMain.h"
#include "Turtle.h"
#include "lsys.h"
#include <ctime>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		string fileName;
		Turtle * turtle1= new Turtle('F', '+', '-', 'f');
		lsys *L = new lsys ;
		string* line;
		string pline;
		ofEasyCam easyCam;
		ofImage img;

		int MODE = 0;

		ifstream testfile;
		ifstream parfile;
		ofLight testLight;


};
