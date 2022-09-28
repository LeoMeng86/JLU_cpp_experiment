#define _CRT_SECURE_NO_WARNINGS
#include<winsock2.h>//winsock2的头文件
#include <Ws2tcpip.h>
#include<iostream>
#include<cstring>
#include<string>

using  namespace std;

#pragma comment(lib, "ws2_32.lib")



DWORD WINAPI recv_thread(LPVOID IpParameter)
{
	SOCKET sk = *(SOCKET*)IpParameter;

	while (1)
	{
		char buf[1024] = { 0 };
		int rec = recv(sk, buf, sizeof(buf), 0);
		if (rec > 0)
		{
			cout << buf << endl;
		}
		else if (rec < 0)
		{
			cout << "与服务器断开连接" << endl;
			break;
		}
	}

	return 0;
}

int  main()
{
	SOCKET sk;
	sockaddr_in ad_ser;
	sockaddr_in ad_cli;


	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		printf("WSASstartup 失败 错误码: %d\n", err);
	}


	sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sk == INVALID_SOCKET)
	{
		printf("socket 失败 错误码: %d\n", WSAGetLastError());
	}

	
	ad_ser.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.124.33", &ad_ser.sin_addr.s_addr);
	ad_ser.sin_port = htons(27015);

	ad_cli.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &ad_cli.sin_addr.s_addr);
	ad_cli.sin_port = htons(27015);

	int len = sizeof(sockaddr_in);
	if (connect(sk, (SOCKADDR*)&ad_ser, len) == SOCKET_ERROR)
	{
		printf("connect 失败 错误码: %d\n", WSAGetLastError());
		return 0;
	}
	
	CloseHandle(CreateThread(NULL, 0, recv_thread, (LPVOID)&sk, 0, 0));



	while (1)
	{
		char buf[1024] = { 0 };
		scanf("%s", buf);
		if (strcmp(buf, "quit") == 0)
		{
			break;
		}
		send(sk, buf, sizeof(buf), 0);
	}



	//4.关闭监听套接字
	closesocket(sk);

	//清理winsock2的环境
	WSACleanup();


	return 0;
}
