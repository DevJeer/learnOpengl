//#include <iostream>
//#include <string>
//#include <stdio.h>
//
//
//using namespace std;
///*
//			summary
//	1.inline 是为了解决一些频繁调用小函数大量消耗栈空间的问题   
//	2.inline只适合简单的函数体使用  对于有while  switch等函数，甚至递归函数效率是不高的
//	3.inline函数的定义放在头文件中    
//	4.inline是一种用于实现的关键字,仅仅将inline放在函数声明面前是不起任何作用的
//	inline void Foo(int x,int y);
//	void Foo(int x , int y){}  这样是没有用的
//	5.inline是将和#define一样   在函数执行的时候将函数方法替换成为函数体内部的语句，所以当内部语句很多的时候，inline就不太适合
//	6.在类内部实现的方法默认都是内联函数
//
//
//*/
//inline const char* dbTest(int a)
//{
//	return (a % 2 > 0) ? "奇" : "偶";
//}
//
//
//inline int adder(int& i)
//{
//	i++;
//	return i;
//}
//
//int main()
//{
//
//	int i = 0;
//	for (i = 0; i < 100; i++)
//	{
//		cout << i << ": " << dbTest(i) << endl;
//		cout << "adder(i)"<< adder(i) << endl;
//	}
//
//	system("pause");
//	return 0;
//}