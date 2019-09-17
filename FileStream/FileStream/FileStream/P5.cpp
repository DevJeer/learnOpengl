#include <iostream>
#include <fstream>

using namespace std;

void wrFiles();
void copyFiles();

int main()
{

	wrFiles();
	copyFiles();

	system("pause");
	return 0;
}
void wrFiles()
{
	char data[100];
	ofstream outFile;
	outFile.open("E:\\test\\P5.txt");
	cout << "start write..." << endl;
	cout << "enter your number: " << endl;
	cin.getline(data, 100);
	outFile << data << endl;
	cout << "enter you project: " << endl;
	cin >> data;
	cin.ignore();
	outFile << data << endl;
	outFile.close();

}

void copyFiles()
{
	char data[100];
	ifstream inFile;
	inFile.open("E:\\test\\P5.txt");
	ofstream outFile;
	outFile.open("E:\\test\\P5_1.txt");
	while (inFile >> data)
	{
		cout << data << endl;
		outFile << data << endl;
	}
	inFile.close();
	outFile.close();


}