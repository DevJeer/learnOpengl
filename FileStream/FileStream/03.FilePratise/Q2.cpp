//#include <iostream>
//#include <string>
//#include <fstream>
//
//using namespace std;
//
//void writeFiles();
//void copyFiles();
//
//int main()
//{
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
//	outfiles.open("E:\\test\\Q2.txt");
//	cout << "enter your number: " << endl;
//	cin.getline(data, 100);
//	outfiles << data << endl;
//	cout << "enter your age: " << endl;
//	cin >> data;
//	cin.ignore();
//	outfiles << data << endl;
//
//	outfiles.close();
//}
//
//void copyFiles()
//{
//	char data[100];
//	ifstream infiles;
//	infiles.open("E:\\test\\Q2.txt");
//	ofstream outfiles;
//	outfiles.open("E:\\test\\Q2_copy.txt");
//	while (infiles >> data)
//	{
//		cout << "writing:" << data << endl;
//		outfiles << data << endl;
//	}
//	infiles.close();
//	outfiles.close();
//}