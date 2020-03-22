/*
 * date_time裤在格力高日历上的时间可以达到微妙级别的精度
 *
 * BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG主要影响构造函数最后一个参数的解释，
 * 若需要编写与时间分辨率无关的代码。可采用hours minutes seconds millisec micorosec
 *
 *
 * 编写时间精度无关的方法
 *			time_duration::tick_type my_millisec = time_duration::ticks_per_second() / 1000;
 */
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG  //定义纳秒精度	
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;


#include <iostream>
using namespace std;

/* 时间长度*/
void test_time_duration(){
	//创建1小时10分30秒1毫秒的时间
	//最后是以微妙为单位
	time_duration t1(1, 10, 30, 1000);	//1ms=1000微秒	// 超出的时间构造函数会进位
	
	//使用time_duration的子类实现hours minutes seconds millisec
	hours h1(1);				
	minutes m1(10);
	seconds s1(30);
	millisec ms(1);
	
	time_duration t2 = h1 + m1 + s1 + ms;
	assert(t1 == t2);			// t1 == t2
	
	//使用工厂函数	duration_from_string(const std::string &s)创建 time_durations对象
	time_duration t3 = duration_from_string("1:10:30:001"); // 最后是以微妙为单位
	assert(t3 == t1);	
	cout << t3.hours() <<"小时" << t3.minutes() << "分钟"
		 << t3.seconds() << "秒" << endl;
	
	cout << "总共" << t3.total_seconds() << "秒; "
		 << "总共" << t3.total_milliseconds() << "毫秒; "
		 << "总共" << t3.total_microseconds() << "微秒; "
		 << "微秒数" << t3.fractional_seconds() << endl; 
		
	//time_duration可以取负值
	hours h2(-10);
	assert(h2.is_negative());
	
	time_duration t4 = h2.invert_sign();	//invert_sign()改变符号求的信的时间长度
	assert(t4.hours() == 10);
	
	time_duration t5(not_a_date_time);		//特殊时间 与 日期相同
	assert(t5.is_special() && t5.is_not_a_date_time());
	
	//获取时间对象的字符串对象
	//to_simple_string()   to_iso_string()
	cout << to_simple_string(t3) << endl;	//01:10:30.001000
	cout << to_iso_string(t3) << endl;		//011030.001000
	
}

/* 时间精确度 */
void test_time_naosec(){
	
	time_duration t1(1, 10, 30, 1000);	
	cout << t1 << endl;	
	assert(t1.total_milliseconds() == t1.total_seconds() * 1000); //1000微妙 = 1ms
	cout << "纳秒数为" << t1.fractional_seconds() << endl;	//fractional_seconds()单位变成了纳秒
	
	assert(time_duration::unit()*1000*1000*1000 == seconds(1));//unit()返回最小单位
															   //最小单位根据宏会发生变化
	//判断 此时的时间的精度 是纳秒还是微妙
	assert(t1.resolution() == boost::date_time::nano);	
	assert(t1.num_fractional_digits() == 9);		//断言成立则为纳秒								
	
	//
	//自定义毫秒单位
	time_duration::tick_type my_millisec = time_duration::ticks_per_second() / 1000; 
	time_duration t2(1, 10, 30, 10*my_millisec);	//10毫秒即0.01微妙			
}


/* 时间点 = 日期+时间长度 */
/*
void test_time_point(){
	
	//创建时间点长度
	using namespace boost::gregorian;
	ptime p(date(2020,3,15), hours(1));	//2020,3,15,凌晨1小时
	
	//从字符串构造
	//time_from_string  from_iso_string()
	ptime p1 = time_from_string("2020-3-15 01:00:00");
	ptime p2 = from_iso_string("20200315T010000");
	assert(p == p1 && p==p2);
	
	
	//ptime也构造特殊时间
	ptime p3(not_a_date_time);
	assert(p3.is_not_a_date_time());
	
	//操作时间对象
	//date() -- 获取日期对象
	//time_of_day() -- 获取时间对象  + - / * 分开来做
	
	//转为字符串
	//to_simple_string()
	//to_iso_string()
	//to_iso_extends_string()
}*/


/* 时间区间 = 时间点 + 时间长度 */
void test_time_period(){
	ptime p1(date(2020, 3, 15), hours(12));
	time_period tp1(p1, hours(8));			//一个8小时的区间
	
}

/* 时间迭代器 */
void test_time_iterator(){
	ptime p(date(2020, 3, 15), hours(10));
	for(time_iterator t_iter(p, minutes(10)); t_iter < p+hours(1); ++t_iter){
		cout << *t_iter << endl;
	}
}

int main(int argc, char *argv[]) {
	//test_time_duration();
	//test_time_naosec();
	//test_time_point();
	test_time_iterator();
}