//#include <iostream>
//#include <string>
//
//using namespace std;
///*
//			summary
//	���������   
//	��Ҫһ������ srand
//	rand()�����������������
//	������ȡ��ķ��������������
//*/
//
////int main()
////{
////	int j;
////	srand((unsigned)time_t(NULL));
////	for (int i = 0; i < 10; i++)
////	{
////		j = rand() % 10;   //����0~10������10  ��Χ�������
////		cout << j << endl;
////	}
////
////	cout << "0~100֮��10�������:" << endl;
////	int x;
////	srand((unsigned)time_t(NULL)); //����ʱ�������������
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
//	/*����0~1000֮���100�������*/
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
