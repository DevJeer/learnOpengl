#include <iostream>
#include <fstream>

using namespace std;
void wrfile();
void copyFile();

int main()
{
	
	////写一个文件
	//char data[100];
	//ofstream outfile;
	//outfile.open("E:\\test\\P4.txt");
	//cout << "enter your name: " << endl;
	//cin.getline(data, 100);
	//outfile << data << endl;
	//cout << "enter your gender: " << endl;
	//cin >> data;
	//cin.ignore();
	//outfile << data << endl;
	//outfile.close();

	/*ifstream infile;
	infile.open("E:\\test\\P4.txt");
	while (infile >> data)
	{
		cout << data << endl;
	}
	infile.close();*/
	wrfile();
	copyFile();


	system("pause");
	return 0;
}
void wrfile()
{
	char data[100];
	ofstream outfile;
	outfile.open("E:\\test\\P4_1.txt");
	cout << "enter your name: " << endl;
	cin.getline(data, 100);
	outfile << data << endl;
	cout << "enter your gender" << endl;
	cin >> data;
	cin.ignore();
	outfile << data << endl;
	outfile.close();
}

void copyFile()
{
	char data[100];
	ifstream infile;
	infile.open("E:\\test\\P4_1.txt");
	ofstream outfile;
	outfile.open("E:\\test\\P4_1_1.txt");
	cout << "start copy ..." << endl;
	while (infile >> data)
	{
		outfile << data << endl;
	}
	cout << "copy completed..." << endl;
	infile.close();
	outfile.close();
}


