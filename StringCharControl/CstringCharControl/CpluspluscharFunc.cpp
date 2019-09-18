//#include <iostream>
////#include <string>
//using namespace std;
///*
//			summary
//	strcpy_s()     复制一个字符串
//	strcat()         连接两个字符串
//	strlen()         得到一个字符串的长度
//*/
//
//int main()
//{
//	//char str1[11] = "Hello";
//	//char str2[11] = "World";
//	//char str3[11];
//	//int len;
//	//char str_data[50];
//
//	////复制str1到str3
//	//strcpy_s(str3, str1);
//	//cout << "拷贝后str3: " << str3 << endl;
//	////连接str1与str2
//	//strcat_s(str1, str2);
//	//cout << "连接后str1: " << str1 << endl;
//
//
//	//strcpy_s(str_data, str1);
//	//cout << "str_data: " << str_data << endl;
//	////连接后str1的总长度
//	//len = strlen(str1);
//	//cout << len << endl;
//
//	//第二遍练习 char类型  字符串之间的连接， 复制
//	char firstName[10] = "Dev";
//	char secondName[10] = "Jeer";
//	char fullName[20];
//	int len;
//	strcpy_s(fullName, secondName);
//	cout << "strcpy_s(fullName,secondName): " << fullName << endl;
//	strcat_s(firstName, secondName);
//	cout << "strcat_s(firstName,secondName): " << firstName << endl;
//	len = strlen(firstName);
//	cout << len << endl;
//	
//	
//	system("pause");
//	return 0;
//}