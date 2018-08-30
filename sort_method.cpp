#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//ð������  �ȶ�
void bubble_sort(int a[], int len)
{
	int tmp;
	for (int i = 0; i < len - 1; i++)
	{
		bool isExchange = 0;  //�Ľ��㷨�����ñ�ʶʶ���Ƿ��н�����û�����Ļ�˵�������Ѿ����򣬲���Ҫ�پ��������ѭ���Աȣ�����
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
		if (isExchange = 0)
			return;
	}
}

//ѡ������ �ȶ�
//���洢�±꣬ÿ�ζԱ�ÿ�ν������򵥰汾��Ч�ʽϵ�
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

//ÿ��ѭ���洢��Сֵ���±��ٽ������Ƚ��Ż���
void select_sort2(int a[], int len)
{
	int i, j, min, k; //min������С����k��¼��С����λ��
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
		a[k] = a[i];  //a[k]Ϊ��Сֵ������min����
		a[i] = min;
	}
}

//�������� �ȶ�
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

//ϣ������  ���ȶ�
void shell_sort(int a[], int n)
{
	int i, j, gap;   //gapΪ������һ������Ϊgap/2��gap/2+1�仯
	for (gap = n/2; gap > 0; gap/=2)
	{
		for (i = 0; i < gap; i++)
		{
			//����Ϊ��������
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
		for (j = gap; j < n; j++)   //�������gap��Ԫ�ؿ�ʼ
			if (a[j] < a[j - gap])  //ÿ��Ԫ�����Լ����ڵ����ݽ���ֱ�Ӳ�������      
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

//������  ���ȶ�
//void swap(int *a, int *b)
//{
//	int tmp = *a;
//	*a = *b;
//	*b = tmp;
//}

void heap_adjust(int arr[], int len, int index)
{
	int left = 2 * index + 1;  //���ӽڵ�
	int right = 2 * index + 2; //�Һ��ӽڵ�
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
	//������
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		heap_adjust(arr, size, i); // ��ÿһ����Ҷ�����жѵ���(�����һ����Ҷ��㿪ʼ)
	}
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);      // ����ǰ���ķ��õ�����ĩβ
		heap_adjust(arr, i, 0);    // ��δ�������Ĳ��ּ������ж�����
	}
}

//�鲢����  �ȶ�
//�ݹ�ʵ��
//1. ����ռ䣬ʹ���СΪ�����Ѿ���������֮�ͣ��ÿռ�������źϲ��������
//2. �趨����ָ�룬���λ�÷ֱ�Ϊ�����Ѿ��������е���ʼλ��
//3. �Ƚ�����ָ����ָ���Ԫ�أ�ѡ�����С��Ԫ�ط��뵽�ϲ��ռ䣬���ƶ�ָ�뵽��һλ��
//4. �ظ�����3ֱ��ĳһָ�뵽������β
//5. ����һ����ʣ�µ�����Ԫ��ֱ�Ӹ��Ƶ��ϲ�����β
//6. �����ս��д��ԭ����
//Tips:�ݹ���ʽ���㷨����ʽ�Ͻϼ�࣬��ʵ���Ժܲ
/*�ú����������±귶Χ[l1,r1]��[l2,r2]���������кϲ���һ����������*/
void merge(vector<int>& nums, int l1, int r1, int l2, int r2) {
	int i = l1;                                               //��벿����ʼλ��
	int j = l2;                                               //�Ұ벿����ʼλ��
	int n = (r1 - l1 + 1) + (r2 - l2 + 1);                    //Ҫ�ϲ���Ԫ�ظ���
	vector<int> temp(n);                                      //��������
	int k = 0;	                                          //������������ʼλ��
	while (i <= r1&&j <= r2) {                                //��ѡ����������С��Ԫ�ط��븨��������
		if (nums[i] < nums[j])
			temp[k++] = nums[i++];
		else
			temp[k++] = nums[j++];
	}
	//�������ʣ�ֱ࣬�ӷ��뵽����������
	while (i <= r1)
		temp[k++] = nums[i++];
	while (j <= r2)
		temp[k++] = nums[j++];
	//����ԭʼ����Ԫ��
	for (int i = 0; i < n; i++)
	{
		nums[l1 + i] = temp[i];
	}
}

/*��·�鲢���򣨵ݹ�ʵ�֣�*/
void MergeSort(vector<int>& nums, int start, int end) {
	if (start < end) {
		int mid = (start + end) >> 1;				//�ָ�����
		MergeSort(nums, start, mid);				//��������벿�ֽ��й沢����
		MergeSort(nums, mid + 1, end);				//�������Ұ벿�ֽ��й沢����
		merge(nums, start, mid, mid + 1, end);                  //�ϲ��Ѿ��������������
	}
}

/*��·�鲢���򣨵���ʵ�֣�*/
void MergeSort1(vector<int>& nums, int start, int end)
{
	int n = nums.size();
	if (start < end) {
		//stepΪ����Ԫ�ظ�����step/2Ϊ��������Ԫ�ظ���
		for (int step = 2; step / 2 <n; step *= 2) {
			//ÿstep��Ԫ��һ�飬����ǰstep/2�ͺ�step/2��Ԫ�ؽ��кϲ�
			for (int i = 0; i < n; i += step) {
				int mid = i + step / 2 - 1;					//��������Ԫ�ظ���Ϊstep/2
				if (mid + 1<n)							//�����������Ԫ�ظ�����ϲ�
					//��������Ϊ[i,mid]����������Ϊ[mid+1, min(i+step-1, n-1)]
					merge(nums, i, mid, mid + 1, min(i + step - 1, n - 1));
			}
		}
	}
}

//�������� �ڿӷ�
void QuickSort(int iArray[], int left, int right)
{
	//��������֮ǰ���ж�һ�µ�ǰ����������Ԫ�ظ����ǲ��Ǵ���1 �����û�б�Ҫ����
	if (left >= right)
	{
		//ֱ���˳��������  û�б�Ҫ����������
		return;
	}

	//��ʼ���п����㷨
	//���������ȱ���left������Ӧ������  ��ǰ������Ϊ�и��������
	int piovt = iArray[left]; //��ֵ�洢��piovt��������Ӧ��λ�ñ�Ϊ���ӡ�

	//������ʱ������������2�˵�����
	int leftIndex = left;
	int rightIndex = right;

	while (leftIndex < rightIndex)
	{
		//��������ͨ��ѭ�����ұ߿�ʼ����һ������ֵС������
		while (leftIndex < rightIndex)
		{
			//����ұߵ������ڵ�ǰ�Ĳ�����ֵ
			if (piovt <= iArray[rightIndex])
			{
				//�Ҷ�����ָʾ������
				rightIndex--;
			}
			else
			{
				//˵�������Ҷ˳��ֱ���ֵ���������
				//���ʱ�����ǾͿ��԰���������������䵽������������Ӧ�ĵط�
				iArray[leftIndex] = iArray[rightIndex];
				leftIndex++;
				//������Ҫ����ѭ���˵�ǰ�������
				break;
			}
		}

		//����߿�ʼ����һ������ֵ���������д�ϴ����µĿ�
		while (leftIndex < rightIndex)
		{
			//�����ߵ�����С����ֵ ��������ָʾ����������
			if (piovt >= iArray[leftIndex])
			{
				leftIndex++;
			}
			else
			{
				//˵������������ҵ��˱���ֵ���������
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
//������ţ�ע��Partion������ʵ�ַ����������ǲ�ͬ�� 
int Partition(int data[], int length, int start, int end)
{
	if (data == NULL || length <= 0 || start < 0 || end >= length)
		throw new std::exception("Invalid Parameters");
	srand(unsigned(time(NULL)));  //srand()����������������ӣ���ϵͳʱ�䵱����ȷ��������������Ӳ�һ��
	int index = rand() % (end - start + 1) + start;
	swap(data[index], data[end]);

	int small = start - 1;
	for (index = start; index < end; ++index)
	{
		if (data[index] < data[end])
		{
			++small;
			if (small != index)
				swap(data[index], data[small]);   //index-small�Ĳ�ֵ���Ա�ʾǰ����۵�data[index]>data[end]�ĸ���
													//index��ʾ�ҵ���data[end]С���±꣬����ǰ��Ķ��Ǳ�data[end]�����,���ҵ�ʱֱ�Ӱ��������data[small]����
													//data[small]һ���Ǳ�data[end]�����
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