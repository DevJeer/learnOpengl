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
	1.命名空间可以在一个项目下的函数体外进行创建
	2.它可以包含类 函数 变量等
	3.调用命名空间下的方法要使用   命名空间::函数方法
	4.我们可以在.cpp .h文件中创建  并且它可以嵌套


*/

int main()
{
	myNamespace::a = 1;
	myNamespace::myFunc();
	cout << myNamespace::a << endl;



	system("pause");
	return 0;
}