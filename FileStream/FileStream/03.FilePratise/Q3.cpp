#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void writeFiles();
void copyFiles();

int main()
{
	writeFiles();
	copyFiles();

	system("pause");
	return 0;
}

void writeFiles()
{
	char data[100];
	ofstream outfiles;
	outfiles.open("E:\\test\\Q3.txt");
	cout << "enter your name: " << endl;
	cin.getline(data, 100);
	outfiles << data << endl;
	cout << "enter your gender:" << endl;
	cin >> data;
	cin.ignore();
	outfiles << data << endl;
	outfiles.close();
}

void copyFiles()
{
	char data[100];
	ifstream infiles;
	infiles.open("E:\\test\\Q3.txt");
	ofstream outfiles;
	outfiles.open("E:\\test\\Q3_copy.txt");
	while (infiles >> data)
	{
		cout << "copying..." << data << endl;
		outfiles << data << endl;
	}
}