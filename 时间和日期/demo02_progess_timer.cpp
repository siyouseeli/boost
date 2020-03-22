/*
 * progess_timer继承了timer，实现了timer的全部能力,继承自noncopyable
 * 
 * 实现原理：
 *			使用标准库<ctime>中的std::clock()函数返回自进程启动以来的clock数
 *			每秒的clock数由宏CLOCKS_PER_SEC定义
 *
 * 与timer区别
 *			构造函数增加了progress_timer(std::ostream& os)
 *			可指定输出流ofstream ostringstream
 *
 * 使用建议：
 *			不适合高精度的时间测量任务；
 *			依赖于操作系统、编译器，难以做到跨平台；
 *			必须理解elapsed_max()  elapsed_min() 两个计时精度的含义；
 */

#include <boost/progress.hpp>
using namespace boost;

#include <iostream>
#include <sstream>
using namespace std;

void test_time_elpased(){
	//与timer相同的是可以显式调用
	//t.elapsed()
	//不同的是可以析构函数来计时
	//progress_timer t;
	//cout << "显示调用elpased(): "<<t.elapsed() << endl;
	
	std::stringstream s;
	{
		////析构函数
		progress_timer t(s);			//也可以ofsream ostringstream 替换
										// 默认为std::cout
		for(int i = 0; i < 10000000; ++i){
				
		}
		
	}
	cout  <<"析构函数调用1: " <<  s.str() << endl;
	s.flush();
	{
		//析构函数
		progress_timer t(s);
		for(long i = 0; i < 5000000000; ++i){
				
		}
	}
	cout  <<"析构函数调用2: " <<  s.str() << endl;
}

int main(int argc, char *argv[]) {
	test_time_elpased();
}