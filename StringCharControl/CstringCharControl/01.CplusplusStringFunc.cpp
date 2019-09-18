//#include <iostream>
//#include <string>
//using namespace std;
//
//
//int main()
//{
//	//string http = "www.baidu.com";
//
//	//cout << http.length() << endl;
//
//	////拼接字符串
//	//http.append("/houjf.txt");
//	//cout << http << endl;
//
//	////查找删除  replace  替换 也可以用空字符串来进行删除
//	//int pos = http.find(".txt");
//	//http.replace(pos, 4, "");
//	//cout << http << endl;
//
//	////查找子串
//	//int first = http.find_first_of(".");
//	//int last = http.find_last_of(".");
//	//cout << http.substr(first + 1, last - first - 1) << endl;
//
//	string url = "www.devjeer.org";
//	//字符串的拼接
//	url.append("/document.txt");
//	cout << "原来字符串的值: "<< url << endl;
//	//字符串的复制
//	string url_1 = url;
//	cout << "复制之后url_1的值: "<<url_1 << endl;
//	//字符串的查找替换
//	int pos = url.find(".txt");
//	url.replace(pos, 4, "");
//	cout <<"查找替换之后url的值: "<< url << endl;
//	//查找字符串的子串
//	int first = url.find_first_of(".");  //查找第一个.
//	int second = url.find_last_of(".");  //查找最后一个点
//	string c =url.substr(first + 1, second - first - 1);   //在一个区间
//	cout << "字符串的子串: "<<c << endl;
//
//
//	system("pause");
//	return 0;
//}