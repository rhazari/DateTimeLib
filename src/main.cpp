#include <iostream>
#include "DateTime.h"

int main(int argc, char *argv[])
{
	{
		DateTime dt({9, 7, 2015});
    	std::cout<<dt.toString()<<"\n";	
	}
	{
		DateTime dt({9, 7, 2015}, {15, 11, 10});
		std::cout<<dt.toString()<<"\n";	
	}
    return 0;
}