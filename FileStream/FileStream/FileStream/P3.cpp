#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	//���ļ���
	//Ԥ��д�����ַ�
	//д��
	//����֮ǰ������
	//����д��
	//to do ...
	//�ر��ļ�


	//�½�һ��P3.txt���ļ�   ����������洢����������
	char data[100];
	ofstream outfile;

	outfile.open("E:\\test\\P3.txt");
	cout << "Enter your name: " << endl;
	//Ԥ��Ҫ��������ַ�
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

