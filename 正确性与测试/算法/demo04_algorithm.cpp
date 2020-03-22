/*
 * clamp -- 判断一个值是否“夹”在另一对值中间
 * 
 *	
 */
#include <boost/algorithm/clamp.hpp>
#include <boost/assign.hpp>

#include <boost/algorithm/hex.hpp>
using namespace boost::algorithm;
#include <iostream>
using namespace std;

void test_clamp_usage(){
	assert(clamp(5, 1, 10));
	assert(clamp(5, 5, 10));
	assert(clamp(5, 1, 5));		// 5在[1,5]之间
	
	assert(clamp(5, 10, 15) == 10);
	assert(clamp(16, 10, 15) == 15);
}

//操作迭代器或容器版本，对一族元素执行clamp算法，然后将结果写入到一个《输出迭代器》
void test_clamp_range(){
	using namespace boost::assign; 
	vector<int> v = list_of(2)(4)(6)(8)(10);
	
	clamp_range(v, ostream_iterator<int>(cout, ","), 3, 9);
	
}

//十六进制 -- 编码与解码
void test_hex_usage(){
	 hex("123", ostream_iterator<char>(cout));		// 不会抛出异常
	cout << endl;
	
	unhex("313233", ostream_iterator<char>(cout));	//跑出not_enough_input或者non_hex_input
	cout << endl;

}
int main(int argc, char *argv[]) {
	//test_clamp_usage();
	//test_clamp_range();
	test_hex_usage();
}