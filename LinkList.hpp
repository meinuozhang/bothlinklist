#include <assert.h>
#include<iostream>
using namespace std;
template<typename T>
class LinkNode
{
  template<typename T>
  friend class LinkList;
public:
	LinkNode(const T &x)
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}
private:
	LinkNode<T>* _next;
	LinkNode<T>* _prev;
	T _data;
};
template<typename T>
class LinkList
{
public:
	LinkList()
	:_head(NULL)
	,_tail(NULL)
	{}
	~LinkList()
	{//在这里删除节点时一定要避免出现内存的泄露
		//（1）避免丢掉链表中的节点指针丢失
		LinkNode<T>* begin = _head;
		while (begin)
		{
			LinkNode<T>* del= begin;
			begin = begin->_next;
			delete del;
		}
	}

	void PushBack(const T &x)
	{
		//没有节点
		//一个节点及一个以上节点
		if (_head == NULL)
		{
			_head = new LinkNode<T>(x);
			_tail = _head;
		}
		else
		{
			LinkNode<T> *tmp = new LinkNode<T> (x);
			_tail->_next = tmp;
			tmp->_prev = _tail;
			_tail = tmp;
		}
	}
	
	LinkNode<T>* Find(const T &x)
	{
		//x 为头节点
		//x为尾节点
		//x为中间节点
		LinkNode<T> *begin = _head;
		while (begin)
		{
			if (begin->_data == x)
			{
				return begin;
			}
			begin = begin->_next;
		}
		return NULL;
		/*if (_head == NULL)
		{
			return;
		}
		else if (_head == _tail)
		{
			
			if (begin->_data == x)
			{
				return begin;
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			while (begin)
			{
				if (begin->_data == x)
				{
					return begin;
				}
				begin = begin->_next;
			}
			return NULL;
		}
		*/
	}
	void Erase(LinkNode<T>* n)
	{
		assert(n);
		if (_head == NULL)
		{
			return;
		}
		else if (_head == _tail && _head == n)
		{
			delete n;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			LinkNode<T> *del = NULL;

			if (_head == n)
			{
				del = _head;
				_head = _head->_next;
				_head->_prev = NULL;
			}
			else if (_tail == n)
			{
				del = _tail;
				_tail = _tail->_prev;
				_tail->_next = NULL;
			}
			else
			{
				LinkNode<T> *prev = n->_prev;
				LinkNode<T> *next = n->_next;
				next->_prev = prev;
				prev->_next = next;

			}
			delete n;
		}
	}
	void Print()
	{
		LinkNode<T> *begin = _head;
		while (begin)
		{
			cout << begin->_data << "->";
			begin = begin->_next;
		}
		cout << NULL << endl;
	}
private:
	LinkNode<T>* _head;
	LinkNode<T>* _tail;
};
void Test()
{
	LinkList<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	l.Print();
	LinkNode<int>* ret = l.Find(1);
	l.Erase(ret);

	ret = l.Find(5);
	l.Erase(ret);

	ret = l.Find(3);
	l.Erase(ret);

	l.Print();
}