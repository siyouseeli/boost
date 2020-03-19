/*
 * boost.exception 针对标准库异常的缺陷进行了强化,重载了<<操作符,可以向异常传入任何数据,有助于增加
 * 异常信息的表达能力
 *
 * 定义错误信息类型:
 *			基本方法:typedef boost::error_info<struct tag_err_int, int> err_int; --不适用于大量的错误类型
 *	        进阶方法: 使用boost.exception库自定义的若干错误信息类		
 *		    自定义方法:#define DEFINE_ERROR_INFO(type, name) \
 *											typedef boost::error_info<struct tag_##name, type> name
 *
 * 包装异常类
 *		包装类型T 产生一个从boost.exception和std::exception得类,不修改原有类记得基础上获得boost.excption的好处
 */
#include <boost/exception/all.hpp>
using namespace boost;


#include <iostream>
using namespace std;

#define DEFINE_ERROR_INFO(type, name) \
				typedef boost::error_info<struct tag_##name, type> name

struct my_exception : virtual std::exception, virtual boost::exception{};
typedef boost::error_info<struct tag_err_int, int> err_int;
typedef boost::error_info<struct tag_err_string, string> err_string;
void test_exception_usage(){
	try{
		try{
			throw my_exception() << err_int(10);		//boost::exception重载了<<操作符
		}catch(my_exception &e){
			cout << *get_error_info<err_int>(e) << endl;//value_type* get_error_info(E &x); -- 获取内部保存的信息指针
			cout << e.what() << endl;
			e << err_string("other");
			throw;
		}
	}catch(my_exception& e){
		cout << *get_error_info<err_string>(e) << endl;
	}
	
}

void test_excepiton_auto(){
	//boost.exception 自定义
	try{
		throw my_exception() << errinfo_api_function("call api") << errinfo_errno(101);
	}catch(boost::exception& e){
		cout << *get_error_info<errinfo_api_function>(e) << endl;
		cout << *get_error_info<errinfo_errno>(e) << endl;
	}

	try{
		throw my_exception() << throw_function(BOOST_CURRENT_FUNCTION) << throw_file(__FILE__)
							 << throw_line(__LINE__);
	}catch(my_exception &e){
		cout << *get_error_info<throw_function>(e) << endl;
		cout << *get_error_info<throw_file>(e) << endl;
		cout << *get_error_info<throw_line>(e) << endl;
	}
	cout << "----------------" << endl;
	//上面几行代码的替代 -- 一次输出所有的错误信息
	try{
		throw my_exception() << throw_function(BOOST_CURRENT_FUNCTION) << throw_file(__FILE__)
							 << throw_line(__LINE__);
	}catch(my_exception &e){
		cout << diagnostic_information(e) << endl;
		
	}
}

void test_define_my_exception(){
	DEFINE_ERROR_INFO(string, myexcp);
	try{
		throw my_exception() << myexcp("myself exception");
	}catch(my_exception& e){
		cout << *get_error_info<myexcp>(e) << endl;
	}

}

/* 包装异常类 */
void test_enable_error_info(){
	struct my_err{};
	try{
		throw enable_error_info(my_err()) << throw_function(BOOST_CURRENT_FUNCTION);	// 返回的一个拷贝 --性能
	}catch(boost::exception &e){			// 返回的是子类,所以此处用父类也可以 -- 多态
		cout << *get_error_info<throw_function>(e) << endl;
	}
}

/* 线程间传递异常信息 */
 
int main(){
	//test_exception_usage();
	//test_excepiton_auto();
	//test_define_my_exception();
	//test_enable_error_info();
	return 0;
}
