#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<fstream>
#include<stack>
#include<queue>
#include<string>
#include<stdlib.h>
#include<string.h>
using namespace std;

class test
{
public:
	int a;
	test(int tmp) :a(tmp)
	{}
	test() :a(7)
	{}
	void* operator new(size_t x)
	{
		cout << "fuck";
		return ::operator new(x);
	}
};
// class String  //Éî¿½±´  
// {
// public:
// friend ostream& operator<<(ostream& out,const String& str)
// {
// out<<str.m_Pstr;
// return out;
// }
// String()
// :m_Pstr(new char('\0'))
// {
// }
// String(const char* str)
// :m_Pstr(new char[strlen(str)+1]) 
// {
// memset(m_Pstr,0,strlen(str)+1);
// if (NULL != str)
// memcpy(m_Pstr,(void*)str,strlen(str)+1);
// }
// String(const String& str)
// :m_Pstr(new char[strlen(str.m_Pstr)+1])
// {
// memset(m_Pstr,0,strlen(str.m_Pstr)+1);
// if (NULL != str.m_Pstr)
// memcpy((void*)m_Pstr,(void*)str.m_Pstr,strlen(str.m_Pstr)+1);
// }
// String& operator=(const String& str)
// {
// if(this != &str) 
// {
// String tmp(str); //ÇÉÃîµÄÀûÓÃ 
// std::swap(tmp.m_Pstr,m_Pstr);   
// }
// return *this;	
// }
// String& operator+(const String& str)
// {	
// if(strlen(str.m_Pstr) == 0)
// return *this;
// char* tmp = new char[strlen(m_Pstr)+strlen(str.m_Pstr)+1];
// memcpy(tmp,m_Pstr,strlen(m_Pstr)+1);
// strcat(tmp,str.m_Pstr);
// std::swap(tmp,m_Pstr);
// delete[] tmp;
// return *this;
// } 

// ~String()
// {
// delete[] m_Pstr;
// }

// char* m_Pstr;		
// };
class String //Ç³¿½±´ COW
{
public:
	friend ostream& operator<<(ostream& out, const String& str)
	{
		out << str.m_Pstr;
		return out;
	}
	String(const char* str = NULL)
		:m_Pstr(new (char[strlen(str) + 1 + 4]))
	{
		memset(m_Pstr, 0, strlen(str) + 5);
		m_Pstr += 4;
		getCount() = 1;
		if (NULL != str)
		{
			memcpy(m_Pstr, str, strlen(str) + 1);
		}
	}
	String(const String& str)
	{
		if (this != &str)
		{
			m_Pstr = str.m_Pstr;
			(getCount())++;
		}
	}
	const String& operator=(const String& str)
	{
		if (this == &str)
		{
			return *this;
		}
		++(*((int*)str.m_Pstr - 1));

		if( (--getCount()) <= 0)
			delete[] ((int*)m_Pstr - 1);
		m_Pstr = str.m_Pstr;  
		return str;
	}
	char& operator[](size_t pos)
	{
		if (getCount() <= 1)
			return m_Pstr[pos];

		char* tmp = (new char[strlen(m_Pstr) + 1 + 4]);

		getCount()--;

		memmove(tmp+4, m_Pstr, strlen(m_Pstr) + 5);
		(*(int*)tmp) = 1;
		tmp += 4;

		m_Pstr = tmp;
		return m_Pstr[pos];
	}
	~String()
	{
		if ((*(int*)m_Pstr) <= 1)
		{
			delete[] ((int*)m_Pstr-1);
		}
	}

	int& getCount()
	{
		return (*((int*)m_Pstr - 1));
	}
protected:
	char* m_Pstr;
};
int main()
{
	// ifstream in("in.txt");
	// ofstream out("out.txt");
	// int tmp = 0;
	// stack<int> s;
	// vector<int> v;
	// queue<int> q;

	// string str("123123");
	// v.resize(str.size());
	// copy(str.begin(),str.end(),v.begin());
	// for(auto&x :v)
	// {
	// cout<<x<<endl;
	// }
	// test* tmp = new test(1);
	// cout<<tmp->a;

	// test* pTest = new test[10];
	// cout<<pTest[2].a;
	// cout<<pTest[-1].a;
	// char* tmp = new char('\0');
	String a("123");
	String b("456");
	//cout<<a;
	a = b;
	//cout<<a;
	//a = a + b + a;
	cout << a;
	cout << a[1];
	cout << a;
	return 0;
}
