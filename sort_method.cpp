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

//基数排序,计数排序（桶思想）

//计数排序（适用于排序数列是连续数字的情况）
void count_sort(int data[], int len)
{
	int min = data[0];
	int max = data[0];
	//遍历排序数组得到最大值和最小值
	for (int i = 0; i < len; i++)
	{
		if (min > data[i])
			min = data[i];
		if (max < data[i])
			max = data[i];
	}
//	cout << max << endl << min << endl;

	int  *help = new int [max - min + 1] ();  //一定要注意这边的初始化，不显示使用（）初始化为0的话，可能默认初始化为负数，导致了后面程序的错误。
	//统计频率
	for (int j = 0; j < len; j++)
	{
//		cout << help[0] << endl;
//		cout << help[1] << endl;
		help[data[j] - min] = help[data[j] - min]+1;
//		cout << help[data[j] - min] << endl;
	}
//	cout << help[0] << endl << help[1] << endl;

	int index = 0;
	for (int k = 0; k < max - min + 1; k++)
	{
		while (help[k]--)
		{
			data[index++] = k + min;
		}
	}
	for (int l = 0; l < len; l++)
	{
		cout << data[l] << endl;
	}
	delete[] help;
}

//基数排序
int maxbit(int data[], int n) 
{
    int d = 1; //保存最大的位数
    int p = 10;
    for(int i = 0; i < n; ++i)
    {
        while(data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;
}
void radixsort(int data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int *tmp = new int [n]();
    int count[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
	delete[] tmp;
    }
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


每一次排序之后都能确定至少一个元素位置的排序方法包括：

1.选择排序：每次将最大的数放到最后。所以最大的数排一次序后位置就确定了。

2.冒泡排序：同选择排序。每一次排序最大的值位置确定。

3.快排：每一次排序pivot的位置确定。

4.堆排序：每一次排序时，都是将堆顶的元素和最后一个节点互换，然后调整堆，再将堆大小减1。所以每一次排序堆顶元素确定。

不能至少确定一个元素的位置的方法包括：
1.插入排序：不到最后一步求的都是相对位置。
2.shell排序：对简单插入排序的改进。不到最后一步，是无法确定每个元素位置的。

3.归并排序：局部有序，并不能确定任一元素在全局的位置。

4.基数排序，计数排序：利用桶排序的思路，不是基于比较的排序，也无法在一次排序中确定某个元素的位置。因为每一次排序都是整体处理。
