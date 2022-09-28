#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<Windows.h>
#include <Ws2tcpip.h>
#include<list>
#include<iostream>
#include<string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int len;

struct sck
{
	SOCKET _socket;
	sockaddr_in _sockaddr_in;
	WSAEVENT _wsaevent;
}sk;

list<sck> connectList;


void sendMsg(int sender, char* msg, int length)
{
	char buf[1024] = { 0 };
	sprintf(buf, "%s", msg);

	for (auto it = connectList.begin(); it != connectList.end(); it++)
	{
		if (sender != it->_socket)
		{
			send(it->_socket, buf, strlen(buf), 0);
		}
	}
}

DWORD WINAPI thread_ser(LPVOID IpParameter)
{
	SOCKET sk_s = *(SOCKET*)IpParameter;
	while (1)
	{
		for (auto it = connectList.begin(); it != connectList.end(); it++)
		{
			DWORD Index = WSAWaitForMultipleEvents(1, &(it->_wsaevent), FALSE, 10, 0);

			Index -= WSA_WAIT_EVENT_0;

			if (Index == WSA_WAIT_TIMEOUT || Index == WSA_WAIT_FAILED)
			{
				continue;
			}


			else if (Index == 0)
			{
				WSANETWORKEVENTS net_event;
				WSAEnumNetworkEvents(it->_socket, it->_wsaevent, &net_event);

				if (net_event.lNetworkEvents & FD_ACCEPT)
				{
					if (net_event.iErrorCode[FD_ACCEPT_BIT] != 0)
					{
						printf("accept 失败 错误码: %d\n", net_event.iErrorCode[FD_ACCEPT_BIT]);
						continue;
					}
					sck tmp;
					SOCKET conn = accept(sk._socket, (SOCKADDR*)&tmp._sockaddr_in, &len);

					if (conn != INVALID_SOCKET)
					{
						tmp._socket = conn;
						WSAEVENT newE = WSACreateEvent();
						WSAEventSelect(tmp._socket, newE, FD_CLOSE | FD_READ | FD_WRITE);
						tmp._wsaevent = newE;


						connectList.push_back(tmp);
						printf("游客 %d 进入房间\n", (int)conn);

						char buf[1024] = "[一梦]欢迎游客（IP：";
						strcat(buf, inet_ntoa(tmp._sockaddr_in.sin_addr));
						strcat(buf, ")进入聊天室");

						for (auto it = connectList.begin(); it != connectList.end(); it++)
						{
							if (sk._socket != it->_socket)
							{
								send(it->_socket, buf, strlen(buf), 0);
							}
						}
					}


				}

				else if (net_event.lNetworkEvents & FD_CLOSE)
				{
					cout << "#游客（IP：" << inet_ntoa(it->_sockaddr_in.sin_addr) << ")退出了聊天室,当前连接数：" << connectList.size() - 2 << endl;
					closesocket(it->_socket);
					WSACloseEvent(it->_wsaevent);

					char buf[1024] = "[一梦]（IP：";
					strcat(buf, inet_ntoa(it->_sockaddr_in.sin_addr));
					strcat(buf, ")退出聊天室");
					sendMsg(sk._socket, buf, strlen(buf));


					connectList.erase(it);

					break;

				}

				else if (net_event.lNetworkEvents & FD_READ)
				{
					char buf[1024] = {0}, buf1[1024] = {0};

					for (auto it = connectList.begin(); it != connectList.end(); it++)
					{
						int ret = recv(it->_socket, buf, sizeof(buf), 0);
						if (ret > 0)
						{
							sprintf(buf1, "[#%d]%s", (int)it->_socket, buf);
							cout << buf1 << endl;
							sendMsg(it->_socket, buf1, strlen(buf1));
						}
					}
				}
			}
		}

	}
	return 0;
}






int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		printf("WSASstartup 失败 错误码: %d\n", err);
	}

	sk._socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sk._socket == INVALID_SOCKET)
	{
		printf("socket 失败 错误码: %d\n", WSAGetLastError());
	}


	sk._sockaddr_in.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.124.33", &sk._sockaddr_in.sin_addr.s_addr);
	sk._sockaddr_in.sin_port = htons(27015);

	int iresult = bind(sk._socket, (SOCKADDR*)&sk._sockaddr_in, sizeof(sk._sockaddr_in));
	if (iresult != 0)
	{
		printf("bind 失败 错误码: %d\n", WSAGetLastError());
	}

	WSAEVENT servE = WSACreateEvent();
	WSAEventSelect(sk._socket, servE, FD_ALL_EVENTS);
	sk._wsaevent = servE;

	connectList.push_back(sk);

	listen(sk._socket, 10);
	len = sizeof(sk._sockaddr_in);

	CloseHandle(CreateThread(NULL, 0, thread_ser, (LPVOID)&sk._socket, 0, 0));

	cout << "您的[一梦]聊天服务器已开启" << endl;

	while (1)
	{

		char contentBuf[1024] = { 0 };
		char sendBuf[1024] = { 0 };
		cin.getline(contentBuf, sizeof(contentBuf));
		sprintf(sendBuf, "[一梦]%s", contentBuf);

		for (auto it = connectList.begin(); it != connectList.end(); it++)
		{
			if (sk._socket != it->_socket)
			{
				send(it->_socket, sendBuf, strlen(sendBuf), 0);
			}
		}

	}

	closesocket(sk._socket);

	WSACleanup();

	return 0;
}