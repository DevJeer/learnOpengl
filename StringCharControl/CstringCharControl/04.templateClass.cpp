//#include <iostream>
//#include <string>
//#include <vector>
//#include <cstdlib>
//#include <stdexcept>
//
//
//using namespace std;
//
////模板函数
//template <class T>
//T const& MultTwo(T const& a, T const& b)
//{
//	return a * b;
//}
//
//template <class T>
//T const& SubTwo(T const& x, T const& y)
//{
//	return x - y;
//}
//
////模板类
//template <class T>
//class  Stack
//{
//public:
//	void push(T const&);
//	void pop();
//	T top() const;
//	bool empty() const
//	{
//		return elemts.empty();
//	}
//
//private:
//	vector<T> elemts;
//};
//
//template <class T>
//void Stack<T>::push(T const& elem)
//{
//	elemts.push_back(elem);
//}
//template <class T>
//void Stack<T>::pop()
//{
//	if (elemts.empty())
//	{
//		throw out_of_range("empty stack");
//	}
//	elemts.pop_back(); //删除最后一个元素
//}
//template <class T>
//T  Stack<T>::top() const
//{
//	if (elemts.empty())
//	{
//		throw out_of_range("empty stack");
//	}
//	//返回最后一个元素的副本
//	return elemts.back();
//}
//
//
//
//int main()
//{
//	/*int a = 2;
//	int b = 6;
//	double c = 18.0f;
//	double d = 25.666f;
//	cout << MultTwo(a, b) << endl;
//	cout << MultTwo(c, d) << endl;*/
//	Stack<int> intStack;
//	Stack<string> stringStack;
//
//	intStack.push(7);
//	cout << intStack.top() << endl;
//
//	//操作string类型的栈
//	stringStack.push("hello template");
//	cout << stringStack.top() << endl;
//	stringStack.pop();
//	intStack.pop();
//
//	system("pause");
//	return 0;
//}