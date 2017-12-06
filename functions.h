#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "imu.h"

void calculaterollpitch(string filename, string rotation, string filenameout); //read acceleration data from a file, calculate its roll and pitch andle and storage in another file
void calculateanglebetween2vec(string filename1, string filename2, string filenameout); //read acceleration data from filename1 and filename2, calculate the angle between the two vectors, and save in filenameout
void calculatetiltang(string filename1, string filenameout); //read acceleration data from filename1, calculate the tilt angle and save in filenameout
int sgn(double n); //return the signal of n 
vector<vector<float> >sinc(vector<vector<float> > x, vector<vector<float> > y);//sincronize two data by timestamp
vector<vector<float> >readfile(string filename); //read a file returning a vector<vector> with the configurarion [columns][lines]
void writefile(string filenameout,vector<vector <float> > data);	//write the float data to the file "filenameout"
void writefilestr(string filenameout, vector < vector < string> > data); //write the string data to the file "filenameout" 
vector<vector<float> >transpose(vector<vector<float> > x);	//transpose x
void organizeinput(int argc, char * argv []); //select the correct function and parameters from terminal or input arguments
vector < vector <float> >lowpassfilter(vector < vector <float> > x, float wc ); //lowpassfilter, where x is the input for filtering and wc the cutoff frequency

#endif /* FUNCTIONS_H */