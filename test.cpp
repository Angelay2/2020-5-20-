#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#pragma warning(disable:4996)

using std::cout;
using std::endl;
using std::swap;
using std::string;

class String{
public:
	//string迭代器：原生指针
	typedef char* iterator;
	typedef const char* const_iterator;
	////无参构造：创建空字符串
	//String()
	//	:_str(new char[1]){
	//	*_str = '\0';
	//}

	//全缺省带参构造: 缺省值为空字符串
	String(const char* str = ""){
		_size = strlen(str);
		_str = new char[_size + 1];
		_capacity = _size;
		//拷贝输入字符串到对象的资源空间中
		strcpy(_str, str);
	}

	//拷贝构造:深拷贝 用一个已经存在的对象创建一个新的的对象, 开空间+内容拷贝
	/*String(const String& str)
	:_str(new char[str._capacity + 1])
	, _size(str._size)
	, _capacity(str._capacity){
	strcpy(_str, str._str);
	}*/

	//拷贝构造的现代写法 --> 代码复用 (推荐) 出错概率小
	String(const String& str)
		:_str(nullptr)
		, _capacity(0)
		, _size(0){
		String tmp(str._str);   // 创建临时对象式已经完成了开空间和内容拷贝, 
		Swap(tmp);  // 所以现在只需要进行交换即可
	}

	void Swap(String& str){
		swap(str._str, _str);
		swap(str._capacity, _capacity);
		swap(str._size, _size);
	}

	//String& operator=(const String& str){
	//	if (this != &str){
	//		// 释放原有资源
	//		delete[] _str;
	//		// 开新空间
	//		_str = new char[str._capacity + 1];
	//		// 拷贝字符串内容
	//		strcpy(_str, str._str);
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}

	//赋值运算符现代写法
	//第一种写法
	String& operator=(String str){
		Swap(str);
		return *this;
	}
	//第二种写法
	/*String& operator=(const String& str){
	String tmp(str);
	Swap(tmp);
	return *this;
	}*/

	char* c_str(){
		return _str;
	}

	~String(){
		if (_str){
			delete[] _str;
			_str = nullptr;
			_capacity = _size = 0;
		}
	}

	//遍历：1. operator[] + size(类似于数组的访问形式)   2. 迭代器  3. 范围for

	//[]方括号运算符重载: char ch = string[pos]
	//获取pos位置的字符
	//可读可写： 返回值类型为引用, 这样才会让operator接口变成可读可写
	// 返回值只能去读, 不能去修改, 传引用可以进行修改
	// 加了const就只读, 不加const可读可写
	char& operator[](size_t pos){
		if (pos < _size)
			return _str[pos];
	}
	size_t size(){
		return _size;
	}

	//迭代器： 可读可写 利用原生指针操作
	//迭代器区间：左闭右开 [begin, end]
	iterator begin(){
		//第一个元素的位置  开的空间的第一个位置
		return _str;
	}

	iterator end(){
		//最后一个元素的下一个位置
		return _str + _size;
	}

	//只读迭代器(const)  
	const_iterator begin() const{
		return _str;
	}

	const_iterator end() const{
		return _str + _size;
	}


private:
	char* _str;
	//_size: 有效字符的个数，不包含\0
	size_t _size;
	//_capacity: 能够存放最大有效字符的个数
	size_t _capacity;
};

void printString(const String& str){
	//迭代器遍历
	String::const_iterator it = str.begin();
	while (it != str.end()){
		cout << *it << " ";
		//const_iterator: 只读迭代器，不能修改指向位置的内容
		//*it = 'a';
		++it;
	}
	cout << endl;

	// 范围for, 左边是要遍历的字符, 右边是遍历的范围
	// 接收的变量必须是引用类型, 可以去修改元素本身, 如果是值的话, 需要先拷贝再遍历, 不能修改
	// 本身也是通过迭代器实现的, 借助迭代器
	for (auto& ch : str){
		cout << ch << " ";
		//ch = 'a';
	}
	cout << endl;
}

void test(){
	//string 无参构造创建了一个空字符串
	string str1;
	String str2;
	const char* ptr = str1.c_str();
	char* ptr2 = str2.c_str();
	//字符串指针输出的为字符串的内容，不是字符串的首地址，即输出需要解引用
	char* ptr3 = "123445";
	cout << ptr3 << endl;
	printf("%p\n", ptr3);
	cout << ptr << endl;
	cout << ptr2 << endl;
}

void test1(){
	char* ptr = "1234";
	string str1(ptr);
	String str2(ptr);
}

void test2(){
	String str("abc");
	String copy(str);
	String str2("123");
	str = str2;
}

void test3(){
	String str("0123456789");
	for (size_t i = 0; i < str.size(); ++i){
		cout << str.operator[](i) << " ";
		str[i] = 'a';
	}
	cout << endl;

	for (size_t i = 0; i < str.size(); ++i){
		cout << str[i] << " ";
	}
	cout << endl;
}

void test4(){
	String str("0123456789");
	String::iterator it = str.begin();
	while (it != str.end()){
		//迭代器解引用
		cout << *it << " ";
		*it = 'a';
		//迭代器移动
		++it;
	}
	cout << endl;

	it = str.begin();
	while (it != str.end()){
		//迭代器解引用
		cout << *it << " ";
		//迭代器移动
		++it;
	}
	cout << endl;

	String str2;
	it = str2.begin();
	while (it != str2.end()){
		//迭代器解引用
		cout << *it << " ";
		//迭代器移动
		++it;
	}
	cout << endl;


}

void test5(){
	String str("0123456789");
	printString(str);
}

void test6(){
	String str("0123456789");
	//范围for: 通过迭代器实现
	//         底层通过迭代器遍历元素
	for (const auto& ch : str){
		cout << ch << " ";
	}
	cout << endl;
}

int main(){
	//test();
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	//test6();

	system("pause");
	return 0;
}