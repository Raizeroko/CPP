#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<stdlib.h>
#include<vector>
using namespace::std;

//float calculation(float A, float a, float b, float c, float d)
//{
//	float B = 0;
//	B = ((A - a) / (c - a) * (d - b)) + b;
//	return B;
//}
//
//
//int main()
//{
//	float A,B;
//	vector<float> input = {};
//	string show[22] = { "A","a","b","c","d",
//							"a1","a2","a3","a4",
//							"b1","b2","b3","b4",
//							"c1","c2","c3","c4",
//							"d1","d2","d3","d4","B"};
//
//	for (int i = 0; i < 21; i++)
//	{
//		cout << show[i]<<" = ";
//		float tmp;
//		cin >> tmp;
//		input.push_back(tmp);
//	}
//	cout << "*******************************************************\n";
//	for (int i = 1; i <= 4; i++)
//	{
//		if (input[i] == 0)
//		{
//			input[i] = calculation(input[0], input[4*i+1], input[4*i+2], input[4*i+3], input[4*i+4]);
//			cout << show[i] << " = " << input[i] << '\n';
//		}
//	}
//	cout << "*****************\n";
//	cout << "是否需要输入A’？(0/1)：";
//	int choose;
//	cin >> choose;
//	if (choose != 1 && choose != 0)
//	{
//		cout << "输入有误";
//		exit(-1);
//	}
//	if (choose == 1)
//	{
//		float _A = 0;
//		cout << "_A:";
//		cin >> _A;
//		float tmp = calculation(_A, input[1], input[2], input[3], input[4]);
//		cout << show[21] << " = " << tmp << '\n';
//
//	}
//	else
//	{
//		float tmp = calculation(input[0], input[1], input[2], input[3], input[4]);
//		cout << show[21] << " = " << tmp << '\n';
//	}



	//input.push_back(tmp);


	//cout << show[21] << " = " << tmp << '\n';

	/*if (input[1] == 0)
	{
		input[1] = calculation(input[0], input[5], input[6], input[7], input[8]);
		cout << show[1] << " = " << input[1];
	}
	if (input[2] == 0)
	{
		input[2] = calculation(input[0], input[9], input[10], input[11], input[12]);
		cout << show[2] << " = " << input[2];


	}
	if (input[3] == 0)
	{
		input[3] = calculation(input[0], input[13], input[14], input[15], input[16]);
		cout << show[3] << " = " << input[3];


	}
	if (input[4] == 0)
	{
		input[4] = calculation(input[0], input[17], input[18], input[19], input[20]);
		cout << show[4] << " = " << input[4];

	}*/
	int main()
	{

		float A, B, a, b, c, d;
		cout << "A = ";
		cin >>A;
		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;
		cout << "c = ";
		cin >> c;
		cout << "d = ";
		cin >> d;

		B = ((A - a) / (c - a) * (d - b)) + b;
		cout << "计算结果：";
		cout << "B = " << B << '\n';

		system("pause");
		return 0;
}