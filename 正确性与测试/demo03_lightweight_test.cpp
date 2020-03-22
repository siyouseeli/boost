/*
 *	lightweight_test 是一个轻量级的<单元测试>框架
 *
 *		BOOST_TEST(e)
 *		BOOST_TEST_NOT(e)
 *		BOOST_ERROR(s)
 * 		BOOST_TEST_EQ(e1, e2)
 *		BOOST_TEST_NE(e1, e2)
 *		BOOST_TEST_CSTR_EQ(e1, e2)	-- 断言两个字符串是否相等
 *		BOOST_TEST_CSTR_NE(e1, e2)
 *		BOOST_TEST_THROWS(e, ex)	-- 断言表达式抛出异常
 */

#include <boost/core/lightweight_test.hpp>
#include <boost/smart_ptr.hpp>
using namespace boost;

#include <iostream>
#include <memory>
using namespace std;

void test_lightweight_test(){
	auto p = make_shared<int>(10);
	
	BOOST_TEST( *p == 10);
	BOOST_TEST(p.unique());
	BOOST_TEST_NOT(!p);
	
	BOOST_TEST_EQ(p.use_count(), 1);
	BOOST_TEST_NE(*p, 20);
	
	p.reset();
	BOOST_TEST(!p);
	
	BOOST_TEST_THROWS(p, std::runtime_error);
	BOOST_ERROR("error accured");
	
}

//编译器的断言
void test_traits_usage(){
	BOOST_TEST_TRAIT_TRUE((is_integral<int>));
	BOOST_TEST_TRAIT_FALSE((if_function<int>));
}

int main(){

	//test_lightweight_test();
	test_traits_usage();
	boost::report_errors();

	return 0;
}