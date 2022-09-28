
#pragma once

#include<iostream>
#include<vector>
using namespace std;

//ָ����С��
template<typename T>
class Less
{
public:
	bool operator()(const T& a, const T& b)const
	{
		return a < b;
	}
};

//ָ������
template<typename T>
class Greater
{
public:
	bool operator()(const T& a, const T& b)const
	{
		return a > b;
	}
};

//�ѣ�Ĭ����С��less����
template<class T, class Compare = Less<T> >
class Heap
{
private:
	int lastIndex;		//�����±꣬��1��ʼ����
	Compare cmp;		//�����࣬�ж����ѻ�����С��
	vector<T> vec_heap;
public:
	Heap() :lastIndex(1)
	{
		vec_heap.push_back(T());
	}
	~Heap() {};
	//�Ѳ���Ԫ��
	void push(T value)
	{
		vec_heap.push_back(value);		//�Ȳ���β��
		int curIndex = lastIndex;	//��ȡ��ǰ�±�
		//����Ԫ���ϸ�
		while (curIndex / 2)
		{
			if (cmp(vec_heap[curIndex], vec_heap[curIndex / 2]))  //cmp�����Ƚ�ȷ������С�ѻ�������
			{
				//��Ҫ�ϸ���˵������Ԫ�رȸ��ڵ���󣨸�С��
				swap(vec_heap[curIndex], vec_heap[curIndex / 2]);
				curIndex /= 2;
			}
			else
				break;

		}
		lastIndex++;
	}
	//��ȡ��������Ԫ��(�±��1��ʼ����-=1)
	int size() { return lastIndex - 1; };

	//��ȡ�Ѷ�Ԫ�أ�ez��
	T top() { return empty() ? T() : vec_heap[1]; };

	//�ж��Ƿ�նѣ���.����
	bool empty() { return vec_heap.size() <= 1; }
	//ɾ���Ѷ�Ԫ��
	T pop()
	{
		if (lastIndex <= 1)
			return T();
		int curIndex = 1;
		T res = vec_heap[1];
		vec_heap[1] = vec_heap[lastIndex - 1];	//��֤��ȫ�������ṹ�������һ��Ԫ���Ƶ��Ѷ���Ȼ��ִ���³�����
		vec_heap.pop_back();
		lastIndex--;
		//�³�����
		while (curIndex * 2 <= lastIndex - 1)   //��ҪԽ��
		{
			int child = curIndex * 2;//����� +1���Ҷ���
			if (child + 1 <= lastIndex - 1 && cmp(vec_heap[child + 1], vec_heap[child]))  //���ӽڵ����ֵ�滻��������С�Ѿ��������ӽڵ�����С���Ǹ��͸��ڵ�Ƚ�
			{
				child++;	//���ӽڵ��С������
			}
			if (cmp(vec_heap[child], vec_heap[curIndex]))  //�ӽڵ��Ƿ�ȸ��ڵ���󣨸�С��
			{
				swap(vec_heap[child], vec_heap[curIndex]);
			}
			else
				break;
			curIndex = child;
		}
		return res;	//����ɾ���Ѷ�Ԫ��
	}

};
