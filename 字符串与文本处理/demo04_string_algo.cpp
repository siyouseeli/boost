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
#include <boost/utility/string_ref.hpp>
#include <boost/format.hpp>
#include <boost/assign.hpp>
using namespace boost;

#include <iostream>
#include <vector>
#include <deque>
#include <list>
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
	//to_upper() 和 to_lower()
	string oStr("hello, world!");
	string str(oStr);

	// 原地修改字符串
	to_lower(str);
	cout << "to_lower() = " << str << endl;//to_lower() = hello, world!
	to_upper(str);
	cout << "to_upper() = " << str<< endl; //Origin_str = HELLO, WORLD!

	cout << "Origin_str = " << str << endl;//Origin_str = hello, world!

	// 返回修改后的拷贝,原字符串没有改变
	str = oStr;
	cout << "to_lower_copy() = " << to_lower_copy(str) << endl;//to_lower_copy() = hello, world!
	cout << "to_upper_copy() = " << to_upper_copy(str) << endl;//to_upper_copy() = HELLO, WORLD!
	cout << "Origin_str = " << str << endl;//Origin_str = hello, world!
}

// 判断式算法
void test_string_algo_Judge(){
	//所有的判断式算法都有一个 i 前缀版本,
	//所有的判断式算法不变动字符串,所以没有_copy版本
	string str("Power Bomb");

	assert(iends_with(str, "bomb"));		// 忽略大小写
	assert(!ends_with(str,"bomb"));			// 严格

	assert(starts_with(str, "Pow"));		// 严格

	assert(contains(str, "er"));			// 是否包含

	string str2 = to_lower_copy(str);
	assert(iequals(str, str2));				// 是否相等

	string str3("power suit");
	assert(ilexicographical_compare(str, str3));	//忽略大小写

	assert(all(str2.substr(0,5), is_lower()));	// 检测字符串均小写


	//判断式--函数对象
	//提供大小写无关的形式
	string str4("Samus"), str5("samus");
	assert(!is_equal()(str4, str5));
	assert(is_less()(str4, str5));
	assert(!is_equal()(str4, string_ref(str2)));
}

//分类
void test_string_algo_classiy(){
	//检测一个字符是否符合某种特性
	//这些函数都是返回detail::is_classifiedF对象.
	//这个对象重载了||, && 和 !
	struct is_zeor_or_one{
		bool operator()(char x){
			return x=='0' || x =='1';
		}
	};// 自定义

}

//修剪
void test_string_algo_trim(){
	//修剪算法可以删除字符串开头或结尾部分的空格
	//_if和_copy版本
	format fmt("|%s|\n");
	string str = "    samus aran    ";
	cout << fmt %(trim_copy(str)) << endl;  	//删除两端的空格
	cout << fmt %(trim_left_copy(str)) << endl; //删除左端的空白

	trim_right(str);							//原地删除右端的空白
	cout << fmt % str << endl;

	string str2 = "2017 Happy new Year!!!";
	cout << fmt %(trim_left_copy_if(str2, is_digit())) << endl;	// 删除右端的数字
	cout << fmt %(trim_right_copy_if(str2, is_punct())) << endl;// 删除右端的标点
	cout << fmt %(trim_copy_if(str2, is_punct()||is_digit()||is_space())) << endl;

}

//查找
void test_string_algo_find(){
	format fmt("|%s|. pos = %d\n");

	string str = "Long long ago, there was a king.";

	iterator_range<string::iterator> rge;	//迭代器区间

	rge = find_first(str, "long");			//找到第一次出现
	cout << fmt % rge % (rge.begin() - str.begin());//|long|. pos = 5

	rge = ifind_first(str, "long");
	cout << fmt % rge % (rge.begin() - str.begin());//|long|. pos = 0

	rge = find_nth(str, "ng", 2);			// 第三次出现
	cout << fmt % rge % (rge.begin() - str.begin());//|ng|. pos = 29

	rge = find_head(str, 4);				// 前4个字符
	cout << fmt % rge % (rge.begin() - str.begin());//|Long|. pos = 0

	rge = find_tail(str, 5);
	cout << fmt % rge % (rge.begin() - str.begin());//|king.|. pos = 27

	rge = find_first(str, "samus");			//找不到
	assert(rge.empty() && !rge);

}


// 替换与删除
void test_string_algo_replace_delete(){
	string str = "Samus beat the monster.";

	cout << replace_first_copy(str, "Samus", "samus") << endl;
	replace_last(str, "beat", "kill");
	cout << str << endl;

	replace_tail(str, 9, "rideley.");
	cout << str << endl;

	cout << ierase_all_copy(str, "samus") << endl;
	cout << replace_nth_copy(str, "l", 1, "L") << endl;
	cout << erase_tail_copy(str, 8) << endl;
}

//分割字符串
void test_string_algo_split(){
	string str = "Samus,Link.Zelda::Mario-Luigi+zelda";
	deque<string> d;

	ifind_all(d, str, "zELDA");
	assert(d.size() == 2);
	for(auto x : d){
		cout << "["<< x << "]" << " ";		//[Zelda] [zelda]
	}
	cout << endl;

	list<iterator_range<string::iterator>> l;
	split(l, str, is_any_of(",.:-+"));
	for(auto x : l){
		cout << "["<< x << "]" << " ";		//[Samus] [Link] [Zelda] [] [Mario] [Luigi] [zelda]
	}
	cout << endl;

	l.clear();
	split(l, str, is_any_of(",.:-+"), token_compress_on);
	for(auto x : l){
		cout << "["<< x << "]" << " ";	//[Samus] [Link] [Zelda] [Mario] [Luigi] [zelda]
	}
	cout << endl;
}


// 合并
void test_string_algo_join(){
	using namespace boost::assign;

	vector<string> v = list_of("Samus")("Link")("Zelda")("Mario");

	cout << join(v, "+") << endl;

	cout << join_if(v, "**", [](string_ref s){ 
												return contains(s, "a"); 
											 }) << endl;
}


int main()
{
	//test_string_algo_usgae();
	//test_string_algo_Upper_lower();
	//test_string_algo_Judge();
	//test_string_algo_classiy();
	//test_string_algo_trim();
	//test_string_algo_find();
	//test_string_algo_replace_delete();
	//test_string_algo_split();
	
	test_string_algo_join();
	return 0;
}