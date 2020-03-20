/*
 *	std::string 必须完全持有字符串的内容.极端的时候有很高的的拷贝代价.
 *	影响程序效率,而且在处理C字符串,提取子串时无能为力
 *
 *	boost::string_ref 轻量级字符串,只持有字符串的引用.没有内存拷贝成本
 *	运行效率高
 *
 *  boost::string_ref 不拷贝字符串,通过成员变量_ptr和_len标记字符串的
 *	起始位置和长度
 */

#include <boost/utility/string_ref.hpp>
using namespace boost;

#include <iostream>
using namespace std;
void test_string_ref_usage(){
	const char* ch = "Days of Future Past";
	string str(ch);

	string_ref s1(ch);
	string_ref s2(str);
	//boost::assert(s1 == s2 && s1 == ch && s2 == str);

	string_ref s3(ch, 4);	//s3 = Days
	cout << "s3 = " << s3 << endl;

	string_ref s4, s5;
	s4 = ch;					// assign
	s5 = str;

	const char * s45 = "Apple IPhone Ipad"
	string_ref str1(s45);

	str1.remove_prefix(6);
	cout << "str.remove_prefix(6)" << str1 << endl;//str.remove_prefix(6)IPhone Ipad

	str1.remove_suffix(5);
	cout << "str.remove_suffix(5)" << str1 << endl;//str.remove_suffix(5)IPhone
	cout << "original string" << s2 << endl;
}

int main(){
	test_string_ref_usage();
	return 0;
}
