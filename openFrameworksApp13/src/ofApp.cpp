#include "ofApp.h"
#include <string>
#include <iostream>




//--------------------------------------------------------------


void ofApp::setup(){


	
	
	ofBackground(0);
	
	
	easyCam.setNearClip(0.01);
	easyCam.setFarClip(10000000);

	easyCam.setDistance(0);
	std::cout << "Enter file name: ";
	std::cin >> fileName;
	
	testfile.open("./"+fileName+".txt", ios::in);
	
	
}

//--------------------------------------------------------------
void ofApp::update(){
	//if (MODE == 2) {

	//	if (testfile.is_open() && parfile.is_open()) {
	//		if (line)
	//			delete line;
	//		line = new string;
	//		getline(testfile, *line);
	//		getline(parfile, pline);

	//		
	//	}
	//	//turtle1.DrawData(line, ofGetWidth() / 2, ofGetHeight() / 2, 0);
	//	string save = "D:/documents/LMeshTest/" + pline + ".ply";
	//	save.erase(std::remove(save.begin(), save.end(), '\"'), save.end());
	//	std::replace(save.begin(), save.end(), '>', ')');
	//	turtle1.save(save);
	//	if (parfile.eof()) {
	//		ofExit();
	//	}

	//}
}
//--------------------------------------------------------------

void ofApp::draw(){
	//ofSetColor(255);
	if (MODE == 0 ||MODE== 1 || MODE ==3)
	{
		easyCam.begin();
			ofPushMatrix();
				ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
				if (MODE == 0)
					
					turtle1->draw();

				if (MODE == 3)
					turtle1->drawPrint();
			ofPopMatrix();
		easyCam.end();
		/*
		if (MODE == 1) {

			keyReleased('s');
			keyReleased(' ');
			if (parfile.eof()) {
				ofExit();
			}
		}*/
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
int iter = 1;
void ofApp::keyReleased(int key){
	//generating a new l-system
	if (key == ' ') {
		//if (testfile.is_open()&&parfile.is_open()) {
		//	if(line)
		//	delete line;
		//	line = new string;
		//	getline(testfile, *line);
		//	getline(parfile, pline);

		//	//turt.setStr(line);
		//	//std::cout << "opened:\n"<< line;
		//	//system("cls");
		//	//cout<< pline;
		//	if (testfile.eof())
		//		cout << "end of file\n";
		//}
		//if(MODE==0|| MODE==1 ||MODE==2)
		//turtle1.draw(line, ofGetWidth() / 2, ofGetHeight() / 2, 0);
		//if(MODE==3)
		//	turtle1.printModel(line, ofGetWidth() / 2, ofGetHeight() / 2, 0);
		delete turtle1;
		turtle1 = new Turtle('F', '+', '-', 'f');
		delete L;
		L = new lsys;
		L->generateRandomRules();
		L->iterate(4);
		/*L->generateRandomRules();
		L->iterate(2);*/
		delete line;
		line = new string;
		line = L->getWord();
		turtle1->draw(line, ofGetWidth() / 2, ofGetHeight() / 2, 0,L->getUpperBound(), 5);
		L->printRules();

	
	}
	//reading in the next l system
	if (key == 'n')
	{
		string line1;
		iter = 1;
		if (testfile.is_open())
		{
			if (testfile.eof()) {
				cout << "\nend of file\n";
			}
			else {
				/*getline(testfile, line1);
				delete turtle1;
				turtle1 = new Turtle('F', '+', '-', 'f');
				turtle1->setAngle(stof(line1));
				cout << "\nAngle: " + line1 + "\n";
				getline(testfile, line1);
				delete L;
				L = new lsys;
				L->setSeed(line1);
				getline(testfile, line1);
				L->addrule('F', line1);
				L->iterate(0);
				delete line;
				line = new string;
				line = L->getWord();
				turtle1->draw(line, ofGetWidth() / 2, ofGetHeight() / 2, 0);
				L->printRules();
				getline(testfile, line1);*/
				getline(testfile, line1);
				delete turtle1;
				turtle1 = new Turtle('F', '+', '-', 'f');
				turtle1->setAngle(stof(line1));
				cout << "\nAngle: " << line1 << "\n";
				getline(testfile, line1);
				delete L;
				L = new lsys;
				L->setSeed(line1);
				getline(testfile, line1);
				while (line1 != "") {
					
					char letter = line1[0];
					line1.erase(0, 2);
					L->addrule(letter,line1);
					getline(testfile, line1);
				}
				L->iterate(0);
				delete line;
				line = new string;
				line = L->getWord();
				L->findGrowthUpperBound();
				cout << L->getUpperBound() << "\n";
				turtle1->draw(line, ofGetWidth() / 2, ofGetHeight() / 2, 0, L->getUpperBound(),1);
				L->printRules();
				//getline(testfile, line1);
			}
		}
	}
	if (key == 's')
	{
		 int time = std::time(NULL);
		 std::string t = to_string(time);
		string save = "D:/documents/LimageTest2/" + t + ".jpeg";
		//save.erase(std::remove(save.begin(), save.end(), '\"'), save.end());
		//std::replace(save.begin(), save.end(), '>', ')');
		//cout << save;
		img.grabScreen(0, 0, ofGetHeight(), ofGetWidth());
		img.save(save);
		
	}
	if (key == 'r')
	{
		testfile.close();
		
		testfile.open("./"+fileName+".txt", ios::in);
		
	}
	if (key == 'p')
	{
		turtle1->printModel(line, ofGetWidth() / 2, ofGetHeight() / 2, 0);
		string save = "D:/documents/LimageModels/" + pline + ".ply";
		save.erase(std::remove(save.begin(), save.end(), '\"'), save.end());
		std::replace(save.begin(), save.end(), '>', ')');
		turtle1->save(save);
	}
	
	if (key == 'i')
	{
		L->iterate(1);
		//delete line; //sometimes references deleted string... but sometimes doesnt so what's happening? and is there a mem leak now?
		line = new string;
		line = L->getWord();
		iter++;
		turtle1->draw(line, ofGetWidth() / 2, ofGetHeight() / 2, 0,L->getUpperBound(),iter );
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------

char c;// i dont know if this is used anywhere but im afraid to get rid of it 
void ofApp::mousePressed(int x, int y, int button){
	/*ofBackground(0);*/
	//turt.setScale(10);
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	/*turt.setX(ofGetWidth() / 2);
	turt.sety(ofGetHeight() / 2);*/
	//if (testfile.is_open()) {
	//	
	//	
	//	getline(testfile, line);
	//	
	//	//turt.setStr(line);
	//	//std::cout << "opened:\n"<< line;
	//}
	//turtle1.draw(line, ofGetWidth() / 2, ofGetHeight() / 2, 0);

	//do {
	//	ofSetColor(255);
	//	c = testfile.get();
	//	turt.draw(&c);
	//	//cout << c << '\n';

	//} while (c != '\n');
	//cout<<"pressed\n";
	//turt.setStr(line);
	


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
