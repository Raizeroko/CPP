#include "My_String.h"

using namespace zwr;

void test_iostream()
{
	String s1;
	std::cin >> s1;
	std::cout << s1 << std::endl;
	std::cin >> s1;
	std::cout << s1 << std::endl;

}

void test_overloads()
{
	String s1 = "0123456789";
	String s2(s1);
	String s3 = s1;
	s2.pop_back();

	if (s1 > s2)
	{
		std::cout << "s1>s2" << std::endl;
	}
	if (s1 == s3)
	{
		std::cout << "s1==s3" << std::endl;
	}
	if (s2 < s1)
	{
		std::cout << "s2<s1" << std::endl;
	}
	if (s1 != s2)
	{
		std::cout << "s1!=s2" << std::endl;
	}
	if (s1 >= s3)
	{
		std::cout << "s1>=s3" << std::endl;
	}
	if (s2 <= s1)
	{
		std::cout << "s1<=s2" << std::endl;

	}
}

void test_modifiers()
{
	String s1("0123456789");
	String s2("6789");
	String s3("xxx");
	/*s1.push_back('0');
	std::cout << s1 << std::endl;
	s1.append("123456789");
	std::cout << s1 << std::endl;
	s1 += '0';
	std::cout << s1 << std::endl;
	s1 += "12345";
	std::cout << s1 << std::endl;
	s1 += s2;
	std::cout << s1 << std::endl;
	s1.assign(s2);
	std::cout << s1 << std::endl;
	s1.assign("0123456789");
	std::cout << s1 << std::endl;*/

	/*s1.insert(0, 'x');
	std::cout << s1 << std::endl;
	s1.insert(3, 'x');
	std::cout << s1 << std::endl;
	s1.insert(s1.size(), 'x');
	std::cout << s1 << std::endl;*/

	/*s1.insert(0, "xxx");
	std::cout << s1 << std::endl;
	s1.insert(5, "xxx");
	std::cout << s1 << std::endl;
	s1.insert(s1.size(), "xxx");
	std::cout << s1 << std::endl;*/

	/*s1.insert(0, s3);
	std::cout << s1 << std::endl;
	s1.insert(5, s3);
	std::cout << s1 << std::endl;
	s1.insert(s1.size(), s3);
	std::cout << s1 << std::endl;*/

	s1.pop_back();
	std::cout << s1 << std::endl;
	s1.erase(s1.size() - 1);
	std::cout << s1 << std::endl;
	s1.erase(3, 4);
	std::cout << s1 << std::endl;
	s1.erase(3);
	std::cout << s1 << std::endl;
	s1.erase(0);
	std::cout << s1 << std::endl;
	s1.assign("0123456789");
	s1.erase(0, 2);
	std::cout << s1 << std::endl;
	s1.erase(1, 2);
	std::cout << s1 << std::endl;



}

void test_iterator()
{
	String s1("hello world");
	auto it = s1.begin();
	while (it != s1.end())
	{
		std::cout << *it;
		++it;
	}
	std::cout << std::endl;

	for (auto e : s1)
	{
		std::cout << e << ' ';
	}
	std::cout << std::endl;

	for (size_t i = 0; i < s1.size(); i++)
	{
		std::cout << s1[i] ;
	}
	std::cout << std::endl;
}

void test_capacity()
{
	String s1("hello world");
	std::cout << "**" << s1.c_str() << "**" << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.length() << std::endl;

	s1.resize(3);
	std::cout << "**" << s1.c_str() << "**" << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.length() << std::endl;

	s1.resize(10);
	std::cout << "**" << s1.c_str() << "**" << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.length() << std::endl;

	s1.resize(20);
	std::cout << "**" << s1.c_str() << "**" << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.length() << std::endl;

	s1.resize(3, 'x');
	std::cout << "**" << s1.c_str() << "**" << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.length() << std::endl;

	s1.resize(10, 'x');
	std::cout << "**" << s1.c_str() << "**" << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.length() << std::endl;

	s1.resize(25, 'x');
	std::cout << "**" << s1.c_str() << "**" << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.length() << std::endl;

	if (s1.empty())
	{
		std::cout << "empty" << std::endl;
	}
	else
	{
		std::cout << "not empty" << std::endl;
	}
	s1.clear();
	std::cout << "**" << s1.c_str() << "**" << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.length() << std::endl;

	if (s1.empty())
	{
		std::cout << "empty" << std::endl;
	}
	else
	{
		std::cout << "not empty" << std::endl;
	}

}

void test_constructor()
{
	String s1;						
	String s2("hello world");		
	String s3(s2);				
	String s4(s2, 0, 100);
	String s5(s2, 0, 11);
	String s6(s2, 3, 4);

	std::cout << s1.c_str() << std::endl;
	std::cout << s2.c_str() << std::endl;
	std::cout << s3.c_str() << std::endl;
	std::cout << s4.c_str() << std::endl;
	std::cout << s5.c_str() << std::endl;
	std::cout << s6.c_str() << std::endl;


}

int main()
{
	//test_constructor();
	//test_capacity();
	//test_iterator();
	//test_modifiers();
	//test_iostream();
	test_overloads();
	return 0;
}