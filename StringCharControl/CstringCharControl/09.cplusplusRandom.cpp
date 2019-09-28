//#include <iostream>
//#include <string>
//
//using namespace std;
///*
//			summary
//	生成随机数   
//	需要一个种子 srand
//	rand()方法可以生成随机数
//	可以用取余的方法来产生随机数
//*/
//
////int main()
////{
////	int j;
////	srand((unsigned)time_t(NULL));
////	for (int i = 0; i < 10; i++)
////	{
////		j = rand() % 10;   //生成0~10不包括10  范围的随机数
////		cout << j << endl;
////	}
////
////	cout << "0~100之间10次随机数:" << endl;
////	int x;
////	srand((unsigned)time_t(NULL)); //根据时间来生成随机数
////	for (int y = 0; y < 10; y++)
////	{
////		x = rand() % 100;
////		cout << x << endl;
////	}
////
////	system("pause");
////	return 0;
////}
//
//
//
//
//
//int SpawnNumber();
//
//
//int main()
//{
//	srand((unsigned)time_t(NULL));
//	/*生成0~1000之间的100个随机数*/
//	for (size_t i = 0; i < 1000; i++)
//	{
//		cout << SpawnNumber() << endl;
//	};
//	int j = 0;
//	/*for (size_t i = 0; i < 1000; i++)
//	{
//		j = rand() % 1000;
//		cout << j << endl;
//	}*/
//	system("pause");
//	return 0;
//}
//
//inline int SpawnNumber()
//{
//	int c = rand() % 1000;
//
//	return c;
//}
