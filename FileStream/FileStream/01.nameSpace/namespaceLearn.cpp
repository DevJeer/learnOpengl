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
namespace myNamespace_1
{
	int width = 10;
	int height = 10;
	void myFunc1()
	{
		cout << "hellp this is myFunc1" << endl;
	}
	class Box
	{
	public:
		int GetSurface(void)
		{
			int c = width * height;
			return c;
		}

	private:

	};
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
	myNamespace_1::myFunc1();
	myNamespace_1::Box box;
	cout << box.GetSurface() << endl;


	system("pause");
	return 0;
}