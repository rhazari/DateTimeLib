#include <iostream>
#include "DateTime.h"

int main(int argc, char *argv[])
{
	{
		DateTime dt({9, 7, 2017});
    	std::cout<<dt.toString()<<"\n";	
	}
	{
		DateTime dt({9, 7, 2017}, {15, 11, 10});
		std::cout<<dt.toString()<<"\n";	
	}
    return 0;
}