#pragma once
#include<vector>
#include<graphics.h>
#include<conio.h>
#include"heap.h"
#include"page_fuction.h"
#include<string>

void init()
{
	initgraph(1500, 720);
	setorigin(220, 0);
	IMAGE img;
	loadimage(&img, "../Data/picture/background.jpg");
	putimage(-220, 0, &img);
	setfillcolor(YELLOW);
	setlinestyle(PS_SOLID, 3);
	setlinecolor(BLUE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(35, 0, "�����п���");
	int left = -200, right = -20, height = 60, bet = 60, top = 100;
	fillroundrect(left, top, right, top + height, 15, 15);
	fillroundrect(left, top + bet + height, right, top + height * 2 + bet, 15, 15);
	fillroundrect(left, top + bet * 2 + height * 2, right, top + height * 3 + bet * 2, 15, 15);
	fillroundrect(left, top + bet * 3 + height * 3, right, top + height * 4 + bet * 3, 15, 15);
	fillroundrect(left, top + bet * 4 + height * 4, right, top + height * 5 + bet * 4, 15, 15);

	outtextxy((right - left - textwidth("�½��ص�")) / 2 + left, (height - textheight("�½��ص�")) / 2 + top, "�½��ص�");
	outtextxy((right - left - textwidth("�½�·��")) / 2 + left, (height - textheight("�½�·��")) / 2 + top + bet + height, "�½�·��");
	outtextxy((right - left - textwidth("�ļ�����")) / 2 + left, (height - textheight("�ļ�����")) / 2 + top + bet * 2 + height * 2, "�ļ�����");
	outtextxy((right - left - textwidth("Dijkstra")) / 2 + left, (height - textheight("Dijkstra")) / 2 + top + bet * 3 + height * 3, "Dijkstra");
	outtextxy((right - left - textwidth("��    ��")) / 2 + left, (height - textheight("��    ��")) / 2 + top + bet * 4 + height * 4, "��    ��");

}



void add_vertex()
{
	char str1[10], str2[10];
	InputBox(str1, 20, "x����(0,1280)");
	InputBox(str2, 20, "y����(0,720)");
	int x = atoi(str1);
	int y = atoi(str2);

	if (x > 1280 || y > 720)
	{
		HWND MBX = GetHWnd();
		//�������ڣ���ʾ�û�����
		int waring = MessageBox(MBX, "�������룡����", "��ʾ", MB_OK);
		if (waring == IDOK)
		{
			return;
		}
	}

	vec_vis_vertex.push_back(pair<int, int>(x, y));
	vec_vertex_head.push_back(nullptr);
	vec_vertex_tail.push_back(nullptr);
}


void add_edge()
{
	int size = vec_vis_vertex.size();
	char str1[10], str2[10], str3[10];
	InputBox(str1, 20, "��һ����(���)");
	InputBox(str2, 20, "�ڶ�����(���)");
	InputBox(str3, 20, "��Ȩ");
	int x = atoi(str1);
	int y = atoi(str2);
	int cost = atoi(str3);

	if (x > size - 1 || y > size - 1 || x < 0 || y < 0 || x == y || cost <= 0)
	{
		HWND MBX = GetHWnd();
		//�������ڣ���ʾ�û�����
		int waring = MessageBox(MBX, "�������룡����", "��ʾ", MB_OK);
		if (waring == IDOK)
		{
			return;
		}
	}

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



void showgraph()
{
	cleardevice();
	setorigin(220, 0);
	IMAGE img;
	loadimage(&img, "../Data/picture/background.jpg");
	putimage(-220, 0, &img);
	setfillcolor(YELLOW);
	setlinestyle(PS_SOLID, 3);
	setlinecolor(BLUE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(35, 0, "�����п���");
	int left = -200, right = -20, height = 60, bet = 60, top = 100;

	fillroundrect(left, top, right, top + height, 15, 15);
	fillroundrect(left, top + bet + height, right, top + height * 2 + bet, 15, 15);
	fillroundrect(left, top + bet * 2 + height * 2, right, top + height * 3 + bet * 2, 15, 15);
	fillroundrect(left, top + bet * 3 + height * 3, right, top + height * 4 + bet * 3, 15, 15);
	fillroundrect(left, top + bet * 4 + height * 4, right, top + height * 5 + bet * 4, 15, 15);

	outtextxy((right - left - textwidth("�½��ص�")) / 2 + left, (height - textheight("�½��ص�")) / 2 + top, "�½��ص�");
	outtextxy((right - left - textwidth("�½�·��")) / 2 + left, (height - textheight("�½�·��")) / 2 + top + bet + height, "�½�·��");
	outtextxy((right - left - textwidth("�ļ�����")) / 2 + left, (height - textheight("�ļ�����")) / 2 + top + bet * 2 + height * 2, "�ļ�����");
	outtextxy((right - left - textwidth("Dijkstra")) / 2 + left, (height - textheight("Dijkstra")) / 2 + top + bet * 3 + height * 3, "Dijkstra");
	outtextxy((right - left - textwidth("��    ��")) / 2 + left, (height - textheight("��    ��")) / 2 + top + bet * 4 + height * 4, "��    ��");

	setfillcolor(BLUE);

	int len = vec_vis_vertex.size();

	for (auto it = vec_vis_edge.begin(); it != vec_vis_edge.end(); it++)
	{
		line(vec_vis_vertex[it->second.first].first, vec_vis_vertex[it->second.first].second,
			vec_vis_vertex[it->second.second].first, vec_vis_vertex[it->second.second].second);
		string tmp = std::to_string(it->first);
		outtextxy((vec_vis_vertex[it->second.first].first + vec_vis_vertex[it->second.second].first) / 2,
			(vec_vis_vertex[it->second.first].second + vec_vis_vertex[it->second.second].second) / 2, tmp.c_str());
	}

	settextcolor(YELLOW);
	settextstyle(35, 0, "�����п���");
	for (int i = 0; i <= len - 1; i++)
	{
		solidcircle(vec_vis_vertex[i].first, vec_vis_vertex[i].second, 20);
		string tmp = to_string(i);
		outtextxy((40 - textwidth(tmp.c_str())) / 2 + vec_vis_vertex[i].first - 20, (40 - textheight(tmp.c_str())) / 2 + vec_vis_vertex[i].second - 20, tmp.c_str());
	}
	settextcolor(BLACK);
	settextstyle(35, 0, "�����п���");
}



void Content()
{
loop:
	while (1)
	{
		if (MouseHit()) {

			//�������
			MOUSEMSG msg;
			msg = GetMouseMsg();

			//��Ϣ�ַ�
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//�����ص�
				int left = 20, right = 200, height = 60, bet = 60, top = 100;

				if (msg.x < right && msg.x>left && msg.y > top + bet * 0 + height * 0 && msg.y < top + height * 1 + bet * 0)
				{
					add_vertex();
					showgraph();
					goto loop;
				}

				//����·��
				if (msg.x < right && msg.x>left && msg.y > top + bet * 1 + height * 1 && msg.y < top + height * 2 + bet * 1)
				{
					add_edge();
					showgraph();
					goto loop;
				}

				//�ļ�����
				if (msg.x < right && msg.x>left && msg.y > top + bet * 2 + height * 2 && msg.y < top + height * 3 + bet * 2)
				{
					file_in();
					showgraph();
					goto loop;
				}

				//Dijkstra
				if (msg.x < right && msg.x>left && msg.y > top + bet * 3 + height * 3 && msg.y < top + height * 4 + bet * 3)
				{
					showgraph();
					Dijkstra();
					goto loop;
				}

				//�˳�
				if (msg.x < right && msg.x>left && msg.y > top + bet * 4 + height * 4 && msg.y < top + height * 5 + bet * 4)
				{
					HWND MBX = GetHWnd();
					//�������ڣ���ʾ�û�����
					int waring = MessageBox(MBX, "�Ƿ��˳�����", "��ʾ", MB_OKCANCEL);
					if (waring == IDOK)
					{
						return;
					}
					else
						goto loop;
				}
			}
		}
	}/*ѭ�����*/
}