//#include <iostream>
//#include <string>
//using namespace std;
//
//
//int main()
//{
//	string http = "www.baidu.com";
//
//	cout << http.length() << endl;
//
//	//Æ´½Ó×Ö·û´®
//	http.append("/houjf.txt");
//	cout << http << endl;
//
//	//²éÕÒÉ¾³ý  replace  Ìæ»» Ò²¿ÉÒÔÓÃ¿Õ×Ö·û´®À´½øÐÐÉ¾³ý
//	int pos = http.find(".txt");
//	http.replace(pos, 4, "");
//	cout << http << endl;
//
//	//²éÕÒ×Ó´®
//	int first = http.find_first_of(".");
//	int last = http.find_last_of(".");
//	cout << http.substr(first + 1, last - first - 1) << endl;
//
//	system("pause");
//	return 0;
//}