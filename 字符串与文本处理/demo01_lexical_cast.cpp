/*
 * lexical_cast 字符串与整数/浮点数之间的字面转换
 *
 *  字符串---->数字:
 *		字符串不能出现字母或其他非数字字符
 *
 *	不能将数字转换成指定格式的字符串
 *
 *	标准形式
 *		template<typename Target, typename Source>
 *		inline Target lexical_cast(const Source& arg);
 *
 *  转换字符串
 *		template<typename Target>
 *		inline Target lexical_cast(const char* chars, std::size_t count);
 *
 *	转换对象的要求:
 *		转换起点对象是可流输出的,既定义了operator<<
 *		转换终点对象是可流输入的,定义了operator>>
 *		转换终点对象必须时刻默认构造和可拷贝构造
 *	
 *  对比C++标准
 *		std标准是无需写模板参数,而且字符串里允许出现非数字字符串--忽略起始的空白格.直到遇到无法转换的字符为止
 */

#include <boost/lexical_cast.hpp>
using namespace boost;

#include <iostream>
#include <exception>
using namespace std;

void text_lexical_cast_usage(){
	//字符串---->整数
	int x = lexical_cast<int>("100");
	long y = lexical_cast<long>("2000");
	float pai = lexical_cast<float>("3.1415999e5");//[output]314160 -- 字母e后面的停止转换
												   // <字符串不能出现字母或其他非数字字符>
	double d = lexical_cast<double>("3.14");
	cout << x <<" " << y << " " << pai << " " << d << endl;

	//整数----->字符串
	string str = lexical_cast<string>(456);
	cout << lexical_cast<string>(0.618) << endl;		//[output] 0.6177777777777777777
	cout << lexical_cast<string>(0x10) << endl;

	//字符串---->bool
	cout << lexical_cast<bool>("1") << endl;
}

//函数模板 -- 验证数字符串的有效性
template<typename T>
bool num_valid(const char* str){
	T tmp;
	return conversion::try_lexical_convert(str, tmp);
}

void test_lexical_cast_error_handle(){
	try{
		cout << lexical_cast<int>("0x100");

	}catch(bad_lexical_cast& e){				// 转换失败抛出bad_lexical_cast
		cout << "error: " << e.what() << endl;
	}

	//代替try_catch
	int x;
	bool ret = conversion::try_lexical_convert("0x100", x);//转换成功返回1
	if(!ret){
		cout << "convert failue" << endl;
	}

	//验证数字字符串的有效性
	cout << num_valid<int>("0.100") << endl;
	cout << num_valid<double>("0x100") << endl;
}

//将lexcial_cast应用于自定义类,实现Java中的Object.toString()
//类中需自定义operator<<运算符
class demo_class{
	friend std::ostream& operator<<(std::ostream& os, const demo_class &x){
		os << "demo_class Name";
		return os;
	}
};
template <typename T>
struct outable{
	friend std::ostream& operator<<(std::ostream& os, const T &x){
		os << typeid(T).name();		//使用typeid操作符输出类型名称
		return os;
	}
};
class demo_class_1 : outable<demo_class_1>{};
void test_lexical_in_class(){
	cout << lexical_cast<string>(demo_class()) << endl;
	cout << "-------" << endl;
	cout << lexical_cast<string>(demo_class_1()) << endl;
}


void test_contrast_std(){
	cout << stoi(" 12eee3  ") << endl;
	cout << stol("  456456L   ") << endl;
	cout << stof("0.222") << endl;

	cout << to_string(123) << endl;
	cout << to_string(3.1444) << endl;
	try{
		
		cout << stoi("99999999999");
	}catch(out_of_range & e){
		cout << "out_of_range " <<e.what() << endl;
	}

	try{
		cout << stoul("x100");
	}catch(invalid_argument & e){
		cout << "invalid_argument " << e.what() << endl;
	}
	

}
int main(){
	//text_lexical_cast_usage();
	//test_lexical_cast_error_handle();
	//test_lexical_in_class();
	test_contrast_std();
	return 0;
}