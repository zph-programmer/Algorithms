#pragma once
#include<string>

class RandUtils
{

private:
	static void random2(int* nums, int begin, int end, int low, int high);
public:
	static int* random(int n, int low, int high);//���ɷ�Χ��[low,high����n�������
	static void print(int* a, int length);
	static bool isSorted(int arr[], int length);
	static std::string intArrToStr(int arr[], int length);
    static int* parallelRandom( int n, int low, int hight, int threadNum);


};

