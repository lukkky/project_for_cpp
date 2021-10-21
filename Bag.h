#pragma once
template <typename Item>
struct Node//����Ԫ�ص����ͣ�
{
	Item item;
	Node<Item>* next;//��һ���ڵ�ĵ�ַ
	Node() {};
};
template <class type>
class Bag
{
private:
	Node<type>* first;//ͷ�ڵ�
		int n;//�ڵ���
public:
	Bag()
	{
		first = nullptr;
		n = 0;
	}
	bool isEmpty()
	{
		return first == nullptr;
	}
	auto begin()->Node<type>*  
		/*����ͷ�ڵ�*/
	{
		return first;
	}
	int size()
	{
		return n;
	}
	void add(type item)
	{   
		if (n == 0)
		{
			first = new Node<type>();
			(*first).item = item;
			(*first).next = nullptr;
			n++;
		}
		else
		{
			Node<type>* oldfirst =first;
			first = new Node<type>();
			(*first).item = item;
			(*first).next = oldfirst;
			n++;
		}
	}
	type& operator[](int index)//���������,����Bag[index];
	{
		int count = 0;//������ȷ��������ת����ȷ�Ľڵ㴦��
		Node<type>*begin = first;
		while ((*begin).next!=nullptr && count < index)
		{
			count++;
			begin = (*begin).next;
		}
		if ((*begin).next==nullptr&&count!=index)//�Ѿ��������һ���ڵ㣬����Ҫ���λ�û���û�дﵽ��
		{
			cerr << "wrong subindex!" << endl;
			abort(); 
		}
		else
		{
			if ((*begin).next == nullptr && count == index)//��Ӧ�ڵ�İ�����ֻ��һ���ߵ������
				return (*begin).item;
			else
				if (count == index)
					return (*begin).item;
				else
				{
					cerr << "wrong subindex!" << endl;
					abort();
				}
		}
			
	}
	~Bag()//���������������ﲻ����ͻᵼ���ͷ��ڴ�ʧ�ܣ�Ӧ���ǰɣ�deleteֻ�ܴ����������ڴ棻
	{
		Node<type>* p = first;
		while (first!=nullptr)
		{
			first = (*first).next;
			delete p;
			p = first;
		}
	}
};
