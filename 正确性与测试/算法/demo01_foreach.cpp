/*
 *	foreach库提供了BOOST_FOREACH和BOOST_REVERSE_FOREACH
 *  实现正向遍历和反向遍历
 *
 *	循环中不能改变序列的长度，也不能增减序列的元素，否则会导致迭代器失效
 *
 *  支持标准容器 原始数组 C字符串 以及元素是std::pair
 *
 * 	支持自定义的容器序列：
 *			第一种：提供内部的iterator和const_iterator,以及类型begin()和end()函数
 *			第二种：自定义类型满足boost.range概念
 *				
 */
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
#include <vector>
#include <iostream>
#include <map>
using namespace std;
#define foreach BOOST_FOREACH
void test_foreach_usage(){
	using namespace boost::assign;
	vector<int> v = list_of(1)(2)(3)(4);
	
	BOOST_FOREACH(auto x, v){			// x其实是一个copy
		cout << x << ", "; 		//1, 2, 3, 4
	}
	cout << endl;
	
	BOOST_REVERSE_FOREACH(auto x, v){
		cout << x << ", "; 		//4, 3, 2, 1
	}
	cout << endl;

	foreach(int &x, v){
		x += 1;
		cout << x << ", ";		//2, 3, 4, 5
	}
	cout << endl;
	
	//map
	map<string, int> mp = list_of(make_pair<string, int>("int", 1))(make_pair<string, int>("float", 3));
	foreach(auto x, mp){
		cout << x.first <<"-->" << x.second << ", ";		//float-->3, int-->1, 
	}
	cout << endl;
	
	//字符串
	const char* s= "Hello world!!!";
	foreach(char x, s){
		cout << x << ", ";		//H, e, l, l, o,  , w, o, r, l, d, !, !, !,
	}
	cout << endl;
}

int main(int argc, char *argv[]) {
	test_foreach_usage();
}