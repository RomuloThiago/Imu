#include "imu.h"
#include "functions.h"
#include <algorithm>

void f1(string filename, string rotation, string filenameout)
{
	vector < float> angles;
	vector < vector < float> > storagevec(3);
	Imu imu;
	vector < vector < float> > x = readfile(filename); //receives the vector of timestamp, acceleration in x, acceleration in y and acceleration in z
	for (int i = 0; i < x[0].size();i++)
	{
		imu.rotationorder = rotation;
		angles = imu.defineattitude(x[1][i], x[2][i], x[3][i]);
		storagevec[0].push_back(x[0][i]);
		storagevec[1].push_back(angles[0]);
		storagevec[2].push_back(angles[1]);
	}
	writefile(filenameout, storagevec);
	cout<<"The program extracted the accelerations in "<<filename<<", estimated the angles roll and pitch in "<<rotation<<" rotation sequence and stored in "<<filenameout<<", with the following configuration: timestamp [s], roll [degree], pitch [degree]"<<endl;
}

void f2(string filename1, string filename2, string filenameout)
{
	float angle;
	vector < vector < float> > storagevec(2);
	vector < vector < float> > y;
	Imu imu;
 	vector < vector < float > > x = readfile(filename1); //receives the vector of timestamp, acceleration in x, acceleration in y and acceleration in z
 	float diff; //sum of the differences between two timestamp vectors
 	if (filename2 == "") //in case which both vectors are in the same file
 	{		
 		y.resize(4);
 		for(size_t i = 0; i < x[0].size(); i++)
 		{
 			y[0].push_back(x[x.size()-4][i]);
 			y[1].push_back(x[x.size()-3][i]);
 			y[2].push_back(x[x.size()-2][i]);
 			y[3].push_back(x[x.size()-1][i]);
 			diff += x[0][i] - y[0][i];
 		}
 		if(x.size() == 7) //in case which the input is timestamp, ax, ay, az, bx, by, bz (same timestamp, there is no need to sincronize)
 		{
 			diff = 0;
 		}
 	}
 	else
 		y = readfile(filename2);
 	diff = x[0].size()*11; //REMOVE AFTER TEST THE FUNCTION SINC
 	if(diff/x[0].size() > 10 || x[0].size()!=y[0].size())
 	{
 		vector < vector < float > > result = sinc(x,y);
 	}
 	for (int i = 0; i < x[0].size();i++)
 	{
	 	angle = imu.anglebetween(x[1][i], x[2][i], x[3][i], y[1][i], y[2][i], y[3][i]);		
	 	storagevec[0].push_back(x[0][i]);
	 	storagevec[1].push_back(angle);
 	}
 	writefile(filenameout, storagevec);
 	cout<<"The program extracted the accelerations in "<<filename1<<" and "<<filename2<<", estimated the angle between the two accelerations, and stored in "<<filenameout<<", with the following configuration: timestamp [s], angle [degree]"<<endl;
}

vector<vector<float> >transpose(vector<vector<float> > x)
{
	vector<vector<float> > y(x[0].size(),vector <float> (x.size()));
	for(int i=0; i<x[0].size(); i++)
	{
		for(int j=0; j<x.size();j++)
		{
			y[i][j] = x[j][i];
		}
	}
	return y; //return x transposed
}

vector<vector<float> >sinc(vector<vector<float> > x, vector<vector<float> > y)
{
	int i = 0, j = 0, k = 0;
	vector<vector<float> > result; //output sincronized
	result.resize(x[0].size()); //allocate memory
	vector<vector<float> > xt = transpose(x);
	vector<vector<float> > yt = transpose(y);

	sort(xt.begin(), xt.end(), [](const vector< float >& a, const vector< float >& b){ return a[0] < b[0]; } );//sort by the first element of the vector(vector) by crescent order
	sort(yt.begin(), yt.end(), [](const vector< float >& a, const vector< float >& b){ return a[0] < b[0]; } );//sort by the first element of the vector(vector) by crescent order

	while(i < x[0].size() && j < y[0].size())
	{
		if(xt[i][0]==yt[j][0])
		{
			result[k].resize(xt[0].size() + yt[0].size()); //realocate memory
			copy (xt[i].begin(), xt[i].begin() + xt[i].size(),result[k].begin());
			copy (yt[j].begin(), yt[j].begin() + yt[i].size(),result[k].begin() + xt[i].size());
			k+=1;
			i+=1;
			j+=1;
		}
		else
		{
			i+=1;
			j+=1;	
		}
	}
	writefile("sinc.log",transpose(result));
	return transpose(result);
}

int sgn(double n) 
{
	if (n < 0) return -1;
	if (n >= 0) return 1;
}

vector < vector < float> >readfile(string filename)
{
	ifstream read;
	read.open(string("Data/").append(filename).c_str());
	string line, aux;
	getline(read,line);
	aux = line;
	int nfield = 1;
	while(aux.find(';') <= aux.length()) //define the archive number of columns 
	{
		aux.erase(0, aux.find(';') + 1);
		nfield += 1;
	}
	vector < vector < float> > p(nfield);
	float value;
	read.clear();
	read.seekg(0, ios::beg); //reset the archive pointer
	if(read.is_open())
	{	
		while(getline(read, line))
  		{
  			aux = line;
			for(int i = 0; i < nfield; i++)
			{
				stringstream conv(aux.substr(0, aux.find(';')));
				aux.erase(0, aux.find(';') + 1);
				conv >> value;
				conv.clear();
				p[i].push_back(value);
			}
		}
		if(p[0].size() == 0)
		{
		 	cout<<"Error: The file "<<filename<<" is empty."<<endl;
		 	abort();			
		}
	}
	else
	{
		cout<<"Error: The file input "<<filename<<" was not open."<<endl;
		abort();
	}
	read.close();
	return p;
}

void writefile(string filenameout, vector < vector < float> > data)
{
	ofstream outfile(string("Data/").append(filenameout).c_str());
	string aux;
	stringstream conv;
	if(outfile)
	{	
		for (int i = 0; i < data[0].size(); i++)
		{
			for(int j = 0; j < data.size(); j++)
			{
			 	conv << (data[j][i]); //convert float to string
				aux.append(conv.str());
				aux.append(";\t");			
				conv.str(string()); //to clear the stringstream
				conv.clear();
			}
		outfile<<aux.erase(aux.length()-2,aux.length())<<endl; //for removing the last ';'
		aux=string(); //clear aux
		}
	}
	else
	{
		cout<<"Error: The output file could not be created."<<endl;
		outfile.close();
		abort();
	}
	outfile.close();
}
void writefilestr(string filenameout, vector < vector < string> > data)
{
	ofstream outfile(string("Data/").append(filenameout).c_str());
	string aux;
	stringstream conv;
	if(outfile)
	{	
		for (int i = 0; i < data[0].size(); i++)
		{
			for(int j = 0; j < data.size(); j++)
			{
			 	conv << (data[j][i]); //convert float to string
				aux.append(conv.str());
				aux.append(";\t");			
				conv.str(string()); //to clear the stringstream
				conv.clear();
			}
		outfile<<aux.erase(aux.length()-2,aux.length())<<endl; //for removing the last ';'
		aux=string(); //clear aux
		}
	}
	else
	{
		cout<<"Error: The output file could not be created."<<endl;
		outfile.close();
		abort();
	}
	outfile.close();
}
