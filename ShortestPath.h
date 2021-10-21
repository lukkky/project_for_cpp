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
* 最短路径类，使用Dijkstra算法确定最短路径，并输出对应路径上的主要建筑物；*/
class ShortestPath
{
private:
	DirectedEdge* edgeTo;//存放边；
    double* distTo;//存放由起点到该点的权重；a
    IndexMinPQ<double>*pq;//索引优先队列，用于存放非树点；
    int s=0;//起点；
	int e = 0;//终点
	EdgeWeightedDigraph* graph;
public:
	~ShortestPath()
	{
		delete[]edgeTo;
		delete[]distTo;
		delete pq;
	}
ShortestPath(EdgeWeightedDigraph&G, int s,int e)//寻找最短路径；
{
	graph = &G;
	edgeTo = new DirectedEdge[G.getV()];
	distTo = new double[G.getV()];
	this->s = s;
	this->e = e;
	pq = new IndexMinPQ<double>(G.getV());
	for (int v = 0; v < G.getV(); v++)
		distTo[v] = 100000;//全部设置成double的最大值；
	distTo[s] = 0;//起点设置成0；
	pq->insert(s, 0.0);
	while (!pq->isEmpty())
		relax(G, pq->delMin());
}
private:
	 void relax(EdgeWeightedDigraph& G, int v)//放松第v个非树节点；
	 {
		 int n = G.getAdj(v).size();
		 DirectedEdge e;
		  for (int i=0;i<n;i++)
		  {
			  e = G.getAdj(v)[i];
			  int w= e.to();
			  if (distTo[w] > distTo[v]+ e.getWeight())//更新数据，确保每一个树节点到根节点都是最短路径；
			  {
			  distTo[w] = distTo[v] + e.getWeight();
			  edgeTo[w] = e;
			  if (pq->contains(w))pq->changeKey(w, distTo[w]);
			  else pq->insert(w, distTo[w]);
			  }

		  }
	 }
public:
	double DistTo(int v)//到v点整条路的最小权重；
{
	return distTo[v];
}
bool hasPathTo(int v)
{
	return distTo[v] <100000;//小于DBL_MAX时也就是此点可以到达；
}
void pathTo(int v)
{
	if (!hasPathTo(v))
	{
		cerr <<(*graph).findKey(v)<<"is not accessable." << endl;
		return;
	}
	for (DirectedEdge e = edgeTo[v]; ; e = edgeTo[e.from()])//最后一条边的终点是s，以此作为结束条件；
	{
		graph->showString(e);
		cout << endl;//从终点逐步回溯至起点；
		if (e.from() == s)
			return;
	}
}
};