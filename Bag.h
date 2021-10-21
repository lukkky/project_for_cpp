#pragma once
template <typename Item>
struct Node//包中元素的类型；
{
	Item item;
	Node<Item>* next;//下一个节点的地址
	Node() {};
};
template <class type>
class Bag
{
private:
	Node<type>* first;//头节点
		int n;//节点数
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
		/*返回头节点*/
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
	type& operator[](int index)//运算符重载,返回Bag[index];
	{
		int count = 0;//计数，确保链表跳转到正确的节点处；
		Node<type>*begin = first;
		while ((*begin).next!=nullptr && count < index)
		{
			count++;
			begin = (*begin).next;
		}
		if ((*begin).next==nullptr&&count!=index)//已经到了最后一个节点，但是要求的位置还是没有达到；
		{
			cerr << "wrong subindex!" << endl;
			abort(); 
		}
		else
		{
			if ((*begin).next == nullptr && count == index)//对应节点的包里面只有一条边的情况；
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
	~Bag()//销毁链表，或许这里不处理就会导致释放内存失败，应该是吧，delete只能处理连续的内存；
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
