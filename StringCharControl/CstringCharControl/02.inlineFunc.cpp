//#include <iostream>
//#include <string>
//#include <stdio.h>
//
//
//using namespace std;
///*
//			summary
//	1.inline ��Ϊ�˽��һЩƵ������С������������ջ�ռ������   
//	2.inlineֻ�ʺϼ򵥵ĺ�����ʹ��  ������while  switch�Ⱥ����������ݹ麯��Ч���ǲ��ߵ�
//	3.inline�����Ķ������ͷ�ļ���    
//	4.inline��һ������ʵ�ֵĹؼ���,������inline���ں���������ǰ�ǲ����κ����õ�
//	inline void Foo(int x,int y);
//	void Foo(int x , int y){}  ������û���õ�
//	5.inline�ǽ���#defineһ��   �ں���ִ�е�ʱ�򽫺��������滻��Ϊ�������ڲ�����䣬���Ե��ڲ����ܶ��ʱ��inline�Ͳ�̫�ʺ�
//	6.�����ڲ�ʵ�ֵķ���Ĭ�϶�����������
//
//
//*/
//inline const char* dbTest(int a)
//{
//	return (a % 2 > 0) ? "��" : "ż";
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