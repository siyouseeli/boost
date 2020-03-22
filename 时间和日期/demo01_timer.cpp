/*
 * timer组建的精度要小于cpu_timer
 * 
 * 实现原理：
 *			使用标准库<ctime>中的std::clock()函数返回自进程启动以来的clock数
 *			每秒的clock数由宏CLOCKS_PER_SEC定义
 *
 * 使用建议：
 *			不适合高精度的时间测量任务；
 *			依赖于操作系统、编译器，难以做到跨平台；
 *			必须理解elapsed_max()  elapsed_min() 两个计时精度的含义；
 */

//-- timer 头文件
#include <boost/timer.hpp>
using namespace boost;


#include <iostream>
using namespace std;

/*timer -- 测量时间的流逝，毫秒精度*/
void test_time_elpased(){
	timer t;			// 声明即构造函数已经启动计时功能
	
	//获取最大的计时范围
	cout << "max time" << t.elapsed_max()/3600 << "h" << endl;
	
	//获取最小的计时范围
	cout << "min_time" << t.elapsed_min() <<  "s" << endl;
	
	for(int i = 0; i < 10000; ++i){
		
	}
	//获取已经过去的时间
	cout << "haved passed" << t.elapsed() <<  "s" << endl;
	
	cout << "restart timer;" << endl;
	
	t.restart();	// 重新开始计时
	cout << "haved passed" << t.elapsed() <<  "s" << endl;
}

int main(int argc, char *argv[]) {
	test_time_elpased();
}