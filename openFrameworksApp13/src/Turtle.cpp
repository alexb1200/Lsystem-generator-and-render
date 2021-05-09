

#include "Turtle.h"


Turtle::Turtle(){
	angle = 15;
	curAngle = 0;
	length = 10;
	x = ofGetWidth()/2;
	y = ofGetHeight()/2;
	
}



struct hash_Line {
	size_t operator()(const std::pair<ofVec3f, ofVec3f> &v) const {
		//cout << '\n'<<(hash<float>()(v.first.x) ^ hash<float>()(v.first.y) ^ hash<float>()(v.first.z) ^ hash<float>()(v.second.x) ^ hash<float>()(v.second.y) ^ hash<float>()(v.second.z))<<'\n'; //just debug stuff
		return std::hash<float>()(v.first.x) ^ std::hash<float>()(v.first.y) ^ std::hash<float>()(v.first.z)^   std::hash<float>()(v.second.x) ^ std::hash<float>()(v.second.y) ^ std::hash<float>()(v.second.z);
	
	} 
};

//checking if two points are the same
struct eqFix{
constexpr bool operator()(const std::pair<ofVec3f, ofVec3f> &v1, const std::pair<ofVec3f, ofVec3f> &v2) const
{	// apply operator== to operands
	
	
	return( (v1.first.x == v2.first.x &&v1.first.y == v2.first.y &&v1.first.z == v2.first.z) &&
		(v1.second.x == v2.second.x &&v1.second.y == v2.second.y &&v1.second.z == v2.second.z)) ||
		((v1.first.x == v2.second.x &&v1.first.y == v2.second.y &&v1.first.z == v2.second.z) &&
		(v1.second.x == v2.first.x &&v1.second.y == v2.first.y &&v1.second.z == v2.first.z));
}
	};

Turtle::Turtle(char _forward, char _left, char _right, char f){
	forward = _forward;
	left = _left;
	right = _right;
	fInvisible = f;
	
	angle = 90.0f;
	curAngle = 0;
	length = 50;
	x = ofGetWidth()/2;
	y = ofGetHeight()/2;
	overWriteC = 0;
	overWriteC2 = 0;
	thickness = 50;
	
	bBox = 250;
	bearing = ofVec3f(1, 0, 0);
	lastP = ofVec3f(0, 0, 0);


	mesh->getMesh().setMode(OF_PRIMITIVE_LINES);
	pmesh->setMode(OF_PRIMITIVE_LINES);

	
}

void Turtle::setAngle(float _angle) {
    angle = _angle;
}

void Turtle::setLength(float _length) {
    length = _length;
}

void Turtle::draw(const string *input, float _x, float _y, float _angle, int lenEst, int iter){
	x = _x;
	y = _y;
	curAngle = _angle;
	bearing= ofVec3f(1, 0, 0);
	lastP = ofVec3f(0, 0, 0);
	header=orientation();
	
	
	lastlastP = lastP;
	dir = 4;
	
	
	mesh->getMesh().clear();
	mesh->setScale(1);
	for (char substr : *input) {		// check every character
		
		//letting the string edit the angle
		/*if (substr == '>')
		{
			if (dir == 10)
				dir = 0;
			dir++;
			setAngle(float(360) /float( dir));
		}
		if (substr == '<')
		{
			if (dir == 0)
				dir = 10;
			dir--;
			setAngle(float(360 )/ float(dir));
		}*/
		if (substr == forward)		// and act accordingly
			moveForward();
		if (substr == 'G')
			moveForward();
		if (substr == 'A')
			moveForward();
		if (substr == fInvisible)
			shift();
		if (substr == left)
			turnLeft();
		if (substr == right)
			turnRight();
		if (substr == '[')
			pushValues();
		if (substr == ']')
			popValues();
		if (substr == '&')
			pitchUp();
		if (substr == '^')
			pitchDown();
		if (substr == '_')
			rollLeft();
		if (substr == '=')
			rollRight();
	}
	

	//bounding box, to resize mesh to fit on-screen
	
		/*if (xExtremes.first->x < yExtremes.first->y) {
			minmum = xExtremes.first->x;
		}
		else { minmum = yExtremes.first->y; }
		if (xExtremes.second->x > yExtremes.second->y) {
			maxy = xExtremes.second->x;
		}
		else { maxy = yExtremes.second->y; }


		//cout << "\n" << mesh->getVertices().size() << "\n";


		//	cout << "\nOverWrite2: " << overWriteC2 << "\n";
		*/
#ifdef COUNTS

 // 

		unordered_map<std::pair<ofVec3f, ofVec3f>, int, hash_Line, eqFix> freq;
		for (auto point = mesh->getMesh().getVertices().begin(); point != mesh->getMesh().getVertices().end(); point += 2)
		{
			

			
			//if(hash_Vec3f() (*point) != hash_Vec3f() (*(point+1)))//looking at vertexs not lines right now, so we're counting those repeats not line repeats
			freq[make_pair(*(point), *(point + 1))]++;
			if (freq[make_pair(*(point), *(point + 1))] > 1)
				overWriteC2++;
		}
		
		//bool check = freq.key_eq()(make_pair(mesh->getMesh().getVertex(0), mesh->getMesh().getVertex(1)), make_pair(mesh->getMesh().getVertex(2), mesh->getMesh().getVertex(3)));
		/*auto fn = freq.hash_function();
		bool check = fn(make_pair(mesh->getVertex(0), mesh->getVertex(1))) == fn(make_pair(mesh->getVertex(2), mesh->getVertex(3)));*/
		
		//mesh debug info
		/*cout << "\nequal: " << check<<std::endl;
		cout << "\nL1: " << mesh->getMesh().getVertex(0) << " : " << mesh->getMesh().getVertex(1) << "\n";
		cout << "\nL2: " << mesh->getMesh().getVertex(2) << " : " << mesh->getMesh().getVertex(3) << "\n";
		cout << "\nSize of mesh: " << mesh->getMesh().getVertices().size() << endl;*/
		cout << "\nOverWrite2: " << overWriteC2 << "\n";

		freq.clear();
		overWriteC2 = 0;
#endif
		//bounding box, to resize mesh to fit on-screen
	//	if (!mesh->getMesh().getVertices().empty()) {
	//		auto xExtremes = minmax_element(mesh->getMesh().getVertices().begin(), mesh->getMesh().getVertices().end(),
	//			[](const ofPoint& lhs, const ofPoint& rhs) {
	//			return lhs.x < rhs.x;
	//		});
	//		auto yExtremes = minmax_element(mesh->getMesh().getVertices().begin(), mesh->getMesh().getVertices().end(),
	//			[](const ofPoint& lhs, const ofPoint& rhs) {
	//			return lhs.y < rhs.y;
	//		});
	//		auto zExtremes = minmax_element(mesh->getMesh().getVertices().begin(), mesh->getMesh().getVertices().end(),
	//			[](const ofPoint& lhs, const ofPoint& rhs) {
	//			return lhs.z < rhs.z;
	//		});



	//		auto collect1 = { xExtremes.first->x, yExtremes.first->y,zExtremes.first->z,
	//						 xExtremes.second->x, yExtremes.second->y , zExtremes.second->z };

	//		auto collect = { xExtremes.first->x - xExtremes.second->x, yExtremes.first->y- yExtremes.second->y  ,zExtremes.first->z- zExtremes.second->z};
	//		



	//		auto minmum = min_element(collect.begin(), collect.end());
	//		auto maxy = max_element(collect.begin(), collect.end());


	//	//cout << xExtremes.first->x<<'\n'<< yExtremes.first->y;
	//	//
	//		//mesh->setScale(ofGetHeight() / (*maxy));
	//	
	//	//for (ofVec3f ye : mesh->getMesh().getVertices())
	//	//{
	//	//	//cout <<"x:"<< ye.x<<" y:"<<ye.y << " z:"<<ye.z<<"\n";
	//	//	float newX = ofMap(ye.x , *minmum, *maxy, 25, ofGetWidth() - 25);
	//	//	float newY = ofMap(ye.y , *minmum, *maxy, 25, ofGetHeight() - 25);
	//	//	float newZ = ofMap(ye.z , *minmum, *maxy, -25, 25-ofGetHeight());

	//	//	//cout <<"x:"<< newX<<" y:"<<newY << " z:"<<newZ<<"\n";
	//	//	//finalMesh->addColor(ofColor(int(ye.x)%255,  int( ye.y)%255, int(ye.z)%255,120));
	//	//	finalMesh->addVertex(ofVec3f(newX, newY, newZ));
	//	//}
	//	cout << header.heading << "\n";
	//	


	//}
}
 
//only for 2d
void Turtle::printModel(const string *input, float _x, float _y, float _angle) {
	x = _x;
	y = _y;
	curAngle = _angle;

	pmesh->clear();
	for (char substr : *input) {		// check every character

		if (substr == forward)		// and act accordingly
			moveForwardPrint();
		if (substr == fInvisible)
			shift();
		if (substr == left)
			turnLeft();
		if (substr == right)
			turnRight();
		if (substr == '[')
			pushValues();
		if (substr == ']')
			popValues();
	}
	

}

void Turtle::moveForwardPrint() {
	
	float newX = x + (cos(ofDegToRad(curAngle))*length);
	float newY = y + (sin(ofDegToRad(curAngle))*length);


	////brownianNoise
	//float newX = x + (cos(ofDegToRad(curAngle))*length) + ((rand()%2==0)? 1:-1);
	//float newY = y + (sin(ofDegToRad(curAngle))*length) + ((rand() % 2 == 0) ? 1 : -1);


	//cout << "forward from: " << x << ", " << y << " to " << newX << ", " << newY << endl;

	auto testP = ofVec3f(x, 0.0f, y);
	auto testNewP = ofVec3f(newX, 0.0f, newY);

	auto testPZ = ofVec3f(x, thickness, y);
	auto testNewPZ = ofVec3f(newX, thickness, newY);
	
	pmesh->addColor(ofColor::fromHsb(/*int(testP.x) % 255*/85, int(testP.y) % 255 + 25, int(testP.z) % 255 + 80, 120));
	pmesh->addVertex(testP);
	pmesh->addVertex(testPZ);
	pmesh->addVertex(testNewP);
	

	


	/*pmesh->addVertex(testNewP);
	pmesh->addVertex(testPZ);
	pmesh->addVertex(testNewPZ);
*/

	//printed.newSubPath();
	//printed.lineTo(testP);
	/*printed.moveTo(testP);
	printed.lineTo(testNewP);
	
	printed.lineTo(testNewPZ);
	printed.lineTo(testPZ);
	printed.close();
	printed.simplify();*/
	
	
	x = newX;
	y = newY;
	//mesh->setMode(OF_PRIMITIVE_TRIANGLE_FAN);
}




void Turtle::drawPrint() {
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 255);

	pmesh->draw();
}


void Turtle::draw() {
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 255);
	mesh->draw();
}

//turtle stack pushing
void Turtle::pushValues(){

	posHis.push_back(lastP);
	bearingHis.push_back(header);
}

//turtle stack popping
void Turtle::popValues(){
	if (!(posHis.empty()&bearingHis.empty())) {
			
			lastP = posHis.back();
			header = bearingHis.back();
			posHis.pop_back();
			bearingHis.pop_back();
	}
}

void Turtle::moveForward(){

	auto newP = lastP + length * header.heading;

	//checking if adding a new point moves out of frame
	if (newP.x > bBox || newP.x < -bBox ||
		newP.y >bBox || newP.y < -bBox ||
		newP.z >bBox || newP.z < -bBox)
	{
		mesh->setScale(mesh->getScale()*0.999f);
		bBox *= 1.001f;
	}
	
	////brownianNoise
	//float newX = x + (cos(ofDegToRad(curAngle))*length) + ((rand()%2==0)? 1:-1);
	//float newY = y + (sin(ofDegToRad(curAngle))*length) + ((rand() % 2 == 0) ? 1 : -1);


	//cout << "forward from: " << x << ", " << y << " to " << newX << ", " << newY << endl; //debug stuff
	
	mesh->getMesh().addVertex( lastP );
	//mesh->getMesh().addVertex( newP );
	int c = int(newP.x)*int(newP.y)*int(newP.z);
	mesh->getMesh().addColor(ofColor::fromHsb(/*int(testP.x) % 255*/c%255,  240, /*int(newP.z) % 255*/  255));

	
	//mesh->getMesh().addVertex(lastlastP);

	//lastlastP = lastP;
	lastP = newP;
	//x = newX;
	//y = newY;
	
}

void Turtle::shift()
{
	auto newP = lastP + length * header.heading.normalize();
	lastP = newP;
}

void Turtle::turnLeft(){
	header.heading = mat3x3VecMul(makeRotMat(header.up.normalize(), angle), header.heading.normalize());
	header.left= mat3x3VecMul(makeRotMat(header.up.normalize(), angle), header.left.normalize());
}

void Turtle::turnRight(){
	header.heading = mat3x3VecMul(makeRotMat(header.up.normalize(), -angle), header.heading.normalize());
	header.left = mat3x3VecMul(makeRotMat(header.up.normalize(), -angle), header.left.normalize());
}


void Turtle::pitchUp()
{
	header.heading = mat3x3VecMul(makeRotMat(header.left.normalize(), -angle), header.heading.normalize());
	//header.left = mat3x3VecMul(makeRotMat(header.up, -angle), header.left);
	header.up = mat3x3VecMul(makeRotMat(header.left.normalize(), -angle), header.up.normalize());
}
void Turtle::pitchDown()
{
	header.heading = mat3x3VecMul(makeRotMat(header.left.normalize(), angle), header.heading.normalize());
	//header.left = mat3x3VecMul(makeRotMat(header.up, -angle), header.left);
	header.up = mat3x3VecMul(makeRotMat(header.left.normalize(), angle), header.up.normalize());
}


void Turtle::rollLeft() {
	header.left = mat3x3VecMul(makeRotMat(header.heading.normalize(), angle), header.left.normalize());
	header.up = mat3x3VecMul(makeRotMat(header.heading.normalize(), angle), header.up.normalize());

	
}
void Turtle::rollRight() {
	header.left = mat3x3VecMul(makeRotMat(header.heading.normalize(), -angle), header.left.normalize());
	header.up = mat3x3VecMul(makeRotMat(header.heading.normalize(), -angle), header.up.normalize());
}

void Turtle::save(string path) {
	//pmesh->save(path, TRUE);
	pmesh->save(path);
	
}
 //makes the rotation matrix about the current heading vector
ofMatrix3x3 Turtle::makeRotMat(ofVec3f ori,double rAngle) {

	//cout << "\nInside make Rot, tested value: "<<  myCos(rAngle) <<endl; //debug stuff
	return(ofMatrix3x3(
		myCos(rAngle) + (double)ori.x*(double)ori.x*(1 - myCos(rAngle)), (double)ori.x*(double)ori.y*(1 - myCos(rAngle)) - (double)ori.z*mySin(rAngle), (double)ori.x*(double)ori.z*(1 - myCos(rAngle)) + (double)ori.y*mySin(rAngle),

		(double)ori.x*(double)ori.y*(1 - myCos(rAngle)) + (double)ori.z*mySin(rAngle), myCos(rAngle) + (double)ori.y*(double)ori.y*(1 - myCos(rAngle)), (double)ori.y*(double)ori.z*(1 - myCos(rAngle)) - (double)ori.x*mySin(rAngle),

		(double)ori.x*(double)ori.z*(1 - myCos(rAngle)) - (double)ori.y*mySin(rAngle), (double)ori.y*(double)ori.z*(1 - myCos(rAngle)) + (double)ori.x*mySin(rAngle), myCos(rAngle) + (double)ori.z*(double)ori.z*(1 - myCos(rAngle)))
		); 
}

//collum vector matrix multiplication 
inline ofVec3f Turtle::mat3x3VecMul(ofMatrix3x3 rot, ofVec3f ori) {
	//cout << "\nX: " << ori.x << "  Y: " << ori.y<<"  Z: " << ori.z << "\n";
	return(
		ofVec3f(
			rot[0] * (double)ori.x + rot[3] * (double)ori.y + rot[6] * (double)ori.z,
			rot[1] * (double)ori.x + rot[4] * (double)ori.y + rot[7] * (double)ori.z,
			rot[2] * (double)ori.x + rot[5] * (double)ori.y + rot[8] * (double)ori.z
		)

		);
}

Turtle::~Turtle()
{
	delete mesh;
}