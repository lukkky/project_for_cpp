#include"DirectedEdge.h"
#include"EdgeWeightedDigraph.h"
#include"ShortestPath.h"
#include<fstream>
#include<map>
using namespace std;
int main()//测试代码
{
	ifstream input("tinyEWG.txt");//建立一个节点位置和节点的对应表；//现在先测试的是节点名称是数字；
	string start;
	string end;
	if (input)
	{
		EdgeWeightedDigraph graph(input);
		cout << "chose the start and end from the graph with" << graph.getV()<<"nodes." << endl;
		cin >> start >> end;
		int n = graph.getV();
		int v = graph.query(start, end).first;//获得起点
		int w = graph.query(start, end).second;//获得终点对应的数字表示；
		ShortestPath sp(graph, v, w);//生成最短路径
		cout << "the shortest way from " << start << "to:" << end<<"is:" << endl;
		sp.pathTo(w);
	}
	else
	{
		cerr << "fail to open file!" << endl;
		abort();
	}
	return 0;
}
