﻿//#include <iostream>
//#include <vector>
//using namespace std;
//class Sort
//{
//public:
//    static int Quick2(vector<int>& arr, int left, int right)
//    {
//        int key = arr[left];
//        while (left < right)
//        {
//            while (left < right && arr[right] >= key)
//                right--;
//            arr[left] = arr[right];
//            while (left < right && arr[left] < key)
//                left++;
//            arr[right] = arr[left];
//        }
//        arr[left] = key;
//        return left;
//    }
//    static int Quick1(vector<int>& arr, int left, int right)
//    {
//        // 优化：找一个中间值，防止单支树的情况
//        int key = arr[left];
//        int pos = left;
//        for (int i = left + 1; i <= right; i++)
//        {
//            if (key > arr[i])
//            {
//                pos++;
//                if (pos != i)
//                    swap(arr[i], arr[pos]);
//            }
//        }
//        swap(arr[left], arr[pos]);
//        return pos;
//    }
//    static void QuickSort(vector<int>& arr, int left, int right)
//    {
//        // 优化：数据量较小时使用直接插入排序
//        if (left >= right)
//            return;
//        int pos = Quick1(arr, left, right - 1);
//        QuickSort(arr, left, pos);
//        QuickSort(arr, pos + 1, right);
//    }
//};
//int main()
//{
//    vector<int> arr = { 4,5,1,6,2,7,3,8 };
//    Sort::QuickSort(arr, 0, arr.size());
//    return 0;
//}
//
#include <iostream>
#pragma warning(disable:4996)
using namespace std;
class String
{
public:
	String(const char* str = "")
	{
		if (str == nullptr)
			str = "";
		_capacity = _size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);
		printf("拷贝：%p\n", _str);
	}
	String(const String& s)
		: _str(new char[s._size + 1])
		, _size(s._size)
		, _capacity(s._capacity)
	{
		strcpy(_str, s._str);
		printf("拷贝构造：%p\n", _str);
	}
	// 移动构造
	String(String&& s)
	{
		printf("移动构造：s：%p，str：%p\n", s._str, _str);
		swap(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
	}
	~String()
	{
		if (_str)
		{
			printf("析构：%p\n", _str);
			delete[] _str;
			_size = _capacity = 0;
			_str = nullptr;
		}
	}
	// 现代法
	String& operator=(String s)
	{
		printf("赋值重载：s：%p，str：%p\n", s._str, _str);
		swap(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}
	// 移动赋值
	String& operator=(String&& s)
	{
		printf("移动赋值：s：%p，str：%p\n", s._str, _str);
		swap(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
};


String Test(String s)
{
	return s;
}
String Test2()
{
	String s("oo");
	return s;
}
//int main()
//{
//	String s1;
//	String s2("qwer");
//	s1 = s2;					// 赋值重载
//	
//	String s3 = String("op");	// 构造一个匿名对象并执行赋值重载 
//	String s4 = Test2();		// 
//}
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		string str;
		cin >> str;
		int ans = 0;
		// 1.每次都要判断是否结束，并且还有一次判断首部%
		ans += str.size() + 1;
		ans += str.size() + 1;
		int i = 0;
		if (str[i] == '%')
			++i;
		for (; i < str.size(); ++i)
		{
			++ans;
			if (str[i] == 's')
				ans += 1;
			else if (str[i] == 'd')
				ans += 2;
			else if (str[i] == 'u')
				ans += 3;
			else if (str[i] == 'p')
				ans += 4;
			else if (str[i] == 'f')
				ans += 5;
			else if (str[i] >= '0' && str[i] <= '9')
				ans += 6;
			else if (str[i] == '%')
				ans += 7;
		}
		cout << ans << endl;
	}
	return 0;
}