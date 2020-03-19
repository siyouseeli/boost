/*
 *	二进制常量
 *
 *	调用函数名
 */
#include <boost/utility/binary.hpp>
#include <boost/utility.hpp>
using namespace boost;

#include <boost/current_function.hpp>

#include <iostream>
#include <bitset>
using namespace std;

void test_const_binary(){
	cout << hex << showbase;
	cout << BOOST_BINARY(0110) << endl;
	cout << BOOST_BINARY(0110 1101) << endl;
	cout << BOOST_BINARY(10110110 01) << endl;
	cout << bitset<5>(BOOST_BINARY(0110)) << endl;
}

double func(){
	cout << BOOST_CURRENT_FUNCTION << endl;		// 调用函数名

}
int main(){

	//test_const_binary();
	func();
	return 0;
}