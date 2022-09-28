
#pragma once

#include<iostream>
#include<vector>
using namespace std;

//指定最小堆
template<typename T>
class Less
{
public:
	bool operator()(const T& a, const T& b)const
	{
		return a < b;
	}
};

//指定最大堆
template<typename T>
class Greater
{
public:
	bool operator()(const T& a, const T& b)const
	{
		return a > b;
	}
};

//堆，默认最小堆less排序
template<class T, class Compare = Less<T> >
class Heap
{
private:
	int lastIndex;		//数组下标，从1开始计数
	Compare cmp;		//排序类，判断最大堆还是最小堆
	vector<T> vec_heap;
public:
	Heap() :lastIndex(1)
	{
		vec_heap.push_back(T());
	}
	~Heap() {};
	//堆插入元素
	void push(T value)
	{
		vec_heap.push_back(value);		//先插入尾部
		int curIndex = lastIndex;	//获取当前下标
		//插入元素上浮
		while (curIndex / 2)
		{
			if (cmp(vec_heap[curIndex], vec_heap[curIndex / 2]))  //cmp类来比较确定是最小堆还是最大堆
			{
				//需要上浮，说明插入元素比父节点更大（更小）
				swap(vec_heap[curIndex], vec_heap[curIndex / 2]);
				curIndex /= 2;
			}
			else
				break;

		}
		lastIndex++;
	}
	//获取堆中所有元素(下标从1开始所以-=1)
	int size() { return lastIndex - 1; };

	//获取堆顶元素（ez）
	T top() { return empty() ? T() : vec_heap[1]; };

	//判断是否空堆（—.—）
	bool empty() { return vec_heap.size() <= 1; }
	//删除堆顶元素
	T pop()
	{
		if (lastIndex <= 1)
			return T();
		int curIndex = 1;
		T res = vec_heap[1];
		vec_heap[1] = vec_heap[lastIndex - 1];	//保证完全二叉树结构，把最后一个元素移到堆顶，然后执行下沉操作
		vec_heap.pop_back();
		lastIndex--;
		//下沉操作
		while (curIndex * 2 <= lastIndex - 1)   //不要越界
		{
			int child = curIndex * 2;//左儿子 +1变右儿子
			if (child + 1 <= lastIndex - 1 && cmp(vec_heap[child + 1], vec_heap[child]))  //找子节点合适值替换，比如最小堆就找两个子节点中最小的那个和父节点比较
			{
				child++;	//右子节点更小（更大）
			}
			if (cmp(vec_heap[child], vec_heap[curIndex]))  //子节点是否比父节点更大（更小）
			{
				swap(vec_heap[child], vec_heap[curIndex]);
			}
			else
				break;
			curIndex = child;
		}
		return res;	//返回删除堆顶元素
	}

};
