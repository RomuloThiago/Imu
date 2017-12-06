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
	float mod = sqrt(Ax*Ax + Ay*Ay + Az*Az); //convert the acceleration from m/s2 to g
	ax =Ax/mod;
	ay =Ay/mod;
	az =Az/mod;

	if (!(rotationorder.compare("xyz"))) //return 0 if the string rotation order is equal to 'xyz'
	{
		rotationxyz();
	}	
	else if (!(rotationorder.compare("yxz"))) //return 0 if the string rotation order is equal to 'yxz'
	{
		rotationyxz();
	}	
	else
	{
		cout<<"Error: The rotation order provided is not correct, the rotation allowed are xyz and yxz"<<endl; 
		abort();
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
	float div = (sqrt(Ax*Ax + Ay*Ay + Az*Az)*sqrt(Bx*Bx + By*By + Bz*Bz));
	normal.push_back(float((Ay*Bz - Az*By)/div));
	normal.push_back(float((Az*Bx - Ax*Bz)/div));
	normal.push_back(float((Ax*By - Ay*Bx)/div)); //Equation 47 of [1]
	return normal;
}

string Imu::Screen(float Ax, float Ay, float Az)
{
	float mod = sqrt(Ax*Ax + Ay*Ay + Az*Az);
	if(Az/mod < 0.5)
	{
	 	if(Ax/mod < 0.4)
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
		if(Ay/mod < 0.4)
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
