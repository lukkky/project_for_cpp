#include"DirectedEdge.h"
#include"EdgeWeightedDigraph.h"
#include"ShortestPath.h"
#include<fstream>
#include<map>
using namespace std;
int main()//���Դ���
{
	ifstream input("tinyEWG.txt");//����һ���ڵ�λ�úͽڵ�Ķ�Ӧ��//�����Ȳ��Ե��ǽڵ����������֣�
	string start;
	string end;
	if (input)
	{
		EdgeWeightedDigraph graph(input);
		cout << "chose the start and end from the graph with" << graph.getV()<<"nodes." << endl;
		cin >> start >> end;
		int n = graph.getV();
		int v = graph.query(start, end).first;//������
		int w = graph.query(start, end).second;//����յ��Ӧ�����ֱ�ʾ��
		ShortestPath sp(graph, v, w);//�������·��
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
