#ifndef IMU_H
#define IMU_H
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <math.h>
#include <fstream>
#include <sstream>
using namespace std;
#define PI 3.14159265
#define mu 0.01
#include "functions.h"

class Imu
{
private:
	float timestamp; //timestamp of the acceleration vector [m]
	float ax; 	//acceleration in x [g]
	float ay;	//acceleration in y [g]
	float az;	//acceleration in z [g]
	float bx; 	//complementary acceleration in x [g]
	float by;	//complementary acceleration in y [g]
	float bz;	//complementary acceleration in z [g]
	float pitch; //angle around y axis [degree]
	float roll; //angle around x axis [degree]
	void rotationxyz(); //calculate roll and pitch in xyz rotation sequence
	void rotationyxz(); //calculate roll and pitch in yxz rotation sequence

public:
	string rotationorder; //standard ordering rotation (aerospace rotation sequence)
	float getaccelerationx(); 	//return acceleration in x [g]
	float getaccelerationy();	//return acceleration in y [g]
	float getaccelerationz();	//return acceleration in z [g]
	float getaroll(); 	//return roll angle [degree]
	float getpitch();	//return pitch angle [degree]
	vector<float> defineattitude(float Ax,float Ay, float Az); //calculate attitude, calling rotationxyz() or rotationyxz() and returning roll and pitch [degree]
	float anglebetween(float Ax,float Ay,float Az,float Bx,float By,float Bz); //return the angle between vector a and b [degree]
	float calculatetiltangle(float Ax, float Ay, float Az); //calculate the angle between the gravity and the z axis of the body [degree]
	vector <float> normalvector(float Ax,float Ay,float Az,float Bx,float By,float Bz); //calcuate the normal vector between two vectors [x , y, z]
	string screen(float Ax, float Ay, float Az);//return the transition based in the acceleration axes [string]
	vector <float> normalize(float Ax, float Ay, float Az); //return Ax, Ay and Az normalized
};	
#endif /* IMU_H */