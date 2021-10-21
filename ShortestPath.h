#pragma once
#include "EdgeWeightedDigraph.h"
#include "DirectedEdge.h"
#include<queue>
#include<float.h>
#include<utility>
#include<functional>
#include<stack>
#include<memory>
#include"IndexMiniPQ.h"
using namespace std;
/*
* ���·���࣬ʹ��Dijkstra�㷨ȷ�����·�����������Ӧ·���ϵ���Ҫ�����*/
class ShortestPath
{
private:
	DirectedEdge* edgeTo;//��űߣ�
    double* distTo;//�������㵽�õ��Ȩ�أ�a
    IndexMinPQ<double>*pq;//�������ȶ��У����ڴ�ŷ����㣻
    int s=0;//��㣻
	int e = 0;//�յ�
	EdgeWeightedDigraph* graph;
public:
	~ShortestPath()
	{
		delete[]edgeTo;
		delete[]distTo;
		delete pq;
	}
ShortestPath(EdgeWeightedDigraph&G, int s,int e)//Ѱ�����·����
{
	graph = &G;
	edgeTo = new DirectedEdge[G.getV()];
	distTo = new double[G.getV()];
	this->s = s;
	this->e = e;
	pq = new IndexMinPQ<double>(G.getV());
	for (int v = 0; v < G.getV(); v++)
		distTo[v] = 100000;//ȫ�����ó�double�����ֵ��
	distTo[s] = 0;//������ó�0��
	pq->insert(s, 0.0);
	while (!pq->isEmpty())
		relax(G, pq->delMin());
}
private:
	 void relax(EdgeWeightedDigraph& G, int v)//���ɵ�v�������ڵ㣻
	 {
		 int n = G.getAdj(v).size();
		 DirectedEdge e;
		  for (int i=0;i<n;i++)
		  {
			  e = G.getAdj(v)[i];
			  int w= e.to();
			  if (distTo[w] > distTo[v]+ e.getWeight())//�������ݣ�ȷ��ÿһ�����ڵ㵽���ڵ㶼�����·����
			  {
			  distTo[w] = distTo[v] + e.getWeight();
			  edgeTo[w] = e;
			  if (pq->contains(w))pq->changeKey(w, distTo[w]);
			  else pq->insert(w, distTo[w]);
			  }

		  }
	 }
public:
	double DistTo(int v)//��v������·����СȨ�أ�
{
	return distTo[v];
}
bool hasPathTo(int v)
{
	return distTo[v] <100000;//С��DBL_MAXʱҲ���Ǵ˵���Ե��
}
void pathTo(int v)
{
	if (!hasPathTo(v))
	{
		cerr <<(*graph).findKey(v)<<"is not accessable." << endl;
		return;
	}
	for (DirectedEdge e = edgeTo[v]; ; e = edgeTo[e.from()])//���һ���ߵ��յ���s���Դ���Ϊ����������
	{
		graph->showString(e);
		cout << endl;//���յ��𲽻�������㣻
		if (e.from() == s)
			return;
	}
}
};