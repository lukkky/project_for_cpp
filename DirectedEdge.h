#pragma once
#include<string>
#include<iostream>
#include<vector>
using namespace std;
class DirectedEdge//加权有向边
{
private: int v=0;//边的起点
int w=0;//边的终点；
 double weight=0;//边的权重；
 string rode;
 vector<string>buildings;
 vector<string>barriers;
public: DirectedEdge(int nv,int nw, double nweight,string nrode,vector<string>nbuildings,vector<string>nbarriers)
	:v(nv), w(nw), weight(nweight),buildings(nbuildings),barriers(nbarriers),rode(nrode)
{}
DirectedEdge(){};
double getWeight()
{
	return weight;
}
int from()
{
	return v;
}
 int to()
{
	return w;
}
 void showString()
 {
	 cout 
		 <<"you can go along the "<<rode<<"\nstreet. and the linear distance is:\n"
		 << weight
		 << "the main buildings along the path :\n";
	 for (auto x : buildings)
		 cout << x << endl;
	 cout << "thw barriers you should watch out bellow:\n";
	 for (auto x : barriers)
		 cout << x << endl;

 }
};
