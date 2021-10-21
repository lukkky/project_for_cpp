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
class  EdgeWeightedDigraph//加权有向图
{
private:
	   int V=0;//顶点总数
	   int E=0;//边总数；
	   Bag<DirectedEdge>*adj;//邻接表
	   map<string, int>name;
	   int counts = 0;
public: 
	EdgeWeightedDigraph(int V):V(V),E(0)
    {
	adj = new Bag<DirectedEdge>[V];
    }
	EdgeWeightedDigraph(ifstream& in)//输入流直接获取地图信息；//需要导入文本文件；
	/*
	* 要先处理边，才能处理图；
	*/
	{
		in >> V >> E;
		adj = new Bag<DirectedEdge>[V];		
		string line;
		while (in.fail() == false)
		{
			int v, w;//起点和终点的对应数字
			string sv, sw;//起点和终点的string表示；
			string rode;
			double x1,y1,x2,y2;//对应一个边的起点和终点；
			in >> sv >> sw >>rode>> x1>>y1>>x2>>y2;//输入起点和终点，以及对应的坐标；
			if ((name.insert(make_pair(sv, ++counts))).second)
				v = counts;//构造数字节点和string名字之间的映射；
			else
			{
				if (name.find(sv) != name.end())
				{
					v = name.find(sv)->second;
					counts--;//计数器回退至原来的位置，防止conuts超过8（8是最大能达到大小）；
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
			double weight = Weight(x1, y1, x2, y2);//计算边的权重
			string building;
			string barrier;
			vector<string>buildings;//放置主要建筑
			vector<string>barriers;//放置主要障碍物
			getline(in, line);//为了换行准备的工作，从当前读取数据的一行跳转到下一string行；
			if (getline(in, line))//输入主要建筑
			{
				istringstream sin(line);
				while (sin >> building)
					buildings.push_back(building);
			}
			if (getline(in, line))//输入障碍物；
			{
				istringstream sin(line);
				while (sin >> barrier)
					barriers.push_back(barrier);
			}
			DirectedEdge temp(v, w, weight,rode, buildings, barriers);
			adj[v].add(temp);//放入边；
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
	double Weight(double x1, double y1, double x2, double y2)//以两点之间的直线距离作为权重；
	{
		double tempx = (x1 - x2) * (x1 - x2);
		double tempy = (y1 - y2) * (y1 - y2);
		return pow(tempx + tempy, 0.5);
	}
	pair<int, int>query(string s, string e)
	{
		auto iterv = name.find(s);//获得起点的键值对指针；
		auto iterw = name.find(e);//获得终点的键值对指针；
		if (iterv != name.end() && iterw != name.end())
			return make_pair(iterv->second, iterw->second);
		else//输错了可以选择重来一遍或者直接退出；
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
	string findKey(int value)//找实值对应的键值，以便输出地点名称；
	{
		for (auto it = name.begin(); it != name.end(); it++)
			if (it->second == value)
				return it->first;
	}
};