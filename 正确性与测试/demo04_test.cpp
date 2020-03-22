/*
 *	test基于命令行界面的测试套件(UTF,Unit Test Framework)，附带检测内存泄漏，还具有程序运行监控功能
 *	
 *  minimal_test -- 最小化测试
 *		测试断言有CHECK/REQUIRE/FAIL级别
 *		不支持捕获异常的测试
 *		必须实现test_main()函数作为测试入口
 *		自动输出测试报告
 */
//#include <boost/test/unit_test.hpp>
#include <boost/test/minimal.hpp>		// 最小化测试
#include <iostream>
using namespace std;

#include <boost/format.hpp>

int test_main(int argc, char* argv[]){
	using namespace boost;
	format fmt("%d-%d");
	
	BOOST_CHECK(fmt.size() != 0);			//断言测试通过，如不通过不影响程序执行
	fmt % 12 % 34;
	BOOST_REQUIRE(fmt.str() == "12-34");	//断言测试必须通过，否则程序停止
	
	BOOST_ERROR("演示一条错误消息");			//给出一个错误消息，程序继续运行
	
	fmt.clear();
	
	fmt % 12;
	try{
		cout << fmt;
	}catch(...){
		BOOST_FAIL("致命错误，测试终止");		//给出一个错误消息，否则程序停止
											//虽然放在异常捕获，但是程序还是停止
	}	
	
	return 0;
}

//单元测试框架
//BOOST_LEVEL_XXX : BOOST_等级__具体的测试断言
