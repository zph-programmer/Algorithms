#include "Sorting.h"
#include "iostream"
#include "RandUtils.h"

using namespace std;



//��������
void Sorting :: quickSort(int nums[],int length) {
	//sizeof(nums)/sizeof(nums[0]); �����ָ��Ͳ������ˣ�����length
	quick_sort(nums, 0, length-1);
}

void Sorting :: quick_sort(int nums[], int low, int high) {

	if (low < high) {
		// ��Ѱ��׼���ݵ���ȷ����
		int mid = partition(nums, low, high);
		//std::string numsStr = RandUtils::intArrToStr(nums, 10);
		//RandUtils::print(nums, 10);
		quick_sort(nums, low, mid - 1);
		quick_sort(nums,  mid + 1, high);
	
	}
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