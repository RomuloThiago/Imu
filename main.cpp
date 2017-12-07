#include "imu.h"
#include "functions.h"
/*
Purpose: Calculate roll, pitch and tilt angle from accelerometer data, calculate angle and normal vector between two accelerometer data
and define screen rotation using accelerometer. The functions are based on the approach of [1].

@author Romulo S. Rosa
@version 1.0 06/12/2017

Reference:
[1] PEDLEY, M. Tilt sensing using a three-axis accelerometer.Freescale semi-conductor application note, v. 1, p. 2012–2013, 2013
*/

int main(int argc, char * argv []) //receive the argument from terminal or from user input, the program will work until a exit command
{
/*	string filename1 = "dvl_unsinc.log";
	string filename2 = "gt_pose_unsinc.log";
	vector < vector < float > > y = readfile(filename1);
	vector < vector < float > > x = readfile(filename2);
	vector < vector < float > > output;

	output = sinc(x,y);*/

	string aux;
	char **input = new char*[20];
	int i=1;
	if(argc>1)
		organizeinput(argc,argv);
	while(1)
	{
		cout<<"Enter the desired command:"<<endl;
		cin.clear();
		
		while(cin.peek() != '\n')
		{
			cin>>aux;
			strcpy(input[i] = new char[aux.length()],aux.c_str());
			i++;		
		}
		organizeinput(i,input);
		cin.ignore(10000, '\n');// ignore next \n, to clean cin.peek;
	}
	return 0;
}