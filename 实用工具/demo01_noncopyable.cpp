/*
 *	noncopyable -- 实现一个禁止拷贝的类
 */

#include <boost\noncopyable.hpp>
#include <boost\utility.hpp>
using namespace std;
using namespace boost;


class do_not_copy : noncopyable{};

void test_noncopyable_usage(){
	do_not_copy d1;
	//do_not_copy d2(d1);			// 编译错误
	do_not_copy d3;
	//d3 = d1;						// 编译错误
}

int main(){

	test_noncopyable_usage();
	return 0;
}