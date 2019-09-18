#include <iostream>
#include <string>

using namespace std;
/*
			summary
	生成随机数   
	需要一个种子 srand
	rand()方法可以生成随机数
	可以用取余的方法来产生随机数
*/

int main()
{
	int j;
	srand((unsigned)time_t(NULL));
	for (int i = 0; i < 10; i++)
	{
		j = rand() % 10;   //生成0~10不包括10  范围的随机数
		cout << j << endl;
	}

	system("pause");
	return 0;
}