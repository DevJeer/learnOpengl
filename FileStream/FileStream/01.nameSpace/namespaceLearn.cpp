#include <iostream>

using namespace std;
namespace myNamespace
{
	int a = 0;
	int b = 1;
	void myFunc()
	{
		printf("hello world");
		cout << "this is myNamespace func" << endl;
	}

}
////////////Summary////////////
/*
	1.�����ռ������һ����Ŀ�µĺ���������д���
	2.�����԰����� ���� ������
	3.���������ռ��µķ���Ҫʹ��   �����ռ�::��������
	4.���ǿ�����.cpp .h�ļ��д���  ����������Ƕ��


*/

int main()
{
	myNamespace::a = 1;
	myNamespace::myFunc();
	cout << myNamespace::a << endl;



	system("pause");
	return 0;
}