/*
 * date是date_time库处理的核心类，使用32位整数作为内部存储，以 天 为单位
 *
 */

#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;


#include <iostream>
using namespace std;



void test_date(){
	
	//空构造函数创建无效日期
	date t;
	if(t.is_not_a_date()){
		cout << "empty construct func's date is  'is_not_a_date'\n"; 
	}
	
	//构造函数传入顺序为 年 月 日
	date t1(2020, 3, 14);
	date t2(2020, Mar, 14);
	date t3(t1);			// copy contruct
	assert(t1 == date(2020,3,14));
	assert(t1 == t3);

	//从字符串构造 -- from_string()  -- from_undelimited_string()
	/*date t4 = from_string("2020-03-14");
	date t5 = from_string("2020/03/14");
	date t6 = from_undelimited_string("20200314");
	assert(t4 == t1);
	assert(t5 == t1);
	assert(t6 == t1);*/
	
	//获取当前日期
	cout << day_clock::local_day() << endl;			// 结果依赖于操作系统时区限制
	cout << day_clock::universal_day() << endl;		// 2020-Mar-14
	
	
}

/*日期的获取*/
void get_date_data(){
		
	//成员函数 year() month() day() 获取年月日
	date d(2020, 3, 14);
	cout  << d.year() << "年 " << d.month() << "月 " << d.day() <<"日" << endl;
	
	//year_month_day获得年月日
	date::ymd_type ymd = d.year_month_day();
	assert(ymd.year == 2020);
	assert(ymd.month == 3);
	assert(ymd.day == 14);
	
	cout << "今天星期" << d.day_of_week() << endl;  //Sat
	//cout << "今天是当月的第" << d.day_of_month() << "天"<< endl;
	cout << "今天是当年的第" << d.day_of_year() << "天"<< endl;	// 74
	cout << "当月的最后一天" << d.end_of_month() <<endl;			// 2020-Mar-31
	
	cout << "所在周是当年周数的第" << d.week_number() << endl;		// 11
	
	// is_iniinty()  is_neg_infinty()  is_pos_infinty() is_not_a_date() is_special()
	
	
}

/*日期的输出*/
/*
void output_data()
{
	
	date t(2020, 3, 14);
	
	//to_simple_string();
	cout <<"to_simple_string" << to_simple_string(t) << endl;
	
	//to_iso_string();
	cout <<"to_iso_string" << to_iso_string(t) << endl;
	
	//to_iso_extended_string()
	cout <<"to_iso_extended_string" << to_iso_extended_string(t) << endl;
	
}*/

/*日期长度*/
void data_of_length(){
	
	//date_duration 以天为单位
	date_duration dd1(10);			// 10天
	date_duration dd2(-100);		// 前100天
	date_duration dd3(255);			// 后255天
	
	assert(dd1 > dd2 && dd1 < dd3);
	assert(dd1 + dd2 < dd3);
	assert((dd1+dd3).days() == 265);
	assert(dd3 / 5 == days(51));

	weeks wk(3);	// 3个星期			// 构造函数以7为单位
	assert(wk.days() == 21);
	
	months m(5);	// 5个月
	//cout << "5个月的天数为：" << m. << endl;
	
	years y(2);		// 2年
	
	months m2 = y + m;  //2年零5个月
	assert(m2.number_of_months() == 29);  // number_of_months 月数
	assert((y * 2).number_of_years() == 4);
}

/* 日期运算 */
void date_of_compute(){
	date d(2020, 3, 14);
	
	d += months(5);
	assert(d.month() == 8);
	
	d += days(10);
	assert(d.day() == 24);
	
	d += weeks(1);
	//cout << d.day() << endl;
	assert(d.day() == 31);
	
	date d2 = d + days(not_a_date_time);	// 正常日期加上特殊日期还是特殊日期
	assert(d2.is_not_a_date());
	
	d2 = date(neg_infin);
	days dd = d - d2;
	assert(dd.is_special() && !dd.is_negative());
	
}

/* 日期区间 */
void date_of_period(){
	//左闭右开
	//声明
	date_period d1(date(2020,2,1), date(2020, 2, 11));
	date_period d2(date(2020,2,1), days(10));
	date_period d3(date(2020,2,1), days(-10));
	date_period d4(date(2020,3,1), days(20));
	assert(d1 == d2);
	
	assert(d3.is_null());		// is_null() 日期区间无效 返回true
	
	assert(d1.begin().day() == 1);
	assert(d1.last().day() == 10); // 不是11 是10		// 左闭右开
	assert(d1.length().days() == 10);
	
	assert(d1 < d4);	// 第一个区间的end() 和 第二个区间的begin()
}

/* 日期迭代器 */
/*void date_iterator(){
	date d(2020, 3, 14);
	day_iterator d_iter(d);		// 天数 迭代器
	
	assert(d == d_iter);
	
	++d_iter;
	assert(d.day() == 15);
	
	year_iterator y_iter(d);	// 年数 迭代器
	++y_iter;
	assert(d.year() == 2021);
	
	month_iterator m_iter;
	++m_iter;
	assert(d.month() == 4);
	
}*/

void print_calender(){
	date d(2020, 3, 14);
	date start(d.year(), d.month(), 1);		//当月第一天
	date end =  d.end_of_month();			//当月最后一天
	for(day_iterator d_iter(start); d_iter != end; ++d_iter){	//天数迭代器
		cout << *d_iter << " " << d_iter->day_of_week() <<endl;
	}
}

int main(int argc, char *argv[]) {
	//test_date();
	//get_date_data();
	//output_data();
	data_of_length();
	//date_of_compute();
	//date_of_period();
	//date_iterator();
	//print_calender();
}