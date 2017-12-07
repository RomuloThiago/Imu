#include "imu.h"
#include "functions.h"

void Imu::rotationxyz() 
{
	pitch = atan2(-ax, sqrt(ay*ay + az*az))*180/PI; //Eq 26 and 38 [1]	
	roll = atan2(ay, sgn(az)*sqrt(az*az+mu*ax*ax))*180/PI; //Eq 37 [1]
}

void Imu::rotationyxz()
{
	roll = atan2(ay, sqrt(ax*ax + az*az))*180/PI; //Eq 28 [1]
	pitch = atan2(-ax, sgn(az)*sqrt(az*az + mu*ay*ay))*180/PI; //Eq 42 [1]
}

float Imu::getaccelerationx()//return acceleration in x
{
	return ax; 
}

float Imu::getaccelerationy()//return acceleration in y
{
	return ay;	
}

float Imu::getaccelerationz()//return acceleration in z
{
	return az;	
}

float Imu::getaroll()//return roll angle
{
	return roll;	
}

float Imu::getpitch()//return pitch angle
{
	return pitch;	
}
	
vector<float> Imu::defineattitude(float Ax, float Ay, float Az)
{
	//receive acceleration in x, y and z and return roll and pitch
	vector <float> A_vector = normalize(Ax, Ay, Az); //normalize(Ax, Ay, Az);

	ax = A_vector[0];
	ay = A_vector[1];
	az = A_vector[2];

	if (!(rotationorder.compare("yxz"))) //return 0 if the string rotation order is equal to 'yxz'
	{
		rotationyxz();
	}	
	else
	{
		rotationorder = "xyz";
		rotationxyz();
	}	

	vector<float> x;
	x.push_back(roll);
	x.push_back(pitch);

	return x; 
}

float Imu::anglebetween(float Ax, float Ay, float Az, float Bx, float By, float Bz) //return the angle between vector a and b in degrees
{

	float angle = acos((Ax*Bx + Ay*By + Az*Bz)/(sqrt(Ax*Ax + Ay*Ay + Az*Az)*sqrt(Bx*Bx + By*By + Bz*Bz))); //Equation 45 of [1]
	return angle*180/PI;
}

float Imu::calculatetiltangle(float Ax, float Ay, float Az)
{
	return acos(Az/sqrt(Ax*Ax + Ay*Ay + Az*Az))*180/PI;
}

vector <float> Imu::normalvector(float Ax, float Ay, float Az, float Bx, float By, float Bz) //return the normal of two vectors
{
	vector <float> normal;
	vector <float> A_vector = {Ax, Ay, Az}; //normalize(Ax, Ay, Az);
	vector <float> B_vector = {Bx, By, Bz}; //normalize(Bx, By, Bz);
	float div = (sqrt(A_vector[0]*A_vector[0] + A_vector[1]*A_vector[1] + A_vector[2]*A_vector[2])*sqrt(B_vector[0]*B_vector[0] + B_vector[1]*B_vector[1] + B_vector[2]*B_vector[2]));
	normal.push_back(float((A_vector[1]*B_vector[2] - A_vector[2]*B_vector[1])/div));
	normal.push_back(float((A_vector[2]*B_vector[0] - A_vector[0]*B_vector[2])/div));
	normal.push_back(float((A_vector[0]*B_vector[1] - A_vector[1]*B_vector[0])/div)); //Equation 47 of [1]
	return normal;
	return normal;
}

string Imu::screen(float Ax, float Ay, float Az)
{
	vector <float> A_vector = normalize(Ax, Ay, Az);
	if(A_vector[2] < 0.5)
	{
	 	if(A_vector[0] < 0.4)
		{
			if(Ay > 0.5)
			{
				return string("Change orientation to Right");
			}
			else if(Ay < -0.5)
			{
				return string("Change orientation to Left");
			}

		}
		if(A_vector[1] < 0.4)
		{
			if(Ax > 0.5)
			{
				return string("Change orientation to Top");
			}
			else if(Ay < -0.5)
			{
				return string("Change orientation to Bottom");
			}
		}
	}
	return string("Do not change orientation");
}

vector <float> Imu::normalize(float Ax, float Ay, float Az)
{
	vector<float> output;
	float module = Ax*Ax + Ay*Ay + Az*Az;
	output.push_back(Ax/module);
	output.push_back(Ay/module);
	output.push_back(Az/module);
	return output;
}
