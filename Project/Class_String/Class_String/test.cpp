#include "My_String.h"

using namespace zwr;

void test_capacity()
{
	;
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
	test_capacity();
	return 0;
}