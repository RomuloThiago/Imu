#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "imu.h"

void f1(string filename, string rotation, string filenameout); //read acceleration data from a file, calculate its roll and pitch andle and storage in another file
void f2(string filename1, string filename2, string filenameout); //read acceleration data from filename1 and filename2, calculate the angle between the two vectors, and save in filenameout
int sgn(double n); //return the signal of n 
vector<vector<float> >sinc(vector<vector<float> > x, vector<vector<float> > y);//sincronize two data by timestamp
vector<vector<float> >readfile(string filename); //read a file returning a vector<vector> with the configurarion [columns][lines]
void writefile(string filenameout,vector<vector <float> > data);	//write the data to a the file "filenameout"
vector<vector<float> >transpose(vector<vector<float> > x);	//transpose x

#endif /* FUNCTIONS_H */