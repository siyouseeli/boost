/*
* math.constants -- 提供了常用的数学常数
*/
#include <boost/math/constants/constants.hpp>
using namespace boost::math;

#include <iostream>
using namespace std;

void test_constant_usage(){
	cout << setprecision(64);		//设置显示精度64位

	//指定精度
	auto a = float_constants::pi * 2 * 2;
	cout << "area = " << a << endl; //area = 12.56637096405029296875

	using namespace double_constants;
	auto x = root_two * root_three;
	cout << "root two 2 * 3 = " << x << endl;//root two 2 * 3 = 2.449489742783178325424842114443890750408172607421875

	cout << "root pi = " << root_pi <<endl;
	cout << "pi pow =" << pi_pow_e << endl;

	
}

void test_math_constants_usage(){
	//利用模板变量特性 using namespace boost::math::constants;
	using namespace boost::math::constants;
	assert(pi<float>() == float_constants::pi);
	assert(pi<double>() == double_constants::pi);

	//使用boost.multiprecision库的高精度浮点数
	typedef boost::multiprecision::cpp_dec_float_100 float_100;
	cout << setprecision(100) << pi<float_100>() << endl;
}


int main(int argc, char *argv[]) {
	//test_constant_usage();
	test_math_constants_usage();
}