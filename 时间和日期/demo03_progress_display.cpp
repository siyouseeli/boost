/*
 * 可在控制台上显示程序的执行进度,是一个独立的类，与timer和progress_timer没有“关系”
 * 继承自noncopyable
 * 
 */
#include <boost/progress.hpp>
using namespace boost;


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void test_progress_display(){
	
	vector<string> v(100000);
	ofstream out("./text1.txt");
	
	progress_display pd(v.size());		//传入的是基数
	for(auto & x : v){
		out << x << endl;
		++pd;
	}
	
	
}

void test_progress_display_error(){
	//progress_display进度与cout其他无法区别分开
	vector<string> v(100, "aaa");
	ofstream out("./text1.txt");
	progress_display pd(v.size());
	v[10] = ""; v[23]="";			//添加条件
	
	for(auto pos = v.begin(); pos != v.end(); pos++){
		out << *pos << endl;
		++pd;
		if(pos->empty()){
			cout << "null string" << (pos - v.begin()) << endl;
			
			//重要的两句，避免程序进度被其他输出打断
			pd.restart(v.size());			// 重新调整基数
			pd += (pos - v.begin()+1);		// 指定当前进度		
		}
	}
			
}


int main(int argc, char *argv[]) {
	//test_progress_display();
	test_progress_display_error();
}