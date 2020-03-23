/*
 * 有理数
 *
 */
#include <boost/rational.hpp>
using namespace boost;

#include <iostream>
using namespace std;

void test_rational_create_assign(){
	rational<int> a;			// a= 0
	rational<int> b(20);		// b=1/20
	rational<int> c(31415, 10000); //c=3.1415

	rational<int> r;
	r = 0x31;
	r.assign(7, 8);				// r =7/8
}

void test_rational_operator(){
	rational<int> a(3), b(65534), c(22, 7);
	cout << a <<" " << b << " " << c << endl;
	b += a;
	cout << b << endl;	//65537/1

	c -= a;
	cout << c << endl;	//1/7
	if(c >= 0){
		c =  c * b;
		++a;
	}
	assert(a == 4);

	//类型转换
	rational<int> r1(10);
	if(r1){					// r1不为0,被隐式转换bool值true
		r1 -= 10;
	}
	assert(!r1);			// r1为0,被隐式转换bool值false

	rational<int> r(2718, 10000);
	cout << rational_cast<int>(r) << endl; //0 -- rational只能隐式转换bool类型
	cout << rational_cast<double>(r) << endl;//0.2718

	rational<int> r2(22, 7);
	cout << r.numerator() << ":" << r.denominator() <<	//返回的是右值,只能读不能写
	"=" << rational_cast<double>(r) ;

	//rational的最大精度数跟模板参数有关
}

void test_gcd_lcm(){
	cout << gcd(37, 62) << ", " << lcm(37, 62) << endl;
}
int main(){

	//test_rational_operator();
	test_gcd_lcm();
	return 0;
}
