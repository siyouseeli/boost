/*
 * integer 提供了一组有关整数处理的头文件和类
 * 具有良好的可移植性
 *
 */
#include <boost/integer_traits.hpp>//integer_traits继承自std::numeric_limits<T>
#include <boost/format.hpp>
using namespace boost;

#include <boost/integer.hpp>
#include <boost/type_index.hpp>


#include <iostream>
using namespace std;

void test_integer_traits_usage(){
	cout << integer_traits<int>::const_max << endl;
	cout << integer_traits<int>::const_min << endl;

	cout << integer_traits<bool>::const_max << endl;
	cout << integer_traits<bool>::const_min << endl;

	cout << integer_traits<long>::const_max << endl;
	cout << integer_traits<long>::const_min << endl;
}

//整数类型模板类
template<typename T>
string type_name(){
	return typeindex::type_id<T>().pretty_name();
}
void test_integer_usage(){
	typedef int_fast_t<char>::fast cfast;	//char类型的最快类型
	cout << typeindex::type_id<cfast>().pretty_name() << endl;

	typedef int_fast_t<int>::fast ifast;
	cout << typeindex::type_id<ifast>().pretty_name() << endl;

	typedef int_fast_t<uint16_t>::fast u16fast;
	cout << typeindex::type_id<u16fast>().pretty_name() << endl;

	//使用指定的整数位或数值作为模板参数,内置类型least返回支持的最小整数类型
	//fast返回的最快整数类型,int_t,uint_t,int_max_value_t,int_min_value_t
	//uint_value_t
	format fmt("type:%s, size=%dbit\n");
	typedef uint_t<15>::fast u15;		//可容纳15位的无符号最快整型
	cout << fmt % type_name<u15>() % (sizeof(u15) * 8);

	typedef int_max_value_t<32700>::fast i32700;
	cout << fmt % type_name<i32700>() % (sizeof(i32700) * 8);

	typedef int_min_value_t<-33000>::fast i3300;
	cout << fmt % type_name<i3300>() % (sizeof(i3300) * 8);

	typedef uint_value_t<33000>::fast u33000;
	cout << fmt % type_name<u33000>() % (sizeof(u33000) & 8);
}

int main(int argc, char *argv[]) {
	//test_integer_traits_usage();
	test_integer_usage();
}