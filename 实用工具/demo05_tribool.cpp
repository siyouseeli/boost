/*
 *	boost.tribool类似C++内建的bool类型,但基于true, false, indeterminate(未知,不确定)
 *
 * tribool 与 optional<bool>的区别:
 *				语义区别:
 *						optional<bool> b;  // 是一个未初始化的bool, 无意义的值
 *						tribool 的indeterminate是已经初始化的有意义值,表示bool值不确定
 *				用法区别:
 *						optional<bool>需要用类似指针的形式,获取bool值 if(optional<bool>) -- 判断的是optional对象是否初始化,而不是bool
 *						tribool 可以当做bool类型使用
 *				函数返回:
 *						如果返回值无效的 -- optional<bool>
 *						如果返回值是确定的,但无法确定其意义 --tribool
 */
#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>
using namespace boost;

#include <iostream>
using namespace std;

void test_tribool_usage(){
	tribool t1;				// 默认构造函数为 false
	if(!t1){	
		cout << "defalut construct is false" << endl;
	}

	tribool t2(tribool::true_value);	// tribool(bool value) -- 构造函数
										// enum{false_value, true_value, indeterminate_value} value
	if(t2){	
		cout << " t2 is true" << endl;
	}

	tribool t3(true);					// tribool(bool value)
	if(t3){	
		cout << " t3 is true" << endl;
	}

	t3 = indeterminate;
	if(indeterminate(t3)){				//indeterminate()函数判断是否是indeterminate
		cout << "t3 is indeterminate_value" << endl;
	}
	if(indeterminate(!t3)){				//indeterminate的逻辑非状态还是indeterminate
		cout << "t3 is indeterminate_value" << endl;
	}

	cout << (t3 || true) << endl;			// 1	|| 只与true运算结果为true
	cout << (t3 || false) << endl;			// 2
	cout << (t3 || indeterminate) << endl;	// 2
	cout << (t3 && false) << endl;			// 0	&& 只与false结果为false
	cout << (t3 && true) << endl;			// 2 	-- indeterminate
	cout << (t3 && indeterminate) << endl;	// 2
}


void test_tribool_output(){
	tribool tb1(true), tb2(false), tb3(indeterminate);
	cout << tb1 << ","
		 << tb2 << ","
		 << tb3 << endl;
}

int main(){
	test_tribool_usage();
	//test_tribool_output();
	return 0;
}