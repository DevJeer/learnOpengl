#include <iostream>
#include <string>

using namespace std;
/*
			summary
	���������   
	��Ҫһ������ srand
	rand()�����������������
	������ȡ��ķ��������������
*/

int main()
{
	int j;
	srand((unsigned)time_t(NULL));
	for (int i = 0; i < 10; i++)
	{
		j = rand() % 10;   //����0~10������10  ��Χ�������
		cout << j << endl;
	}

	system("pause");
	return 0;
}