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
	//string��������ԭ��ָ��
	typedef char* iterator;
	typedef const char* const_iterator;
	////�޲ι��죺�������ַ���
	//String()
	//	:_str(new char[1]){
	//	*_str = '\0';
	//}

	//ȫȱʡ���ι���: ȱʡֵΪ���ַ���
	String(const char* str = ""){
		_size = strlen(str);
		_str = new char[_size + 1];
		_capacity = _size;
		//���������ַ������������Դ�ռ���
		strcpy(_str, str);
	}

	//��������:��� ��һ���Ѿ����ڵĶ��󴴽�һ���µĵĶ���, ���ռ�+���ݿ���
	/*String(const String& str)
	:_str(new char[str._capacity + 1])
	, _size(str._size)
	, _capacity(str._capacity){
	strcpy(_str, str._str);
	}*/

	//����������ִ�д�� --> ���븴�� (�Ƽ�) �������С
	String(const String& str)
		:_str(nullptr)
		, _capacity(0)
		, _size(0){
		String tmp(str._str);   // ������ʱ����ʽ�Ѿ�����˿��ռ�����ݿ���, 
		Swap(tmp);  // ��������ֻ��Ҫ���н�������
	}

	void Swap(String& str){
		swap(str._str, _str);
		swap(str._capacity, _capacity);
		swap(str._size, _size);
	}

	//String& operator=(const String& str){
	//	if (this != &str){
	//		// �ͷ�ԭ����Դ
	//		delete[] _str;
	//		// ���¿ռ�
	//		_str = new char[str._capacity + 1];
	//		// �����ַ�������
	//		strcpy(_str, str._str);
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}

	//��ֵ������ִ�д��
	//��һ��д��
	String& operator=(String str){
		Swap(str);
		return *this;
	}
	//�ڶ���д��
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

	//������1. operator[] + size(����������ķ�����ʽ)   2. ������  3. ��Χfor

	//[]���������������: char ch = string[pos]
	//��ȡposλ�õ��ַ�
	//�ɶ���д�� ����ֵ����Ϊ����, �����Ż���operator�ӿڱ�ɿɶ���д
	// ����ֵֻ��ȥ��, ����ȥ�޸�, �����ÿ��Խ����޸�
	// ����const��ֻ��, ����const�ɶ���д
	char& operator[](size_t pos){
		if (pos < _size)
			return _str[pos];
	}
	size_t size(){
		return _size;
	}

	//�������� �ɶ���д ����ԭ��ָ�����
	//���������䣺����ҿ� [begin, end]
	iterator begin(){
		//��һ��Ԫ�ص�λ��  ���Ŀռ�ĵ�һ��λ��
		return _str;
	}

	iterator end(){
		//���һ��Ԫ�ص���һ��λ��
		return _str + _size;
	}

	//ֻ��������(const)  
	const_iterator begin() const{
		return _str;
	}

	const_iterator end() const{
		return _str + _size;
	}


private:
	char* _str;
	//_size: ��Ч�ַ��ĸ�����������\0
	size_t _size;
	//_capacity: �ܹ���������Ч�ַ��ĸ���
	size_t _capacity;
};

void printString(const String& str){
	//����������
	String::const_iterator it = str.begin();
	while (it != str.end()){
		cout << *it << " ";
		//const_iterator: ֻ���������������޸�ָ��λ�õ�����
		//*it = 'a';
		++it;
	}
	cout << endl;

	// ��Χfor, �����Ҫ�������ַ�, �ұ��Ǳ����ķ�Χ
	// ���յı�����������������, ����ȥ�޸�Ԫ�ر���, �����ֵ�Ļ�, ��Ҫ�ȿ����ٱ���, �����޸�
	// ����Ҳ��ͨ��������ʵ�ֵ�, ����������
	for (auto& ch : str){
		cout << ch << " ";
		//ch = 'a';
	}
	cout << endl;
}

void test(){
	//string �޲ι��촴����һ�����ַ���
	string str1;
	String str2;
	const char* ptr = str1.c_str();
	char* ptr2 = str2.c_str();
	//�ַ���ָ�������Ϊ�ַ��������ݣ������ַ������׵�ַ���������Ҫ������
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
		//������������
		cout << *it << " ";
		*it = 'a';
		//�������ƶ�
		++it;
	}
	cout << endl;

	it = str.begin();
	while (it != str.end()){
		//������������
		cout << *it << " ";
		//�������ƶ�
		++it;
	}
	cout << endl;

	String str2;
	it = str2.begin();
	while (it != str2.end()){
		//������������
		cout << *it << " ";
		//�������ƶ�
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
	//��Χfor: ͨ��������ʵ��
	//         �ײ�ͨ������������Ԫ��
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