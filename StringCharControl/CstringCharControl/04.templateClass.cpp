//#include <iostream>
//#include <string>
//#include <vector>
//#include <cstdlib>
//#include <stdexcept>
//
//
//using namespace std;
//
////ģ�庯��
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
////ģ����
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
//	elemts.pop_back(); //ɾ�����һ��Ԫ��
//}
//template <class T>
//T  Stack<T>::top() const
//{
//	if (elemts.empty())
//	{
//		throw out_of_range("empty stack");
//	}
//	//�������һ��Ԫ�صĸ���
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
//	//����string���͵�ջ
//	stringStack.push("hello template");
//	cout << stringStack.top() << endl;
//	stringStack.pop();
//	intStack.pop();
//
//	system("pause");
//	return 0;
//}