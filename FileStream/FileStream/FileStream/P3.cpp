#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	//打开文件流
	//预定写多少字符
	//写入
	//忽略之前的输入
	//继续写入
	//to do ...
	//关闭文件


	//新建一个P3.txt的文件   并且在里面存储姓名和年龄
	char data[100];
	ofstream outfile;

	outfile.open("E:\\test\\P3.txt");
	cout << "Enter your name: " << endl;
	//预定要输入多少字符
	cin.getline(data, 100);
	outfile << data << endl;
	cout << "Enter your age" << endl;
	cin >> data;
	cin.ignore();
	outfile << data << endl;
	outfile.close();

	system("pause");
	return 0;
}

