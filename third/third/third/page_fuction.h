#pragma once
#include<iostream>
#include<string>
#include<graphics.h>
#include<vector>
#include<queue>
#include<algorithm>
#include<conio.h>
#include"heap.h"
#include<fstream>

#define maxn 10001

std::vector<std::pair<int, int>> vec_vis_vertex;
std::vector<std::pair<int, std::pair<int, int>>> vec_vis_edge;

struct Vertex
{
	int val;
	int cost;
	Vertex* next;
	Vertex(int v = -1, int c = 0, Vertex* n = nullptr) :
		val(v), cost(c), next(n) {};
};

vector<Vertex*> vec_vertex_head, vec_vertex_tail;

int vis[maxn] = {0};
int dist[maxn];
int path[maxn];
string f1 = "1.txt";
string f2 = "2.txt";
string f3 = "3.txt";

void Dijkstra()
{
	int size = vec_vis_vertex.size();

	char str1[10], str2[10];
	InputBox(str1, 20, "起始点");
	InputBox(str2, 20, "终止点");
	int strt = atoi(str1);
	int nd = atoi(str2);

	if (strt > size - 1 || nd > size - 1 || strt < 0 || nd < 0 || strt == nd)
	{
		HWND MBX = GetHWnd();
		//弹出窗口，提示用户操作
		int waring = MessageBox(MBX, "错误输入！！！", "提示", MB_OK);
		if (waring == IDOK)
		{
			return;
		}
	}

	for (int i = 0; i <= size; i++)
	{
		dist[i] = INT32_MAX;
		path[i] = i;
		vis[i] = 0;
	}
	
	Heap<pair<int, int>, Less<pair<int, int>>> list_cost_val;

	dist[strt] = 0;
	list_cost_val.push(pair<int, int>(0,strt));
	while (!list_cost_val.empty())
	{
		int e_cost, e_val;
		e_cost = list_cost_val.top().first;
		e_val = list_cost_val.top().second;
		list_cost_val.pop();
		if (vis[e_val] == 1)
			continue;
		else
			vis[e_val] = 1;

		Vertex* p = vec_vertex_head[e_val];
		while (p != nullptr)
		{
			if (p->cost + dist[e_val] < dist[p->val])
			{
				dist[p->val] = p->cost + dist[e_val];
				path[p->val] = e_val;
				list_cost_val.push(pair<int, int>(dist[p->val], p->val));
			}
			p = p->next;
		}
	}

	setfillcolor(BLUE);
	setlinestyle(PS_SOLID, 5);
	setlinecolor(RED);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(35, 0, "汉仪行楷简");

	if (dist[nd] != INT32_MAX)
	{
		outtextxy(0, 0, ("总路程：" + to_string(dist[nd])).c_str());
		outtextxy(1280 - textwidth(("起点：" + to_string(strt) + "   终点：" + to_string(nd) + "   ").c_str()),
			720 - textheight(("起点：" + to_string(strt) + "   终点：" + to_string(nd) + "   ").c_str()),
			("起点：" + to_string(strt) + "   终点：" + to_string(nd) + "   ").c_str());

		while (path[nd] != nd)
		{
			line(vec_vis_vertex[nd].first, vec_vis_vertex[nd].second,
				vec_vis_vertex[path[nd]].first, vec_vis_vertex[path[nd]].second);

			nd = path[nd];
		}
	}
	else
	{
		outtextxy(0, 0, "起点与终点不连通");
		outtextxy(1280 - textwidth(("起点：" + to_string(strt) + "   终点：" + to_string(nd) + "   ").c_str()),
			720 - textheight(("起点：" + to_string(strt) + "   终点：" + to_string(nd) + "   ").c_str()),
			("起点：" + to_string(strt) + "   终点：" + to_string(nd) + "   ").c_str());
	}
}

void file_in()
{
	char str[10];
	InputBox(str, 20, "数据编号（1,3）");
	int tmp = atoi(str);
	ifstream is;
	switch (tmp)
	{
	case 1: is.open("../Data/text/" + f1); break;
	case 2: is.open("../Data/text/" + f2); break;
	case 3: is.open("../Data/text/" + f3); break;
	default:
		HWND MBX = GetHWnd();
		//弹出窗口，提示用户操作
		int waring = MessageBox(MBX, "错误输入！！！", "提示", MB_OK);
		if (waring == IDOK)
		{
			return;
		}
		break;
	}

	int n, m;
	is >> n >> m;

	for (int i = 0; i <= n - 1; i++)
	{
		int x;
		int y;

		is >> x >> y;

		vec_vis_vertex.push_back(pair<int, int>(x, y));
		vec_vertex_head.push_back(nullptr);
		vec_vertex_tail.push_back(nullptr);
	}

	for (int i = 0; i <= m - 1; i++)
	{
		int x;
		int y;
		int cost;

		is >> x >> y >> cost;


		vec_vis_edge.push_back(pair<int, pair<int, int>>(cost, pair<int, int>(x, y)));

		Vertex* tmp = vec_vertex_head[x];
		if (tmp == nullptr)
		{
			tmp = new Vertex(y, cost);
			vec_vertex_head[x] = tmp;
			vec_vertex_tail[x] = tmp;
		}
		else
		{
			tmp = new Vertex(y, cost);
			vec_vertex_tail[x]->next = tmp;
			vec_vertex_tail[x] = tmp;
		}

		tmp = vec_vertex_head[y];
		if (tmp == nullptr)
		{
			tmp = new Vertex(x, cost);
			vec_vertex_head[y] = tmp;
			vec_vertex_tail[y] = tmp;
		}
		else
		{
			tmp = new Vertex(x, cost);
			vec_vertex_tail[y]->next = tmp;
			vec_vertex_tail[y] = tmp;
		}
	}

	is.close();
}