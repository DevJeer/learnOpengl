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
//class Man
//{
//public :
//	void sayHello();
//	void Lambda();
//	
//private:
//	int a = 10;
//	int b = 10;
//};
//
//void Man::sayHello()
//{
//	cout << "Hello  guy" << endl;
//}
//
//void Man::Lambda()
//{
//	auto funMan = [this]
//	{
//		cout << "a :"<<this->a << endl;
//		cout <<"b :"<< this->b << endl;
//		this->sayHello();
//	};
//	funMan();
//}
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
//	int i = 1024;
//	cout << &i << endl;
//	auto fun1 = [&]
//	{
//		cout << &i << endl;
//	};
//	fun1();
//
//	auto fun2 = [](int add1, int add2) 
//	{
//		return add1 + add2;
//	};
//	int ddd = fun2(1, 2);
//	cout << "ddd is " << ddd << endl;
//
//	int a = 1024, b = 2048;
//
//	auto func_1 = [=, &i]
//	{
//		cout << "a: " << &a << endl;
//		cout << "b: " << &b << endl;
//	};
//	Man man;
//	man.Lambda();
//
//	func_1();
//	Test tes;
//	tes.lambda();
//	system("pause");
//	return 0;
//}