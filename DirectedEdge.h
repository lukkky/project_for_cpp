#pragma once
#include<string>
#include<iostream>
#include<vector>
using namespace std;
class DirectedEdge//��Ȩ�����
{
private: int v=0;//�ߵ����
int w=0;//�ߵ��յ㣻
 double weight=0;//�ߵ�Ȩ�أ�
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
