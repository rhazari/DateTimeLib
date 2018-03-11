#include "gtest/gtest.h"
#include "DateTimeTest.h"
#include "DateTime.h"

DateTimeTest::DateTimeTest() {}

DateTimeTest::~DateTimeTest() {};

void DateTimeTest::SetUp() {};

void DateTimeTest::TearDown() {};

//// return type - vector<KString> {Day, Month, Date, Hour, Minute, Seconds, Year}
//std::vector<KString> tokenizeDateTimeString(std::string _dateTime)
//{
//    auto _vec = tokenize(_dateTime, " ");
//    if (_vec.size() == 6)
//        _vec.erase(_vec.begin() + 2);
//    auto _time = tokenize(_vec[4], ":");
//    _vec.erase(_vec.begin() + 4);
//    _vec.insert(_vec.begin() + 4, _time.begin(), _time.end());
//    return _vec;
//}

class DateTimeProtectedHelperClass : public DateTime
{
public:
    DateTimeProtectedHelperClass(const DateTime& obj) : DateTime(obj)
    {
    }

    time_t getEpochTime()
    {
        return m_sinceEpoch;
    }

    std::tm gettm()
    {
        return m_tm;
    }

    std::string tz()
    {
        std::stringstream ss;
        ss << std::put_time(&m_tm, "%z");
        return ss.str();
    }
};

TEST(DateTime, DateTimeObject)
{
    // Date Object
    {
        DateTime dt({9, 7, 2017});
        std::cout<<dt.toString()<<"\n";
        auto _timeZone = DateTimeProtectedHelperClass(dt).tz();
        EXPECT_EQ(dt.toString(), "2017-09-07T01:00:00" + _timeZone);
    }
    // Date Time Object
    {
        DateTime dt({9, 7, 2017}, {15, 11, 10});
        auto _timeZone = DateTimeProtectedHelperClass(dt).tz();
        EXPECT_EQ(dt.toString(), "2017-09-07T15:11:10" + _timeZone);
    }
}

TEST(DateTime, DateTimeObjectConstructorwithInvalidValues)
{
    // Invalid Month
    {
        EXPECT_ANY_THROW(DateTime dt({13, 7, 2017}));
        EXPECT_ANY_THROW(DateTime dt({-3, 7, 2017}));
    }
    // Invalid Day
    {
        EXPECT_ANY_THROW(DateTime dt({7, 32, 2017}));
        EXPECT_ANY_THROW(DateTime dt({7, -2, 2017}));
    }
    // Invalid Year
    {
        // EXPECT_ANY_THROW(DateTime dt({7, 17, 1899}));
        // EXPECT_ANY_THROW(DateTime dt({7, 17, -2017}));
    }
    // Invalid Hours
    {
        EXPECT_ANY_THROW(DateTime dt({9, 7, 2017}, {24, 11, 10}));
        EXPECT_ANY_THROW(DateTime dt({9, 7, 2017}, {-1, 11, 10}));
    }
    // Invalid Minutes
    {
        EXPECT_ANY_THROW(DateTime dt({9, 7, 2017}, {15, 60, 10}));
        EXPECT_ANY_THROW(DateTime dt({9, 7, 2017}, {15, -1, 10}));
    }
    // Invalid Seconds
    {
        EXPECT_ANY_THROW(DateTime dt({9, 7, 2017}, {15, 11, 61}));
        EXPECT_ANY_THROW(DateTime dt({9, 7, 2017}, {-5, 11, -1}));
    }
}

TEST(DateTime, DateTimeObjectCopyConstructor)
{
    // Date Object
    {
        DateTime dt({9, 7, 2017});
        DateTime dt1(dt);
        EXPECT_EQ(dt1, dt);
    }
    // Date Time Object
    {
        DateTime dt({9, 7, 2017}, {15, 11, 10});
        DateTime dt1(dt);
        EXPECT_EQ(dt1, dt);
    }
}

TEST(DateTime, DateTimeObjectCopyAssignment)
{
    // Date Object
    {
        DateTime dt({9, 7, 2017});
        DateTime dt1 = dt;
        EXPECT_EQ(dt1, dt);
    }
    // Date Time Object
    {
        DateTime dt({9, 7, 2017}, {15, 11, 10});
        DateTime dt1 = dt;
        EXPECT_EQ(dt1, dt);
    }
}

TEST(DateTime, operators)
{
    // Operator ==
    {
        DateTime dt1({9, 7, 2017}, {15, 11, 10});
        DateTime dt2({9, 7, 2017}, {15, 11, 10});
        EXPECT_EQ(dt1, dt2);
    }
    // Operator !=
    {
        DateTime dt1({9, 7, 2017}, {15, 11, 10});
        DateTime dt2 = DateTime::currentLocalTime();
        EXPECT_NE(dt1, dt2);
    }
    // Operator < & >
    {
        DateTime dt1({9, 7, 2017}, {15, 11, 10});
        DateTime dt2({9, 7, 2017}, {15, 11, 11});
        EXPECT_TRUE(dt1 < dt2);
        EXPECT_FALSE(dt1 > dt2);
    }
    // Operator -
    {
        DateTime dt1({9, 7, 2017}, {15, 11, 15});
        DateTime dt2({9, 7, 2017}, {15, 11, 10});
        EXPECT_EQ(dt1 - dt2, 5);

        DateTime dt3({9, 9, 2017}, {15, 11, 10});
        DateTime dt4({9, 7, 2017}, {15, 11, 10});
        EXPECT_EQ(dt3 - dt4, 2 * 24 * 60 * 60);
    }
}

TEST(DateTime, DateObject)
{
    DateTime dt({9, 7, 2017}, {15, 11, 10});
    EXPECT_EQ(dt.getDate().toString(), "9-7-2017");
}

TEST(DateTime, TimeObject)
{
    DateTime dt({9, 7, 2017}, {15, 11, 10});
    EXPECT_EQ(dt.getTime().toString(), "15:11:10");
}

//TEST(DateTime, currentLocalTime)
//{
//    auto dt = DateTime::currentLocalTime();
//    time_t t = time(nullptr);
//    std::tm tm = *std::localtime(&t);
//    std::stringstream ss;
//    ss << std::put_time(&tm, "%a %b %d %Y %T");
//    auto v1 = tokenizeDateTimeString(ss.str());
//    auto v2 = tokenizeDateTimeString(dt.toString("%a %b %d %Y %T"));
//    EXPECT_EQ(v1[0], v2[0]);
//    EXPECT_EQ(v1[1], v2[1]);
//    EXPECT_EQ(v1[2], v2[2]);
//    EXPECT_EQ(v1[3], v2[3]);
//    EXPECT_EQ(v1[4], v2[4]);
//    EXPECT_EQ(v1[5], v2[5]);
//}

//TEST(DateTime, currentUTCTime)
//{
//    auto dt = DateTime::currentUTCTime();
//    time_t t = time(nullptr);
//    std::tm tm = *std::gmtime(&t);
//    std::stringstream ss;
//    ss << std::put_time(&tm, "%a %b %d %Y %T");
//    auto v1 = tokenizeDateTimeString(ss.str());
//    auto v2 = tokenizeDateTimeString(dt.toString("%a %b %d %Y %T"));
//    EXPECT_EQ(v1[0], v2[0]);
//    EXPECT_EQ(v1[1], v2[1]);
//    EXPECT_EQ(v1[2], v2[2]);
//    EXPECT_EQ(v1[3], v2[3]);
//    EXPECT_EQ(v1[4], v2[4]);
//    EXPECT_EQ(v1[5], v2[5]);
//}

TEST(DateTime, toString)
{
    DateTime dt({9, 7, 2017}, {15, 11, 10});
    auto _timeZone = DateTimeProtectedHelperClass(dt).tz();

    EXPECT_EQ(dt.toString(), "2017-09-07T15:11:10" + _timeZone);

    EXPECT_EQ(dt.toString("%Y-%m-%d %T"), "2017-09-07 15:11:10");

    EXPECT_EQ(dt.toString("%Y-%m-%d %I:%M:%S %p"), "2017-09-07 03:11:10 PM");

    EXPECT_EQ(dt.toString("%F %T"), "2017-09-07 15:11:10");
}

TEST(DateTime, fromString)
{
    auto dt = DateTime::fromString("2017-09-07T15:11:10");
    auto _timeZone = DateTimeProtectedHelperClass(dt).tz();

    EXPECT_EQ(dt.toString(), "2017-09-07T15:11:10" + _timeZone);

    dt = DateTime::fromString("Sep 07 2017 15:11:10", "%b %d %Y %T");
    EXPECT_EQ(dt.toString(), "2017-09-07T15:11:10" + _timeZone);
}

TEST(DateTime, addSeconds)
{
    DateTime dt({9, 7, 2017}, {15, 11, 10});
    auto _timeZone = DateTimeProtectedHelperClass(dt).tz();

    EXPECT_EQ(dt.toString(), "2017-09-07T15:11:10" + _timeZone);

    auto dt1 = dt.addSeconds(2000);
    EXPECT_EQ(dt1.toString(), "2017-09-07T15:44:30" + _timeZone);
}

TEST(DateTime, addDays)
{
    DateTime dt({9, 7, 2017}, {15, 11, 10});
    auto _timeZone = DateTimeProtectedHelperClass(dt).tz();

    EXPECT_EQ(dt.toString(), "2017-09-07T15:11:10" + _timeZone);

    auto dt1 = dt.addDays(10);
    EXPECT_EQ(dt1.toString(), "2017-09-17T15:11:10" + _timeZone);
}

TEST(DateTime, addMonths)
{
    DateTime dt({9, 7, 2017}, {15, 11, 10});
    auto _timeZone = DateTimeProtectedHelperClass(dt).tz();

    EXPECT_EQ(dt.toString(), "2017-09-07T15:11:10" + _timeZone);

    auto dt1 = dt.addMonths(10);
    EXPECT_EQ(dt1.toString(), "2018-07-07T15:11:10" + _timeZone);
}

TEST(DateTime, addYears)
{
    DateTime dt({9, 7, 2017}, {15, 11, 10});
    auto _timeZone = DateTimeProtectedHelperClass(dt).tz();

    EXPECT_EQ(dt.toString(), "2017-09-07T15:11:10" + _timeZone);

    auto dt1 = dt.addYears(3);
    EXPECT_EQ(dt1.toString(), "2020-09-07T15:11:10" + _timeZone);
}

TEST(DateTime, toUTCTime)
{
    DateTime dt({2, 7, 2017}, {15, 11, 10});
    auto _timeZone = DateTimeProtectedHelperClass(dt).tz();

    EXPECT_EQ(dt.toString(), "2017-02-07T14:11:10" + _timeZone);
    auto dt1 = dt.toUTC();

    auto _time = DateTimeProtectedHelperClass(dt).getEpochTime();
    // Converts time since epoch as std::time_t value into UTC time
    auto _tm = *gmtime(&_time);
    std::stringstream ss;
    ss << std::put_time(&_tm, "%a %b %d %Y %T");

    EXPECT_EQ(dt1.toString("%a %b %d %Y %T"), ss.str());
}

TEST(DateTime, timeZone)
{
    auto dt = DateTime::currentLocalTime();

    std::stringstream ss;
    auto _tm = DateTimeProtectedHelperClass(dt).gettm();
    ss << std::put_time(&_tm, "%z");

    EXPECT_EQ(dt.timeZone(), "GMT" + ss.str());
}

TEST(DateTime, offsetFromUtc)
{
    DateTime dt = DateTime::currentLocalTime();

    auto rawtime = DateTimeProtectedHelperClass(dt).getEpochTime();
    std::tm ptm = *gmtime(&rawtime);
    // Request that mktime() looksup dst in timezone database
    ptm.tm_isdst = -1;
    time_t gmt = mktime(&ptm);
    EXPECT_EQ(dt.offsetFromUtc(), (int)difftime(rawtime, gmt));
}