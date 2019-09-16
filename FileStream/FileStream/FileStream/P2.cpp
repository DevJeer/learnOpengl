//#include <iostream>
//#include <fstream>
//using namespace std;
//
//void readFiles();
//void copyFiles();
//
//int main()
//{
//	readFiles();
//	copyFiles();
//
//	system("pause");
//	return 0;
//}
//
//void readFiles()
//{
//	char data[100];
//	ifstream infile;
//	infile.open("E:\\test\\code.txt");
//	cout << "start read code.txt" << endl;
//
//	while (infile >> data)
//	{
//		cout << data << endl;
//	}
//	infile.close();
//}
//
//void copyFiles()
//{
//	char data[100];
//	ifstream infile;
//	ofstream outfile;
//	infile.open("E:\\test\\code.txt");
//	outfile.open("E:\\test\\code_1.txt");
//	cout << "copy code.txt to code_1.txt" << endl;
//	while (infile >> data)
//	{
//		outfile << data << endl;
//	}
//	cout << "copy completed !!!" << endl;
//	infile.close();
//	outfile.close();
//
//}