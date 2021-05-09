
#pragma once
//#define COUNTS
#include "ofMain.h"
#include <vector>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp> 

//defining different cosines for preformance vs accuracy
#ifdef COUNTS
using boost::multiprecision::cpp_dec_float_50;
template<typename T>
inline T myCos(T r)
{
	
	using boost::math::constants::pi;
	cpp_dec_float_50 x = pi<cpp_dec_float_50>() * r / 180.0f;
	cpp_dec_float_50 y = cos(x);
	return y.convert_to<T>();
}
template<typename T>
inline T mySin(T r)
{

	using boost::math::constants::pi;
	cpp_dec_float_50 x = pi<cpp_dec_float_50>() * r / 180.0f;
	cpp_dec_float_50 y = sin(x);
	return y.convert_to<T>();
}
#else
template<typename T>
inline T myCos(T r)
{

	
	return cos(ofDegToRad(r));
}
template<typename T>
inline T mySin(T r)
{

	
	return sin(ofDegToRad(r));
}
#endif

using namespace std;

class Turtle {
	
public:
	

	Turtle();
	~Turtle();
	Turtle(char _forward, char _left, char _right, char f);
	Turtle(string forward, string left, string right, string f);
    void setAngle(float angle);
    void setLength(float length);
    
	void draw(const string* input, float x, float y, float angle, int lenEst, int iter);
	void printModel(const string * input, float _x, float _y, float _angle);
	void DrawData(const string * input, float _x, float _y, float _angle);
	void moveForwardPrint();
	void draw();
	void moveForward();
	void shift();
	void turnLeft();
	void turnRight();

	void drawPrint();
	
	void pitchUp();
	void pitchDown();
	void rollLeft();
	void rollRight();
	void save(string path);
	
	class orientation {
	public:
		ofVec3f heading;
		ofVec3f left;
		ofVec3f up;
		orientation() {
			heading = ofVec3f(1, 0, 0); left = ofVec3f(0, 0, 1); up = ofVec3f(0, 1, 0);
		}
	};
	ofMatrix3x3 makeRotMat(ofVec3f ori,double rAngle);
	ofVec3f mat3x3VecMul(ofMatrix3x3 rot, ofVec3f ori);
protected:
	
	
	/*string forward;
	string left;
	string right;*/
	char forward;
	char left;
	char right;
	char fInvisible;
	
	of3dPrimitive * mesh =new of3dPrimitive();

	int overWriteC;
	int overWriteC2;
	int dir;

	
	float thickness;

	double bBox;
	double angle;
	float curAngle;
	float length;
	float x;
	float y;
	
	ofPath printed;
	ofVboMesh tess;

	ofMesh* pmesh=new ofMesh();

	vector<float> xHis;
	vector<float> yHis;
	vector<float> aHis;

	vector<ofVec3f>posHis;
	vector<orientation>bearingHis;
	
	ofVec3f bearing;
	ofVec3f lastP;
	ofVec3f newP;
	ofVec3f lastlastP;
	orientation header;
	void pushValues();
	void popValues();
	ofstream exportVerts;
};
