//#include <iostream>
//#include <string>
//
//
//using namespace std;
//
//class Test
//{
//public :
//	void hello()
//	{
//		cout << "hello";
//	};
//	void lambda()
//	{
//		//定义了一个lambda函数  匿名函数
//		auto fun = [this]
//		{
//			this->hello();
//		};
//		fun();
//	}
//
//};
//
//int main()
//{
//	/*auto basicLambda = [] {cout << "Hello Lambda" << endl; };
//	basicLambda();
//
//	auto add = [](int a, int b)
//	{
//		return a + b;
//	};
//	cout << add(1, 2) << endl;
//	auto mult = [](int c, int d)->int
//	{
//		return c * d;
//	};
//	cout << mult(3, 4) << endl;*/
//
//	/*int i = 1024;
//	auto func = [=] 
//	{
//		cout << i << endl;
//	};
//
//	func();*/
//	//int i = 1024;
//	////cout << &i << endl;
//	//auto fun1 = [&]
//	//{
//	//	cout << &i << endl;
//	//};
//	//fun1();
//
//	//int a = 1024, b = 2048;
//
//	//auto func_1 = [=, &i]
//	//{
//	//	cout << "a: " << &a << endl;
//	//	cout << "b: " << &b << endl;
//	//};
//	//func_1();
//	Test tes;
//	tes.lambda();
//	system("pause");
//	return 0;
//}