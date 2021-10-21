#pragma once
#include<vector>
#include<iostream>
#include<assert.h>
using namespace std;//ʹ�ö���ѵ�������������
template <typename Key>
class IndexMinPQ//��Comparable֮�󣬿����Զ���ȽϷ�ʽ��
{
private:
	int maxN;//Ԥ����������
	int n;//����Ԫ�ظ���
	int*pq;//��¼ÿ��Ԫ�ض�Ӧ��λ�ã�
	int*qp;//��¼ÿһ��λ�ö�Ӧ�ĸ�Ԫ�أ�
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
		while (k > 1 && greater(k / 2, k))//�ӽڵ�͸��ڵ�Ƚϣ����ڵ�ϴ����ӽڵ�͸��ڵ����λ�ã�
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
			if(j<n&&greater(j,j+1))j++;//ѡ���ӽڵ��н�С����һ��
				if(!greater(k,j))break;//���ڵ���ӽڵ�С�����øı䣻������н�����
				exch(k,j);
				k=j;
		}
	}
	bool greater(int i, int j)//�Ƚ�ʵֵ��С����������
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
		if (nnMax < 0)//�����Ԥ���������ֵ��⣻
		{
			cerr << "invalidate max number!" << endl;
			return ;
		}
		keys = new Key[maxN + 1];
		pq = new int[maxN + 1];
		qp = new int[maxN + 1];
		for (int i = 0; i < maxN; i++)//��ÿ��������Ӧ��λ�ó�ʼ��Ϊ-1����ʾ��û�ж�Ӧ��Ԫ�ر���ӣ�
			qp[i]=-1;
		for (int i = 0; i < maxN; i++)
			pq[i] = -1;
	}
	bool isEmpty()//�����Ƿ�Ϊ��
	{
		return n == 0;
	}
	bool contains(int i)//�����Ƿ��������Ϊi��Ԫ�أ�
	{
		validateIndex(i);//�ж�i�Ƿ�Ϸ���
		return pq[i]!=-1;
	}
	 int size()//���ض��еĴ�С
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
	 Key minKey()//������СԪ�ص�ʵֵ
	 {
		 if (n == 0)
		 {
			 cerr << "Pq underflow." << endl;
			 return;
		 }
		 return keys[pq[1]];
	 }
	 int delMin()//ɾ����СԪ��,���ҷ�����������
	 {
		 if (n == 0)
		 {
			 cerr << "PQ underflow." << endl;
			 return -1;
		 }
		 int min = pq[1];//�ݴ���СԪ�ص�������
		 exch(1, n--);//��һ��Ԫ�أ���С��Ԫ�أ������һ��Ԫ�ؽ���λ�ã�
		 sink(1);//�Զ�����������
		 assert(min == pq[n + 1]);//ȷ����һ��Ԫ�غ����һ��Ԫ�ؽ����ɹ���
		 qp[min] = -1;//ɾ��Ԫ�أ�
		 keys[min] = NULL;//ʵֵ���㣻
		 pq[n + 1] = -1;
		 return min;
	 }
	 Key keyOf(int i)//��������Ϊi�ļ�ֵ��
	 {
		 validateIndex(i);
		 if (!contains(i))
		 {
			 cerr << "index is not in the PQ." << endl;
			 return;
		 }
		 return keys[i];
	 }
	 void changeKey(int i, Key key)//�ı�����Ϊi��ʵֵ��
	 {
		 validateIndex(i);
		 if (!contains(i))
		 {
			 cerr << "index is not in the PQ." << endl;
			 return;
		 }
		 keys[i] = key;
		 //ʵֵ��������Ҳ���ܼ��٣�����swim��sink��д����룻
		 swim(qp[i]);
		 sink(qp[i]); 
	 }
	 void Delete(int i)//ɾ��i��Ӧ��Ԫ�أ�
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