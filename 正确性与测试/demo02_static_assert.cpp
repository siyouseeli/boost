/*
 *
 *	BOOST_STATIC_ASSERT(expr)				// 编译器检查表达式
 *	BOOST_STATIC_ASSERT_MSG(expr, msg)		// 编译器检查表达式,带字符串消息
 *
 *  实际上是一个 typedef, 对运行效率没有任何影响
 *
 *	BOOST_ASSERT(expr) -- 必须是一个可执行的语句
 *  BOOST_STATIC_ASSERT() -- 则可以出现在程序的任何位置,名字空间域 类域 函数域
 *	
 *	主要用在泛型编程或模板元编程用于验证编译器常熟或者模板类型参数
 */
#include <boost/static_assert.hpp>

#include <iostream>
using namespace std;

void test_static_usage(){

	BOOST_STATIC_ASSERT(2 == sizeof(short));
	BOOST_STATIC_ASSERT(true);
	BOOST_STATIC_ASSERT_MSG(16 == 0x10, "test static assert");
}

template<typename T>
T my_min(T a, T b){
	//BOOST_STATIC_ASSERT(sizeof(T) < sizeof(int));	// 静态断言
	BOOST_STATIC_ASSERT_MSG(sizeof(T) < sizeof(int), "only short or char");
	return a < b ? a : b;
}
void test_static_assert_scoped(){
	cout << my_min((short)1, (short)3);
	cout << my_min(1L, 3L);				//编译器错误
}
int main(){

	//test_static_usage();
	test_static_assert_scoped();
	return 0;
}
