/*
 *	boost.format 参数格式化到字符串,而且是完全类型安全的	
 */

#include <boost/format.hpp>
using namespace boost;


#include <iostream>
using namespace std;

void test_format_usage(){
	//产生一个临时的format对象,由于format重载了operator%操作符,
	//此处相当于format("%d + %d + %d = %d") << 1 << 2 <<3 << 6
	//最后format定义了输出流运算符
	cout << format("%d + %d + %d = %d") % 1 % 2 % 3 % 6 << endl;

	format ft("%1% + %2% + %3% + %4%");
	ft % 1 % 2 % 3 % 5;		// 参数的数量必须等于格式化中的数量,
	cout << ft.str() << endl;		// 1+2+3+5

}


void test_format_language(){
	cout << format("%05d") % 1 << endl;			// 输出宽度为5,不足位用0补充
	cout << format("%-8.3f") % 3.141589 << endl;//3.142 输出左对齐,总宽度为8,小数位3位的浮点数
	cout << format("%8.3f") % 3.141589 << endl;//   3.142 输出右对齐,总宽度为8,小数位3位的浮点数
	cout << format("%10s") % "hello" << endl;//     hello 输出10位字符串,不足位用空格填充
	cout << format("%05X") % 16 << endl;	//00010 输出宽度为5的大写十六进制,不足位用0填充

}

void test_format_junior(){
	using boost::io::group;
	format fmt("%1% %2% %3% %2% %1%");
	cout << fmt % 1 %2 %3 << endl;
	cout << fmt.str() << endl;

	fmt.bind_arg(2, 10);		// 第二个参数绑定为10
	cout << fmt % 1 %3 << endl;

	fmt.clear(); 	// 清空缓冲,但绑定参数不变

	cout << fmt % group(showbase, oct, 111) % 333 << endl;

	fmt.clear_binds();			//清空所有绑定参数
	cout << fmt % 1 %2 %3 << endl;


}


int main(){
	
	//test_format_usage();
	//test_format_language();
	test_format_junior();
	return 0;
}