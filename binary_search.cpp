template <typename container>
int binary_search(container &array, int value)
{
	int res;
	auto begin = array.begin();
	auto end = array.end();
	auto mid = array.begin() + (end - begin) / 2;
	while (mid != end && *mid != value)
	{
		if (value < *mid)
			end = mid;
		else
			begin = mid + 1;
		mid = begin + (end - begin) / 2;  //mid是一个迭代器，不能直接转化为下标，必须通过下面的方法转化
	}
	res = distance(array.begin(), mid);//得到下标值
	//或者 res = mid - array.begin(); res = int(mid - array.begin());
	return res;
}

//二分查找的代码及其变种请仔细参考
//https://www.cnblogs.com/luoxn28/p/5767571.html
//二分查找注意事项 http://www.sohu.com/a/215243987_465914
//即注意使用 mid = left + (right - left)/2,而不要使用 mid = (left + right)/2,因为后者可能出现溢出问题。
