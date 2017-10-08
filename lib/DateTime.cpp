#include "DateTime.h"

std::string Time::toString()
{
	std::string str;
	str.append(std::to_string(m_hrs)).append(":").append(std::to_string(m_mins)).append(":").append(std::to_string(m_secs));
	return str;	
}