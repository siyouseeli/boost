/*
 *	boost.string_algo -- 全面的字符串算法库
 *
 *	boost.string_algo基于boost.range,避免了标准库算法必须提供begin()和end()迭代器
 *
 *	命名规则:
 *			前缀 i     -- 大小写不敏感(忽略大小写),否则大小写敏感
 *			后缀 copy  -- 不变动输入,返回处理结果的拷贝,否则原地输入输出
 *			后缀_if    -- 需要作一个判断式的谓词函数对象,否则使用默认的判断准则
 *	
 *	string_algo:
 *		大小写转换
 *		判断式与分类
 *		修剪
 *		查找与替换
 *		分割与合并
 */
#include <boost/algorithm/string.hpp>
using namespace boost;

#include <iostream>
#include <vector>
using namespace std;

void test_string_algo_usgae(){
	string str("readme.txt");
	if(ends_with(str, "txt")){
		cout << "to_upper_copy = " <<to_upper_copy(str) + " UPPER" << endl;
		assert(ends_with(str, "txt"));	// 原始字符串没有变
	}

	replace_first(str, "readme", "followme");//替换字符串 - 无copy
	cout <<"replace_first = " <<  str << endl;

	//string_algo 也可工作在具有可拷贝构造和赋值的类型上,如vector
	vector<char> v(str.begin(), str.end());
	vector<char> v2 = to_upper_copy(erase_first_copy(v, "txt"));
	for(auto ch : v2){
		cout << ch;
	}
	cout << endl;
}


//(1)大小写转换
void test_string_algo_Upper_lower(){
	
}

int main(){
	test_string_algo_usgae();
	return 0;
}