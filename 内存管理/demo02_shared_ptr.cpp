/*
 * shared_ptr:
 *			包装了new操作符在堆上分配的动态对象
 *			使用了引用计数的智能指针,可以被自由的拷贝和赋值,引用计数为0才被删除
 *
 * 构造函数:
 *			无参的shared_ptr() -- > 空指针的
 *			shared_ptr(Y * p) --> 获得指向类型T的指针p的管理权,同时引用计数置为1, Y必须转为T
 *			shared_ptr(shared_ptr const & r) -- 引用计数+1
 *			operator=赋值操作符从另外一个shared_ptr获得指针管理权
 *          shared_ptr(Y * p, D d) -->提供删除器D
 * rest()
 *		作用是将引用计数减1,停止对指针的共享,与scoped_ptr不一样
 *
 * 线程安全:
 *		多个线程可以访问shared_ptr对象
 *
 * 函数为protected意味着自己和子类才可以调用
 */

#include <boost\scoped_ptr.hpp>
#include <map>
#include <iostream>
#include <memory>		//被纳入C++11标准
#include <vector>
#include <stdio.h>
using namespace std;
using namespace boost;

void test_shared_ptr_use(){
	shared_ptr<int> spi(new int);
	assert(spi);									// 在bool语境中转换为bool值
	*spi = 253;

	shared_ptr<string> sps(new string("smart"));
	assert(sps->size() == 5);

	shared_ptr<int> dont_do_this(new int[10]);		// 危险不能正确释放内存

	typedef shared_ptr<string> sp_t;
	map<sp_t, int> m;				//标准映射器

	sp_t sp(new string("one"));		//一个shapred_ptr独享
	m[sp] = 111;					

	cout << sp << endl;				// 重载operator<<,输出指针值
}


void test_shared_ptr_count_1(){
	shared_ptr<int> sp(new int(10));			//
	assert(sp.unique());						// unique()是否唯一
	shared_ptr<int> sp2 = sp;					// 引用计数为2
	assert(sp == sp2 && sp.use_count() == 2);	// use_count()求得引用计数

	*sp2 = 100;
	assert(*sp == 100);

	sp.reset();									// 停止shared_ptr的使用
	assert(!sp);
}


class shared{
private:
	shared_ptr<int> p;
public:
	shared(shared_ptr<int> p_) : p(p_){}			// 没有使用引用参数,会增加shared_ptr引用计数
	void print(){
		cout << "count: " << p.use_count() << "v=" << *p <<endl;
	}
};

void print_func(shared_ptr<int> p){					// 没有使用引用参数,会增加shared_ptr引用计数
	cout << "count: " << p.use_count() << "v=" << *p <<endl;
}// 推出作用域,函数的形参会将引用计数减1

void test_shared_ptr_count_2(){
	shared_ptr<int> p(new int(100));
	shared s1(p), s2(p);				
	s1.print();
	s2.print();

	*p = 20;
	print_func(p);
	s1.print();
}


void test_shared_ptr_factory(){
	
	auto sp = make_shared<string>("make_shared");
	auto spv = make_shared<vector<int>>(10, 2);
	assert(spv->size() == 10);
}


void test_shared_ptr_in_std_container(){
	//智能指针应用于标准容器
	typedef vector<shared_ptr<int>> vs;	// 将智能指针置于标准容器
	vs v(10);

	int i = 0;
	for(auto pos = v.begin(); pos != v.end(); ++pos){
		*pos = make_shared<int>(++i);
		cout << *(*pos) << ",";
	}
	cout << endl;

	shared_ptr<int> p = v[0];
	*p = 10;
	cout << *(v[0]) <<endl;
}


struct socket_{};
socket_ * open_socket(){
	cout << "open socket" << endl;
	return new socket_;
}
void close_socket(socket_* s){			// 参数不能忘记
	cout << "close socket" << endl;
}

void test_shared_ptr_delete(){
	//定制删除器
	socket_ * s = open_socket();
	shared_ptr<socket_> p(s, close_socket);		//传入删除器

	shared_ptr<FILE> sp(fopen("./text.txt", "r"), fclose);	// 可借鉴
}


void test_shared_ptr_cast(){
	//基类与子类互相转换
	//转型 -- 引用计数增加
	shared_ptr<std::exception> sp1(new bad_exception);
	auto sp2 = dynamic_pointer_cast<bad_exception>(sp1);
	cout << sp2.use_count() << endl;		// 2	
	auto sp3 = static_pointer_cast<std::exception>(sp2);
	cout << sp3.use_count() << endl;		// 3
	assert(sp3 == sp1 && !sp3.unique() );

}


int main(){

	//test_shared_ptr_use();
	//test_shared_ptr_count_1();
	//test_shared_ptr_count_2();
	//test_shared_ptr_factory();
	//test_shared_ptr_in_std_container();
	//test_shared_ptr_delete();
	//test_shared_ptr_cast();
	return 0;
}

