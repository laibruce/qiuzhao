#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//冒泡排序  稳定
void bubble_sort(int a[], int len)
{
	int tmp;
	for (int i = 0; i < len - 1; i++)
	{
		bool isExchange = 0;  //改进算法，设置标识识别是否有交换，没交换的话说明数组已经有序，不需要再经过后面的循环对比！！！
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (a[j + 1] < a[j])
			{
				tmp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = tmp;
				isExchange = 1;
			}
		}
		if (isExchange == 0)
			return;
	}
}

//选择排序 稳定
//不存储下标，每次对比每次交换，简单版本，效率较低
void select_sort(int a[], int len)
{
	int i, j, temp;
	for (i = 0; i<len; i++)
	{
		for (j = i + 1; j<len; j++)
		{
			if (a[i]>a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

//每趟循环存储最小值的下标再交换（比较优化）
void select_sort2(int a[], int len)
{
	int i, j, min, k; //min保存最小数，k记录最小数的位置
	for (i = 0; i<len; i++)
	{
		min = a[i];
		k = i;
		for (j = i + 1; j<len; j++)
		{
			if (a[j]<min)
			{
				min = a[j];
				k = j;
			}
		}
		a[k] = a[i];  //a[k]为最小值，已由min保存
		a[i] = min;
	}
}

//插入排序 稳定
void insert_sort(int a[], int len)
{
	int i = 0, j = 0, temp = 0;
	for (i = 1; i<len; i++)
	{
		temp = a[i];
		for (j = i - 1; j >= 0 && temp<a[j]; j--)
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}

//希尔排序  不稳定
void shell_sort(int a[], int n)
{
	int i, j, gap;   //gap为增量，一般设置为gap/2或gap/2+1变化
	for (gap = n/2; gap > 0; gap/=2)
	{
		for (i = 0; i < gap; i++)
		{
			//以下为插入排序
			for (j = i + gap; j < n; j += gap)
			{
				if (a[j] < a[j - gap])
				{
					int tmp = a[j];
					int k = j - gap;
					while (k >= 0 && a[k] > tmp)
					{
						a[k + gap] = a[k];
						k -= gap;
					}
					a[k + gap] = tmp;
				}
			}
		}
		
	}
}

void shellsort2(int a[], int n)
{
	int j, gap;

	for (gap = n / 2; gap > 0; gap /= 2)
		for (j = gap; j < n; j++)   //从数组第gap个元素开始
			if (a[j] < a[j - gap])  //每个元素与自己组内的数据进行直接插入排序      
			{
				int temp = a[j];
				int k = j - gap;
				while (k >= 0 && a[k] > temp)
				{
					a[k + gap] = a[k];
					k -= gap;
				}
				a[k + gap] = temp;
			}
}

void shellsort3(int a[], int n)
{
       int i, j, gap;

       for (gap = n / 2; gap > 0; gap /= 2)
              for (i = gap; i < n; i++)
                     for (j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
                            swap(a[j], a[j + gap]);
}

//堆排序  不稳定
//void swap(int *a, int *b)
//{
//	int tmp = *a;
//	*a = *b;
//	*b = tmp;
//}

void heap_adjust(int arr[], int len, int index)
{
	int left = 2 * index + 1;  //左孩子节点
	int right = 2 * index + 2; //右孩子节点
	int maxIdx = index;
	if (left < len && arr[left] > arr[maxIdx])
		maxIdx = left;
	if (right < len && arr[right] > arr[maxIdx])
		maxIdx = right;
	if (maxIdx != index)
	{
		swap(arr[maxIdx], arr[index]);
		heap_adjust(arr, len, maxIdx);
	}
}
void heap_sort(int arr[], int size)
{
	//构建堆
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		heap_adjust(arr, size, i); // 对每一个非叶结点进行堆调整(从最后一个非叶结点开始)
	}
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);      // 将当前最大的放置到数组末尾
		heap_adjust(arr, i, 0);    // 将未完成排序的部分继续进行堆排序
	}
}

//归并排序  稳定
//递归实现
//1. 申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列
//2. 设定两个指针，最初位置分别为两个已经排序序列的起始位置
//3. 比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置
//4. 重复步骤3直到某一指针到达序列尾
//5. 将另一序列剩下的所有元素直接复制到合并序列尾
//6. 将最终结果写回原数组
//Tips:递归形式的算法在形式上较简洁，但实用性很差。
/*该函数将数组下标范围[l1,r1]和[l2,r2]的有序序列合并成一个有序序列*/
void merge(vector<int>& nums, int l1, int r1, int l2, int r2) {
	int i = l1;                                               //左半部分起始位置
	int j = l2;                                               //右半部分起始位置
	int n = (r1 - l1 + 1) + (r2 - l2 + 1);                    //要合并的元素个数
	vector<int> temp(n);                                      //辅助数组
	int k = 0;	                                          //辅助数组其起始位置
	while (i <= r1&&j <= r2) {                                //挑选两部分中最小的元素放入辅助数组中
		if (nums[i] < nums[j])
			temp[k++] = nums[i++];
		else
			temp[k++] = nums[j++];
	}
	//如果还有剩余，直接放入到辅助数组中
	while (i <= r1)
		temp[k++] = nums[i++];
	while (j <= r2)
		temp[k++] = nums[j++];
	//更新原始数组元素
	for (int i = 0; i < n; i++)
	{
		nums[l1 + i] = temp[i];
	}
}

/*二路归并排序（递归实现）*/
void MergeSort(vector<int>& nums, int start, int end) {
	if (start < end) {
		int mid = (start + end) >> 1;				//分割序列
		MergeSort(nums, start, mid);				//对序列左半部分进行规并排序
		MergeSort(nums, mid + 1, end);				//对序列右半部分进行规并排序
		merge(nums, start, mid, mid + 1, end);                  //合并已经有序的两个序列
	}
}

/*二路归并排序（迭代实现）*/
void MergeSort1(vector<int>& nums, int start, int end)
{
	int n = nums.size();
	if (start < end) {
		//step为组内元素个数，step/2为左子区间元素个数
		for (int step = 2; step / 2 <n; step *= 2) {
			//每step个元素一组，组内前step/2和后step/2个元素进行合并
			for (int i = 0; i < n; i += step) {
				int mid = i + step / 2 - 1;					//左子区间元素个数为step/2
				if (mid + 1<n)							//右子区间存在元素个数则合并
					//左子区间为[i,mid]，右子区间为[mid+1, min(i+step-1, n-1)]
					merge(nums, i, mid, mid + 1, min(i + step - 1, n - 1));
			}
		}
	}
}

//快速排序 挖坑法
void QuickSort(int iArray[], int left, int right)
{
	//快速排序之前先判断一下当前待排序数组元素个数是不是大于1 否则就没有必要排序
	if (left >= right)
	{
		//直接退出排序代码  没有必要进行排序了
		return;
	}

	//开始进行快排算法
	//首先我们先保存left索引对应的数据  当前数据作为切割数组的轴
	int piovt = iArray[left]; //把值存储在piovt变量，相应的位置变为“坑”

	//定义临时变量保存数组2端的索引
	int leftIndex = left;
	int rightIndex = right;

	while (leftIndex < rightIndex)
	{
		//现在我们通过循环从右边开始搜索一个比轴值小的数据
		while (leftIndex < rightIndex)
		{
			//如果右边的数大于当前的参数轴值
			if (piovt <= iArray[rightIndex])
			{
				//右端索引指示器左移
				rightIndex--;
			}
			else
			{
				//说明我们右端出现比轴值更大的数据
				//这个时候我们就可以把这个更大的数据填充到索引轴索引对应的地方
				iArray[leftIndex] = iArray[rightIndex];
				leftIndex++;
				//我们需要跳出循环了当前工作完毕
				break;
			}
		}

		//从左边开始搜索一个比轴值更大的数填写上次留下的坑
		while (leftIndex < rightIndex)
		{
			//如果左边的数据小于轴值 我们索引指示器就往右走
			if (piovt >= iArray[leftIndex])
			{
				leftIndex++;
			}
			else
			{
				//说明我们在左端找到了比轴值更大的数据
				iArray[rightIndex] = iArray[leftIndex];
				rightIndex--;
				break;
			}
		}
	}

	iArray[leftIndex] = piovt;

	QuickSort(iArray, left, leftIndex - 1);
	QuickSort(iArray, rightIndex + 1, right);
}

#include <time.h>
//随机快排，注意Partion函数的实现方法与上面是不同的 
int Partition(int data[], int length, int start, int end)
{
	if (data == NULL || length <= 0 || start < 0 || end >= length)
		throw new std::exception("Invalid Parameters");
	srand(unsigned(time(NULL)));  //srand()函数产生随机数种子，用系统时间当参数确保产生的随机种子不一样
	int index = rand() % (end - start + 1) + start;
	swap(data[index], data[end]);

	int small = start - 1;
	for (index = start; index < end; ++index)
	{
		if (data[index] < data[end])
		{
			++small;
			if (small != index)
				swap(data[index], data[small]);   //index-small的差值可以表示前面积累的data[index]>data[end]的个数
													//index表示找到比data[end]小的下标，而其前面的都是比data[end]大的数,当找到时直接把这个数与data[small]交换
													//data[small]一定是比data[end]大的数
		}
	}
	++small;
	swap(data[small], data[end]);
	return small;
}
void quick_sort(int data[], int length, int start, int end)
{
	if (start == end)
		return;
	int index = Partition(data, length, start, end);
	if (index > start)
		quick_sort(data, length, start, index - 1);
	if (index < end)
		quick_sort(data, length, index + 1, end);
}

int main()
{
	int data[6] = { 6, 5, 4, 3, 2, 1 };
	quick_sort(data, 6, 0, 5);
	for (auto a : data)
	{
		cout << a << " ";
	}
	system("pause");
	return 0;
}
