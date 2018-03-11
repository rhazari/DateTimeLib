#pragma once
#include <assert.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <sstream>

class Time
{
    friend class DateTime;
    int m_hrs;
    int m_mins;
    int m_secs;

public:
    Time() : m_hrs(0), m_mins(0), m_secs(0)
    {
    }

    Time(int hrs, int mins, int secs) : m_hrs(hrs), m_mins(mins), m_secs(secs)
    {
    }

    std::string toString()
    {
        std::string str;
        str.append(std::to_string(m_hrs)).append(":").append(std::to_string(m_mins)).append(":").append(std::to_string(m_secs));
        return str; 
    }
};

class Date
{
    friend class DateTime;
    int m_day;
    int m_month;
    int m_year;

public:
    Date(int _month, int _day, int _year) : m_month(_month), m_day(_day), m_year(_year)
    {
    }

    std::string toString();
    // {
    //     std::string str;
    //     str.append(std::to_string(m_month)).append("-").append(std::to_string(m_day)).append("-").append(std::to_string(m_year));
    //     return str;
    // }
};

/**
* @class DateTime DateTime.h "Keysight/Cdm/Experimental/DateTime.h"
* @brief Class for creating a DateTime object
* @parameters Month, Day, Year, Hours, Minutes, Seconds
*/
class DateTime
{
protected:
    Date m_date;
    Time m_time;
    time_t m_sinceEpoch;
    std::tm m_tm;

public:
    DateTime(Date _date, Time _time = Time()) : m_date(_date), m_time(_time)
    {
        // Date
        m_tm.tm_mon = m_date.m_month - 1;
        m_tm.tm_mday = m_date.m_day;
        m_tm.tm_year = m_date.m_year - 1900;
        
        // Time
        m_tm.tm_hour = m_time.m_hrs;
        m_tm.tm_min = m_time.m_mins;
        m_tm.tm_sec = m_time.m_secs;
        m_sinceEpoch = std::mktime(&m_tm);
        
        if (m_tm.tm_mon != m_date.m_month - 1)
            throw std::runtime_error("Invalid month entry");
        if (m_tm.tm_mday != m_date.m_day)
            throw std::runtime_error("Invalid day entry");
        if (m_tm.tm_year != (m_date.m_year - 1900) )
            throw std::runtime_error("Invalid year entry");
        // if ( (m_tm.tm_hour - m_tm.tm_isdst) != m_time.m_hrs)
        //     throw std::runtime_error("Invalid hour entry");
        if (m_tm.tm_min != m_time.m_mins)
            throw std::runtime_error("Invalid minute entry");
        if (m_tm.tm_sec != m_time.m_secs)
            throw std::runtime_error("Invalid seconds entry");
        if (m_sinceEpoch == -1)
            throw std::runtime_error("Invalid Date Time value for the constructor");
    }

    DateTime(const DateTime&) = default;
    DateTime& operator=(const DateTime&) = default;

    std::string toString(std::string format = "%FT%T%z")
    {
        std::stringstream ss;
        ss << std::put_time(&m_tm, format.data());
        return ss.str();
    }

    Time getTime()
    {
        return m_time;
    }

    Date getDate()
    {
        return m_date;
    }

    DateTime addSeconds(int seconds)
    {
        std::tm tm = this->m_tm;
        tm.tm_sec += seconds;
        std::mktime(&tm);
        return DateTime({tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900}, {tm.tm_hour, tm.tm_min, tm.tm_sec});
    }

    DateTime addDays(int days)
    {
        return addSeconds(days * 24 * 60 * 60);
    }

    DateTime addMonths(int months)
    {
        std::tm tm = this->m_tm;
        tm.tm_mon += months;
        std::mktime(&tm);
        return DateTime({tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900}, {tm.tm_hour, tm.tm_min, tm.tm_sec});
    }

    DateTime addYears(int years)
    {
        std::tm tm = this->m_tm;
        tm.tm_year += years;
        std::mktime(&tm);
        return DateTime({tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900}, {tm.tm_hour, tm.tm_min, tm.tm_sec});
    }

    DateTime toUTC()
    {
        time_t temp_time_t = this->m_sinceEpoch;
        std::tm tm = *gmtime(&temp_time_t);
        return DateTime({tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900}, {tm.tm_hour, tm.tm_min, tm.tm_sec});
    }

    int offsetFromUtc()
    {
        time_t rawtime = this->m_sinceEpoch;
        struct tm ptm = *gmtime(&rawtime);
        // Request that mktime() looksup dst in timezone database
        ptm.tm_isdst = -1;
        time_t gmt = mktime(&ptm);
        return (int)difftime(rawtime, gmt);
    }

    std::string timeZone()
    {
        std::stringstream ss;
        ss << std::put_time(&m_tm, "%z");
        return "GMT" + ss.str();
    }

    static DateTime currentLocalTime()
    {
        std::time_t t = std::time(nullptr);
        std::tm tm = *localtime(&t);
        return DateTime({tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900}, {tm.tm_hour, tm.tm_min, tm.tm_sec});
    }

    static DateTime currentUTCTime()
    {
        std::time_t t = std::time(nullptr);
        std::tm tm = *gmtime(&t);
        return DateTime({tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900}, {tm.tm_hour, tm.tm_min, tm.tm_sec});
    }

    static DateTime fromString(std::string dateTime, std::string format = "%Y-%m-%dT%H:%M:%S%z")
    {
        std::tm tm;
        std::istringstream ss(dateTime);
        ss >> std::get_time(&tm, format.data());
        return DateTime({tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900}, {tm.tm_hour, tm.tm_min, tm.tm_sec});
    }

    // Operators
    bool operator==(DateTime rhs) const
    {
        return this->m_sinceEpoch == rhs.m_sinceEpoch;
    }

    bool operator!=(DateTime rhs) const
    {
        return this->m_sinceEpoch != rhs.m_sinceEpoch;
    }

    bool operator<(DateTime rhs) const
    {
        return this->m_sinceEpoch < rhs.m_sinceEpoch;
    }

    bool operator>(DateTime rhs) const
    {
        return this->m_sinceEpoch > rhs.m_sinceEpoch;
    }

    int operator-(DateTime rhs) const
    {
        return (int)(this->m_sinceEpoch - rhs.m_sinceEpoch);
    }
};