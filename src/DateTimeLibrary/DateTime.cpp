#include "DateTime.h"

std::string Date::toString(){
    std::string str;
    str.append(std::to_string(m_month)).append("-").append(std::to_string(m_day)).append("-").append(std::to_string(m_year));
    return str;
}