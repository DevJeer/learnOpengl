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
//	//ƴ���ַ���
//	http.append("/houjf.txt");
//	cout << http << endl;
//
//	//����ɾ��  replace  �滻 Ҳ�����ÿ��ַ���������ɾ��
//	int pos = http.find(".txt");
//	http.replace(pos, 4, "");
//	cout << http << endl;
//
//	//�����Ӵ�
//	int first = http.find_first_of(".");
//	int last = http.find_last_of(".");
//	cout << http.substr(first + 1, last - first - 1) << endl;
//
//	system("pause");
//	return 0;
//}