//#include <iostream>
//#include <string>
//#include <fstream>
//
//
//using namespace std;
//
///*
//	summary
//	�����ļ�  ����д���ļ�   copy
//*/
//
//void writeFiles();
//
//void copyFiles();
//
//int main()
//{
//	
//	writeFiles();
//	copyFiles();
//
//	system("pause");
//	return 0;
//}
//
//void writeFiles()
//{
//	char data[100];
//	ofstream outfiles;
//	outfiles.open("E:\\test\\Q1.txt");
//
//	cout << "enter your name : " << endl;
//	cin.getline(data, 100);   /*����֮ǰ��ȡ����*/
//	outfiles << data << endl;
//	cout << "enter your gender : " << endl;
//	cin >> data;
//	cin.ignore();
//	outfiles << data << endl;
//}
//
//void copyFiles()
//{
//	//��ȡҪCopy���ļ�
//	char data[100];
//	ifstream infiles;
//	infiles.open("E:\\test\\Q1.txt");
//	ofstream outfiles;
//	outfiles.open("E:\\test\\Q1_copy.txt");
//	while (infiles >> data)
//	{
//		cout << "reading files..." << data << endl;
//		outfiles << data << endl;
//	}
//	cout << "read completed" << endl;
//	
//}