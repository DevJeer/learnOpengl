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
//	////ƴ���ַ���
//	//http.append("/houjf.txt");
//	//cout << http << endl;
//
//	////����ɾ��  replace  �滻 Ҳ�����ÿ��ַ���������ɾ��
//	//int pos = http.find(".txt");
//	//http.replace(pos, 4, "");
//	//cout << http << endl;
//
//	////�����Ӵ�
//	//int first = http.find_first_of(".");
//	//int last = http.find_last_of(".");
//	//cout << http.substr(first + 1, last - first - 1) << endl;
//
//	string url = "www.devjeer.org";
//	//�ַ�����ƴ��
//	url.append("/document.txt");
//	cout << "ԭ���ַ�����ֵ: "<< url << endl;
//	//�ַ����ĸ���
//	string url_1 = url;
//	cout << "����֮��url_1��ֵ: "<<url_1 << endl;
//	//�ַ����Ĳ����滻
//	int pos = url.find(".txt");
//	url.replace(pos, 4, "");
//	cout <<"�����滻֮��url��ֵ: "<< url << endl;
//	//�����ַ������Ӵ�
//	int first = url.find_first_of(".");  //���ҵ�һ��.
//	int second = url.find_last_of(".");  //�������һ����
//	string c =url.substr(first + 1, second - first - 1);   //��һ������
//	cout << "�ַ������Ӵ�: "<<c << endl;
//
//
//	system("pause");
//	return 0;
//}