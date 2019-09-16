//#include <iostream>
//#include <fstream>
//
//using namespace std;
//int main()
//{
//	char data[100];
//	//int a = 1;
//
//	//cout << "一个char类型所占的字节数是: " << sizeof(data) << endl;
//	//以写模式打开文件
//	ofstream outfile;
//	outfile.open("E:\\test\\Resolution.txt");
//	//tips  提示
//	cout << "Writing to the file" << endl;
//	cout << "enter your name: ";
//	//一次读取多个字符，直到第x个字符的位置
//	cin.getline(data, 100);   //其实相当于scanf   预定要输入多少个字符
//	//将data中的数据写入outfile 并且换行
//	outfile << data << endl;
//
//	cout << "Enter your age: ";
//	////将data里面有的数据进行忽略  
//	cin >> data;
//	cin.ignore();
//	outfile << data << endl;
//	
//	//写入第三个数据
//	cout << "Enter your gender: ";
//	cin >> data;
//	cin.ignore();
//	outfile << data << endl;
//
//	outfile.close();
//
//
//
//	//以读模式打开文件
//	ifstream infile;
//	infile.open("E:\\test\\Resolution.txt");
//
//	cout << "Reading from the file" << endl;
//	//利用infile文件读取数据到data
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