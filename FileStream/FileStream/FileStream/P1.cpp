//#include <iostream>
//#include <fstream>
//using namespace std;
//
//void file_wr();
//void file_copy();
//
//int main()
//{
//
//	file_wr();
//	file_copy();
//
//	system("pause");
//	return 0;
//}
//
//
//void file_wr()
//{
//	char data[100];
//	ofstream outfile;
//	outfile.open("E:\\test\\P1.txt");
//	cout << "Write to the file" << endl;
//	cout << "Enter your name: " << endl;
//	cin.getline(data, 100);
//	outfile << data << endl;
//	cout << "Enter your gender:" << endl;
//	cin >> data;
//	cin.ignore();
//	outfile << data << endl;
//	outfile.close();
//
//	//¶ÁÈ¡Êý¾Ý
//	ifstream infile;
//	infile.open("E:\\test\\P1.txt");
//	cout << "Read from the file" << endl;
//	while (infile >> data)
//	{
//		cout << data << endl;
//	}
//	/*infile >> data;
//	cout << data << endl;
//	infile >> data;
//	cout << data << endl;*/
//	infile.close();
//	
//}
//
//void file_copy()
//{
//	char data[100];
//	ifstream infile;
//	ofstream outfile;
//	infile.open("E:\\test\\P1.txt");
//	outfile.open("E:\\test\\P1_1.txt");
//	cout << "copy from P1.txt to P1_1.txt" << endl;
//	/*while (!infile.eof())
//	{
//		infile >> data;
//		cout << data << endl;
//		outfile << data << endl;
//	}*/
//	while (infile >> data)
//	{
//		//cout << data << endl;
//		outfile << data << endl;
//	}
//	infile.close();
//	outfile.close();
//}