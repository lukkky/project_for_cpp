#pragma once
#include<vector>
#include<iostream>
#include<assert.h>
using namespace std;//使用二叉堆的优先索引队列
template <typename Key>
class IndexMinPQ//有Comparable之后，可以自定义比较方式；
{
private:
	int maxN;//预定的最大个数
	int n;//队列元素个数
	int*pq;//记录每个元素对应的位置；
	int*qp;//记录每一个位置对应哪个元素；
	Key*keys;//record the key of the elements;
	void validateIndex(int i)
	{
		if (i < 0)
		{
			cerr << "the index is negative." << endl;
			abort();
		}
	}
	void exch(int i, int j)
	{
		int swap = pq[i];
		pq[i] = pq[j];
		pq[j] = swap;
		qp[pq[i]] = i;
		qp[pq[j]] = j;
	}
	void swim(int k)
	{
		while (k > 1 && greater(k / 2, k))//子节点和父节点比较，父节点较大则子节点和父节点调换位置；
		{
			exch(k, k / 2);
			k = k / 2;
		}
	}
	void sink(int k)
	{
		while (2 * k <= n)
		{
			int j = 2 * k;
			if(j<n&&greater(j,j+1))j++;//选择子节点中较小的那一个
				if(!greater(k,j))break;//父节点比子节点小，不用改变；否则进行交换；
				exch(k,j);
				k=j;
		}
	}
	bool greater(int i, int j)//比较实值大小，用于排序；
	{
		return keys[pq[i]]>keys[pq[j]];
	}
public:
	~IndexMinPQ()
	{
		delete[]keys;
		delete[]pq;
		delete[]qp;
	}
	IndexMinPQ() {};
	IndexMinPQ(int nnMax) :maxN(nnMax)
	{
		if (nnMax < 0)//输入的预估个数最大值检测；
		{
			cerr << "invalidate max number!" << endl;
			return ;
		}
		keys = new Key[maxN + 1];
		pq = new int[maxN + 1];
		qp = new int[maxN + 1];
		for (int i = 0; i < maxN; i++)//将每个索引对应的位置初始化为-1，表示还没有对应的元素被添加；
			qp[i]=-1;
		for (int i = 0; i < maxN; i++)
			pq[i] = -1;
	}
	bool isEmpty()//队列是否为空
	{
		return n == 0;
	}
	bool contains(int i)//队列是否包含索引为i的元素；
	{
		validateIndex(i);//判断i是否合法；
		return pq[i]!=-1;
	}
	 int size()//返回队列的大小
	{
		return n;
	}
	 void insert(int i, Key key)
	 {
		 validateIndex(i);
		 if (contains(i))
		 {
			 cerr << "index has already in the PQ." << endl;
			 return;
		 }
		 n++;
		 qp[i] = n;
		 pq[n] = i;
		 keys[i] = key;
		 swim(n);
	 }
	 int minIndex()
	 {
		 if (n == 0)
		 {
			 cerr << "PQ underflow." << endl;
			 return;
		 }
		 return pq[1];
	 }
	 Key minKey()//返回最小元素的实值
	 {
		 if (n == 0)
		 {
			 cerr << "Pq underflow." << endl;
			 return;
		 }
		 return keys[pq[1]];
	 }
	 int delMin()//删除最小元素,并且返回其索引；
	 {
		 if (n == 0)
		 {
			 cerr << "PQ underflow." << endl;
			 return -1;
		 }
		 int min = pq[1];//暂存最小元素的索引；
		 exch(1, n--);//第一个元素（最小的元素）和最后一个元素交换位置；
		 sink(1);//对队列重新排序；
		 assert(min == pq[n + 1]);//确保第一个元素和最后一个元素交换成功；
		 qp[min] = -1;//删除元素；
		 keys[min] = NULL;//实值置零；
		 pq[n + 1] = -1;
		 return min;
	 }
	 Key keyOf(int i)//返回索引为i的键值；
	 {
		 validateIndex(i);
		 if (!contains(i))
		 {
			 cerr << "index is not in the PQ." << endl;
			 return;
		 }
		 return keys[i];
	 }
	 void changeKey(int i, Key key)//改变索引为i的实值；
	 {
		 validateIndex(i);
		 if (!contains(i))
		 {
			 cerr << "index is not in the PQ." << endl;
			 return;
		 }
		 keys[i] = key;
		 //实值可能增加也可能减少，所以swim和sink都写入代码；
		 swim(qp[i]);
		 sink(qp[i]); 
	 }
	 void Delete(int i)//删除i对应的元素；
	 {
		 validateIndex(i);
		 if (!contains(i))
		 {
			 cerr << "index is not in the PQ." << endl;
			 return;
		 }
		 int index = qp[i];
		 exch(index, n--);
		 swim(index);
		 sink(index);
		 keys[i] = nullptr;
		 qp[i] = -1;
	 }
};