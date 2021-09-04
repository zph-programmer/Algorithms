#include "Sorting.h"
#include "iostream"
#include "RandUtils.h"
#include <thread>
#include<vector>
using namespace std;

//��������
void Sorting::quickSort(int nums[], int length) {
	//sizeof(nums)/sizeof(nums[0]); �����ָ��Ͳ������ˣ�����length
	quick_sort(nums, 0, length - 1);
}

void Sorting::quick_sort(int nums[], int low, int high) {

	if (low < high) {
		// ��Ѱ��׼���ݵ���ȷ����
		int mid = partition(nums, low, high);
		//std::string numsStr = RandUtils::intArrToStr(nums, 10);
		//RandUtils::print(nums, 10);
		quick_sort(nums, low, mid - 1);
		quick_sort(nums, mid + 1, high);

	}
}


void Sorting::parallelQuickSort(int nums[], int length, int threadNum)
{
	parallel_quick_sort(nums, 0, length - 1, 0, threadNum);
}

void Sorting::parallel_quick_sort(int* nums, int low, int high, int threadDeepth, int maxNum) {
	std::thread::id tid = std::this_thread::get_id();
	cout << "thread id=" << tid << "start." <<"thread_deepth =" <<threadDeepth<< endl;
	if (low < high) {
		// ��Ѱ��׼���ݵ���ȷ����
		int mid = partition(nums, low, high);
		//std::string numsStr = RandUtils::intArrToStr(nums, 10);
		//RandUtils::print(nums, 10);
		if (threadDeepth < maxNum) {
			//����߳���
			vector<thread> vt;
			vt.push_back(thread(&Sorting::parallel_quick_sort,this, nums, low, mid - 1, threadDeepth + 1, maxNum));
			vt.push_back(thread(&Sorting::parallel_quick_sort,this, nums, mid + 1, high, threadDeepth + 1, maxNum));
			for (int i = 0; i < vt.size(); i++) {
				vt[i].join();
			}
		}
		else {
			quick_sort(nums, low, mid - 1);
			quick_sort(nums, mid + 1, high);
		}
	}
	cout << "thread id=" << tid << " end." << endl;
}




int Sorting::partition(int nums[], int low, int high) {
	// ��׼����
	int temp = nums[low];
	while (low < high) {
		// ����β��Ԫ�ش��ڵ��ڻ�׼����ʱ,��ǰŲ��highָ��
		while (low < high && nums[high] >= temp) {
			high--;
		}
		// �����βԪ��С��tmp��,��Ҫ���丳ֵ��low
		nums[low] = nums[high];
		// ������Ԫ��С�ڵ���tmpʱ,��ǰŲ��lowָ��
		while (low < high && nums[low] <= temp) {
			low++;
		}
		// ������Ԫ�ش���tmpʱ,��Ҫ���丳ֵ��high
		nums[high] = nums[low];
	}
	// ����ѭ��ʱlow��high���,��ʱ��low��high����tmp����ȷ����λ��
	// lowλ�õ�ֵ������tmp,������Ҫ��tmp��ֵ��arr[low]
	nums[low] = temp;
	return low;
}

void Sorting::heapAdjust(int* a, int i, int size)  //������ 
{
	int lchild = 2 * i + 1;       //i�����ӽڵ����  
	int rchild = 2 * i + 2;     //i���Һ��ӽڵ���� 
	int max = i;            //��ʱ���� ,����
	if (i <= size / 2)          //���i����Ҷ�ڵ�Ͳ��ý��е���    
	{
		if (lchild <= size && a[lchild] > a[max])
		{
			max = lchild;
		}
		if (rchild <= size && a[rchild] > a[max])
		{
			max = rchild;
		}
		if (max != i)
		{
			swap(a[i], a[max]);
			heapAdjust(a, max, size);    //�������֮����maxΪ���ڵ���������Ƕ�        
		}
	}
}

void Sorting::buildHeap(int* a, int size)    //������
{
	for (int i= size / 2; i >= 0; i--)    //��Ҷ�ڵ�������ֵΪsize/2    
	{
		heapAdjust(a, i, size);
	}
}

//������
void Sorting::heapSort(int* a, int length)    
{
	buildHeap(a, length-1);
	for (int i = length -1; i >= 1; i--)
	{
		//cout<<a[0]<<" ";        
		swap(a[0], a[i]);           //�����Ѷ������һ��Ԫ�أ���ÿ�ν�ʣ��Ԫ���е�����߷ŵ������ 
		buildHeap(a, i - 1);        //������Ԫ�����½���Ϊ�󶥶�         
		heapAdjust(a, 0, i - 1);      //���µ����Ѷ��ڵ��Ϊ�󶥶�   
	}
}

