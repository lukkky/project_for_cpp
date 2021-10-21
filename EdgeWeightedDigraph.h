#pragma once
#include"DirectedEdge.h"
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include"Bag.h"
#include<math.h>
#include<utility>
#include<map>
using namespace std;
class  EdgeWeightedDigraph//��Ȩ����ͼ
{
private:
	   int V=0;//��������
	   int E=0;//��������
	   Bag<DirectedEdge>*adj;//�ڽӱ�
	   map<string, int>name;
	   int counts = 0;
public: 
	EdgeWeightedDigraph(int V):V(V),E(0)
    {
	adj = new Bag<DirectedEdge>[V];
    }
	EdgeWeightedDigraph(ifstream& in)//������ֱ�ӻ�ȡ��ͼ��Ϣ��//��Ҫ�����ı��ļ���
	/*
	* Ҫ�ȴ���ߣ����ܴ���ͼ��
	*/
	{
		in >> V >> E;
		adj = new Bag<DirectedEdge>[V];		
		string line;
		while (in.fail() == false)
		{
			int v, w;//�����յ�Ķ�Ӧ����
			string sv, sw;//�����յ��string��ʾ��
			string rode;
			double x1,y1,x2,y2;//��Ӧһ���ߵ������յ㣻
			in >> sv >> sw >>rode>> x1>>y1>>x2>>y2;//���������յ㣬�Լ���Ӧ�����ꣻ
			if ((name.insert(make_pair(sv, ++counts))).second)
				v = counts;//�������ֽڵ��string����֮���ӳ�䣻
			else
			{
				if (name.find(sv) != name.end())
				{
					v = name.find(sv)->second;
					counts--;//������������ԭ����λ�ã���ֹconuts����8��8������ܴﵽ��С����
				}
			}
			if ((name.insert(make_pair(sw, ++counts))).second)
				w = counts;
			else
			{
				if (name.find(sw) != name.end())
				{
					w = name.find(sw)->second;
					counts--;
				}
			}
			double weight = Weight(x1, y1, x2, y2);//����ߵ�Ȩ��
			string building;
			string barrier;
			vector<string>buildings;//������Ҫ����
			vector<string>barriers;//������Ҫ�ϰ���
			getline(in, line);//Ϊ�˻���׼���Ĺ������ӵ�ǰ��ȡ���ݵ�һ����ת����һstring�У�
			if (getline(in, line))//������Ҫ����
			{
				istringstream sin(line);
				while (sin >> building)
					buildings.push_back(building);
			}
			if (getline(in, line))//�����ϰ��
			{
				istringstream sin(line);
				while (sin >> barrier)
					barriers.push_back(barrier);
			}
			DirectedEdge temp(v, w, weight,rode, buildings, barriers);
			adj[v].add(temp);//����ߣ�
		}
	};
    EdgeWeightedDigraph() {};
    int getV() { return V; }
    int getE() { return E; }
    void addEdge(DirectedEdge e)
    {
	adj[e.from()].add(e);
	E++;
    }
	Bag<DirectedEdge>* edges()
    {
	Bag<DirectedEdge>* bag = new Bag<DirectedEdge>();
	for (int v = 0; v < V; v++)
	{
		auto* beg = adj[v].begin();
		int n = adj[v].size();
		while (n>1)
		{
			bag->add(beg->item);
			beg = beg->next;
			n--;
		}
	}
	return bag;
    }
    Bag<DirectedEdge>&getAdj(int v)
    {
	return adj[v];
    }
	int Node()
	{
		return V;
	}
	double Weight(double x1, double y1, double x2, double y2)//������֮���ֱ�߾�����ΪȨ�أ�
	{
		double tempx = (x1 - x2) * (x1 - x2);
		double tempy = (y1 - y2) * (y1 - y2);
		return pow(tempx + tempy, 0.5);
	}
	pair<int, int>query(string s, string e)
	{
		auto iterv = name.find(s);//������ļ�ֵ��ָ�룻
		auto iterw = name.find(e);//����յ�ļ�ֵ��ָ�룻
		if (iterv != name.end() && iterw != name.end())
			return make_pair(iterv->second, iterw->second);
		else//����˿���ѡ������һ�����ֱ���˳���
		{
			string start, end;
			char ch;
			cerr << "start and end do not exsist in the graph.\n"
				<< "try again(y)/quit(n):";
				cin >> ch;
			if (ch == 'y')
			{
				cout << "enter the start:\n"
					<< "enter the end:\n";
				cin >> start >> end;
				query(start, end);
			}
			else
				exit(1);
		}
	}
	void showString(DirectedEdge e)
	{
		int v = e.from();
		int w = e.to();
		cout << findKey(v) << "->" << findKey(w) << '\n';
		e.showString();
		
	}
	string findKey(int value)//��ʵֵ��Ӧ�ļ�ֵ���Ա�����ص����ƣ�
	{
		for (auto it = name.begin(); it != name.end(); it++)
			if (it->second == value)
				return it->first;
	}
};