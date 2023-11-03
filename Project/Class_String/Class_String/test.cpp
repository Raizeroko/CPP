#include "My_String.h"

using namespace zwr;

void test_modifiers()
{
	;
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
	test_iterator();
	return 0;
}