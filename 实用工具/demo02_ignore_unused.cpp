/*
 * ignore_unused -- 暂时用不到但又必须保留的变量, 禁止编译器警告
 * 
 * 	接受可变参数的模板类,运行时几乎没有效率损失 --- inline函数
 */
#include <boost/core/ignore_unused.hpp>
using namespace boost;

#include <iostream>
using namespace std;

int test_ignore_unused_usage(int x, int y){
	int i;
	ignore_unused(i, x);			// 相当于(void)i, (void)x
	return y;
}

int main(){
	int i ;
	i = test_ignore_unused_usage(1, 2);

	return 0;
}