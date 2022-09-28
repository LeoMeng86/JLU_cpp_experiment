#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Table
{
public:
	string tableName;
	int titleCnt = 0;
	vector<string> titleName;
	vector<string> titleType;
	fstream tableAddr;
};

class MyDBMS
{
	vector<Table*> tableList;
public:
	string Cmd;
	string fileprePath;
	bool open;
	MyDBMS();
	~MyDBMS();
	void open_DBMS();
	void close_DBMS();
	void new_DBMS();
	void new_Table();
	void del_Table();
	void ins_Data();
	void del_Data();
	void check_Data();
};

MyDBMS::MyDBMS()
{
	Cmd = "";
	fileprePath = "";
	open = false;
	cout << "欢迎使用一梦数据库管理系统" << endl;
	cout << "请进行操作" << endl;
	cout << "打开数据库：openDatabase" << endl;
	cout << "新建数据库：newDatabase" << endl;
	cout << "关闭数据库：closeDatabase" << endl;
	cout << "新建数据表：newTable" << endl;
	cout << "删除数据库：delTable" << endl;
	cout << "插入数据：insertData" << endl;
	cout << "删除数据：delData" << endl;
	cout << "查询数据：checkData" << endl;
	cout << "退出：exit" << endl;
}

MyDBMS::~MyDBMS()
{
	for (int i = 0; i <= tableList.size() - 1; i++)
	{
		tableList[i]->tableAddr.close();
	}
	tableList.clear();
	Cmd = "";
	fileprePath = "";
}

void MyDBMS::open_DBMS()
{
	cout << "请输入数据库位置：" << endl;
	cout << " >";
	cin >> fileprePath;
	fstream fs;
	fs.open(fileprePath + "\\tableList.txt", ios::in);
	if (!fs.is_open())
	{
		cout << "数据库打开失败" << endl;
		fileprePath = "";
		return;
	}
	open = true;
	int cnt = 0;
	fs >> cnt;
	for (int i = 0; i <= cnt - 1; i++)
	{
		Table* tmp = new Table;
		fs >> tmp->tableName;
		fs >> tmp->titleCnt;
		for (int i = 0; i <= tmp->titleCnt - 1; i++)
		{
			string type, name;
			fs >> name >> type;
			tmp->titleName.push_back(name);
			tmp->titleType.push_back(type);
		}
		tmp->tableAddr.open(fileprePath + tmp->tableName);
		if (!tmp->tableAddr.is_open())
		{
			cout << "数据表" << tmp->tableName << "加载失败" << endl;
		}
		else
		{
			tableList.push_back(tmp);
		}
	}
	cout << "数据库" << fileprePath << "打开成功" << endl;
	fs.close();
}

void MyDBMS::close_DBMS()
{
	this->~MyDBMS();
	fileprePath = "";
	Cmd = "";
}

void MyDBMS::new_DBMS()
{
	cout << "请输入数据库位置：" << endl;
	cout << " >";
	cin >> fileprePath;
	fstream fs;
	fs.open(fileprePath + "tableList.txt", ios::out);
	if (!fs.is_open())
	{
		cout << "数据库创建失败" << endl;
		fileprePath = "";
		return;
	}
	open = true;
	cout << "数据库" << fileprePath << "创建并打开成功" << endl;
	fs.close();
}

void MyDBMS::new_Table()
{
	if (open)
	{
		Table* tmp = new Table;
		cout << "请输入数据表名称" << endl;
		cout << ">";
		cin >> tmp->tableName;
		tmp->tableAddr.open(fileprePath + tmp->tableName, ios::out);
		if (!tmp->tableAddr.is_open())
		{
			cout << "数据表创建失败" << endl;
			return;
		}
		cout << "请输入表头数量" << endl;
		cout << ">";
		cin >> tmp->titleCnt;
		for (int i = 0; i <= tmp->titleCnt - 1; i++)
		{
			string type, name;
			cout << "表头名称" << endl;
			cout << ">";
			cin >> name;
			cout << "表头数据类型" << endl;
			cout << ">";
			cin >> type;
			tmp->titleName.push_back(name);
			tmp->titleType.push_back(type);
		}
		tmp->tableAddr.open(fileprePath + tmp->tableName);
		tableList.push_back(tmp);
		fstream dbs;
		dbs.open(fileprePath + "\\tableList.txt", ios::trunc | ios::out);
		dbs << tableList.size() << endl;
		for (int i = 0; i <= tableList.size() - 1; i++)
		{
			dbs << tableList[i]->tableName << " " << tableList[i]->titleCnt << endl;
			for (int j = 0; j <= tableList[i]->titleCnt - 1; j++)
			{
				dbs << tableList[i]->titleName[j] << " " << tableList[i]->titleType[j] << endl;
			}
		}
		dbs.close();
	}
	else
	{
		cout << "请先打开数据库" << endl;
	}
}

void MyDBMS::del_Table()
{
	if (open)
	{
		string nm;
		cout << "请输入数据表名称" << endl;
		cout << ">";
		cin >> nm;
		fstream fs;
		fs.open(fileprePath + nm);
		if (!fs.is_open())
		{
			cout << "数据表" << nm << "不存在" << endl;
			return;
		}
		if (remove((fileprePath + nm).c_str()) == -1)
		{
			cout << "数据表文件删除失败" << endl;
			return;
		}
		for (int i = 0; i <= tableList.size() - 1; i++)
		{
			if (tableList[i]->tableName == nm)
			{
				tableList.erase(tableList.begin() + i);
				break;
			}
		}
		fstream dbs;
		dbs.open(fileprePath + "tableList.txt", ios::trunc | ios::out);
		dbs << tableList.size() << endl;
		for (int i = 0; i <= tableList.size() - 1; i++)
		{
			dbs << tableList[i]->tableName << " " << tableList[i]->titleCnt << endl;
			for (int j = 0; j <= tableList[i]->titleCnt - 1; j++)
			{
				dbs << tableList[i]->titleName[j] << " " << tableList[i]->titleType[j] << endl;
			}
		}
		dbs.close();
	}
	else
	{
		cout << "请先打开数据库" << endl;
	}
}

void MyDBMS::ins_Data()
{
	if (open)
	{
		string nm;
		cout << "请选择数据表" << endl;
		cout << ">";
		cin >> nm;
		for (auto it = tableList.begin(); it != tableList.end(); it++)
		{
			if (nm == (*it)->tableName)
			{
				for (int j = 0; j <= (*it)->titleCnt - 1; j++)
				{
					string _type = (*it)->titleType[j];
					if (_type == "int")
					{
						cout << (*it)->titleName[j] << " " << (*it)->titleType[j] << endl;
						cout << ">";
						int x;
						cin >> x;
						if (j != (*it)->titleCnt - 1)
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << " ";
						}
						else
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << endl;
						}
					}
					else if (_type == "float")
					{
						cout << (*it)->titleName[j] << " " << (*it)->titleType[j] << endl;
						cout << ">";
						float x;
						cin >> x;
						if (j != (*it)->titleCnt - 1)
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << " ";
						}
						else
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << endl;
						}
					}
					else if (_type == "double")
					{
						cout << (*it)->titleName[j] << " " << (*it)->titleType[j] << endl;
						cout << ">";
						double x;
						cin >> x;
						if (j != (*it)->titleCnt - 1)
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << " ";
						}
						else
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << endl;
						}
					}
					else if (_type == "char")
					{
						cout << (*it)->titleName[j] << " " << (*it)->titleType[j] << endl;
						cout << ">";
						char x;
						cin >> x;
						if (j != (*it)->titleCnt - 1)
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << " ";
						}
						else
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << endl;
						}
					}
					else if (_type == "string")
					{
						cout << (*it)->titleName[j] << " " << (*it)->titleType[j] << endl;
						cout << ">";
						string x;
						cin >> x;
						if (j != (*it)->titleCnt - 1)
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << " ";
						}
						else
						{
							(*it)->tableAddr.clear();
							(*it)->tableAddr.seekg(0, ios::end);
							(*it)->tableAddr << x << endl;
						}
					}
				}
			}
		}
	}
	else
	{
		cout << "请先打开数据库" << endl;
	}
}

void MyDBMS::del_Data()
{
	if (open)
	{
		string nm;
		cout << "请选择数据表" << endl;
		cout << ">";
		cin >> nm;
		for (int i = 0; i <= tableList.size() - 1; i++)
		{
			if (tableList[i]->tableName == nm)
			{
				if (!tableList[i]->tableAddr.is_open())
				{
					cout << "未找到该数据表" << endl;
				}
				cout << "rank";

				for (int j = 0; j <= tableList[i]->titleName.size() - 1; j++)
				{
					cout << "    " << tableList[i]->titleName[j];
				}
				cout << endl;

				vector<string> vec;
				int rank = 1;

				tableList[i]->tableAddr.clear();
				tableList[i]->tableAddr.seekg(0, ios::beg);
				while (!tableList[i]->tableAddr.eof())
				{
					string* tmp = new string;
					getline(tableList[i]->tableAddr, *tmp, '\n');
					if ((*tmp).size() != 0)
					{
						cout << rank << "  " << *tmp << endl;
						vec.push_back(*tmp);
						rank++;
					}
				}

				int num;
				if (vec.size() != 0)
				{
					cout << "请输入要删除的编号" << endl;
					cout << ">";
					cin >> num;
					if (num > vec.size())
					{
						cout << "无该编号" << endl;
						break;
					}
				}
				else
				{
					cout << "该表为空表" << endl;
					break;
				}

				vec.erase(vec.begin() + num - 1);

				tableList[i]->tableAddr.clear();
				tableList[i]->tableAddr.close();
				tableList[i]->tableAddr.open(fileprePath + tableList[i]->tableName, ios::trunc | ios:: out);

				if(!vec.empty())tableList[i]->tableAddr << vec[0];

				for (int k = 1; k <= vec.size() - 1; k++)
				{
					tableList[i]->tableAddr << endl << vec[k];
				}

				tableList[i]->tableAddr.close();
				tableList[i]->tableAddr.open(fileprePath + tableList[i]->tableName);
			}
		}
	}
	else
	{
		cout << "请先打开数据库" << endl;
	}
}

void MyDBMS::check_Data()
{
	if (open)
	{
		string nm;
		cout << "请选择数据表" << endl;
		cout << ">";
		cin >> nm;
		for (int i = 0; i <= tableList.size() - 1; i++)
		{
			if (tableList[i]->tableName == nm)
			{
				if (!tableList[i]->tableAddr.is_open())
				{
					cout << "未找到该数据表" << endl;
				}
				
				cout << "请选择查询内容" << endl;
				cout << ">";
				string nm;
				cin >> nm;

				vector<string> vec;

				tableList[i]->tableAddr.clear();
				tableList[i]->tableAddr.seekg(0, ios::beg);
				while (!tableList[i]->tableAddr.eof())
				{
					string* tmp = new string;
					getline(tableList[i]->tableAddr, *tmp, '\n');
					if ((*tmp).size() != 0)
					{
						vec.push_back(*tmp);
					}
				}

				if (vec.empty())
				{
					cout << "该表为空表" << endl;
					break;
				}

				bool flag = true;
				for (int j = 0; j <= vec.size() - 1; j++)
				{
					int begin = -1;
					if (begin = vec[j].find(nm,begin + 1) != string::npos)
					{
						if (flag)
						{
							cout << tableList[i]->titleName[0];
							for (int j = 1; j <= tableList[i]->titleName.size() - 1; j++)
							{
								cout << "    " << tableList[i]->titleName[j];
							}
							cout << endl;
							flag = false;
						}
						cout << vec[j] << endl;
					}
				}
				if (flag)
				{
					cout << "未查询到该信息" << endl;
				}
			}
		}
	}
	else
	{
		cout << "请先打开数据库" << endl;
	}
}

int main()
{
	MyDBMS db;
	db.Cmd = "";
	while (cin >> db.Cmd)
	{
		if (db.Cmd == "exit")
		{
			db.~MyDBMS();
			return 0;
		}
		else if (db.Cmd == "openDatabase")
		{
			if (!db.open)
			{
				db.open_DBMS();
			}
			else
			{
				cout << "请关闭已经打开的数据库" << endl;
			}
		}
		else if (db.Cmd == "newDatabase")
		{
			if (!db.open)
			{

				db.new_DBMS();
			}
			else
			{
				cout << "请关闭已经打开的数据库" << endl;
			}
		}
		else if (db.Cmd == "newTable")
		{
			db.new_Table();
		}
		else if (db.Cmd == "insertData")
		{
			db.ins_Data();
		}
		else if (db.Cmd == "delTable")
		{
			db.del_Table();
		}
		else if (db.Cmd == "delData")
		{
			db.del_Data();
		}
		else if (db.Cmd == "checkData")
		{
			db.check_Data();
		}
		else if (db.Cmd == "closeDatabase")
		{
			db.close_DBMS();
		}
	}
	return 0;
}