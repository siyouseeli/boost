/*
 *	boost.assert提供的主要工具 BOOST_ASSERT 
 *	
 * BOOST_DISABLE_ASSERTS
 *		断言取消
 * BOOST_ENABLE_ASSERT_HANDLER
 *  	debug 和 release 都会运行
 */
#define BOOST_ENABLE_ASSERT_HANDLER		// 启用handler
#include <boost/assert.hpp>
#include <boost/format.hpp>
using namespace boost;

#include <iostream>
using namespace std;


namespace boost{
	void assertion_failed_msg(char const* expr, char const* msg,
					char const* function, char const* file, long line)
	{
		boost::format fmt("Assertion failed!\nExpression: %s\n"
						 "Function: %s\nFile:%s\nLine:%ld\n"
						 "Msg: %s\n\n");
		fmt % expr % function % file % line %msg;
		cout << fmt;
	}
	void assertion_failed(char const*expr , char const* function, 
					char const*file, long line){
		boost::format fmt("Assertion failed!\nExpression: %s\n"
						 "Function: %s\nFile:%s\nLine:%ld\n"
						 "\n\n");
		fmt % expr % function % file % line;
		cout << fmt;
	}
	
}



double func(int x){
	BOOST_ASSERT(0);	// 用BOOST_DISABLE_ASSERTS宏之后,BOOST_ASSERT失效
	cout << "after BOOST_ASSERT" << endl;
	
	//assert(x != 0 && "divided by zero");//用BOOST_DISABLE_ASSERTS宏之后,assert不失效
	//cout << "after assert " << endl;		//
	return 1.0/ x;
}

void test_assert_usage(){
	func(0);
}

//扩展用法
void test_assert_enable_msg_handle(){
	func(0);
}
int main(){

	//test_assert_usage();
	test_assert_enable_msg_handle();
	return 0;
}
