//#include <iostream>
//#include <fstream>
//
//using namespace std;
//int main()
//{
//	char data[100];
//	//int a = 1;
//
//	//cout << "һ��char������ռ���ֽ�����: " << sizeof(data) << endl;
//	//��дģʽ���ļ�
//	ofstream outfile;
//	outfile.open("E:\\test\\Resolution.txt");
//	//tips  ��ʾ
//	cout << "Writing to the file" << endl;
//	cout << "enter your name: ";
//	//һ�ζ�ȡ����ַ���ֱ����x���ַ���λ��
//	cin.getline(data, 100);   //��ʵ�൱��scanf   Ԥ��Ҫ������ٸ��ַ�
//	//��data�е�����д��outfile ���һ���
//	outfile << data << endl;
//
//	cout << "Enter your age: ";
//	////��data�����е����ݽ��к���  
//	cin >> data;
//	cin.ignore();
//	outfile << data << endl;
//	
//	//д�����������
//	cout << "Enter your gender: ";
//	cin >> data;
//	cin.ignore();
//	outfile << data << endl;
//
//	outfile.close();
//
//
//
//	//�Զ�ģʽ���ļ�
//	ifstream infile;
//	infile.open("E:\\test\\Resolution.txt");
//
//	cout << "Reading from the file" << endl;
//	//����infile�ļ���ȡ���ݵ�data
//	infile >> data;
//	cout << data << endl;
//	infile >> data;
//	cout << data << endl;
//	infile >> data;
//	cout << data << endl;
//	infile.close();
//
//	system("pause");
//	return 0;
//}