/*
 *	唯一性,不能拷贝和赋值  
 *
 * 局部对象,利用RAII机制(声明及初始化)会很好的工作(析构函数会被执行),
 * 但是new操作在堆上创建的对象,意味着可能存在内存泄漏.
 *
 * boots.smart_ptr库的优点;(前提)对于其指向的类型T析构函数不能抛出异常
 *
 * scoped_ptr的工作原理和特点
 *			包装了new操作符在堆上分配的动态对象,能够保证对象在任何人时候都被正确的删除
 * 			只能在<本作用域>里使用,不希望被转让(拷贝构造和赋值操作符是private -- >拒绝所有权转让)
 *			没有定义++ 与 -- 操作
 *
 * scoped_ptr对象间不能进行相等或不等测试,默认仅支持nullptr比较
 */
#include <boost\smart_ptr.hpp>
#include <boost\smart_ptr.hpp\make_unique.hpp>	 // 为调用make_unique
using namespace boost;

#include <iostream>
#include <string>
using namespace std;

struct posix_file{
	posix_file(const char* file_name){
		cout << "open file" << file_name << endl;
	}
	~posix_file(){
		cout << "close file" << endl;
	}
};

void test_scoped_ptr(){
	scoped_ptr<string> sp(new string("text"));
	assert(sp);				// 使用显示bool操作 -- 定义了operator bool()
	assert(sp != nullptr);	// 与空指针比较操作 -- 只能与空指针比较
	//assert(sp == sp);		// scoped_str对象间不能比较
	cout << *sp << endl;			// text -- 操作符*重载
	cout << sp->size() << endl;		// 4 -- 操作符->重载

	//auto sp1 =sp;			// 错误,所有权不得转让 -- **函数私有化
							// 一个类中含有对象,则此类也是不可复制和拷贝的,编译错误

	scoped_ptr<posix_file> fp(new posix_file("./tmp"));
	scoped_ptr<int> p(new int);
	if(p){						// 使用显示bool操作
		*p = 100;
		cout << *p << endl;
	}

	//fp.reset();				// fp调用reset将会调用其析构函数,但是一般不建议
	p.reset();					// reset()将 重置为nullptr
	assert(p == 0);
	if(!p){
		cout << "scoped_ptr == nullptr" << endl;
	}


	//与std unique_ptr对比
	//unique_ptr可以像指针一样进行比较,可以像shared_ptr一样定制删除器
	//也可以安全的放入标准容器
	unique_ptr<int> up(new int);
	assert(up);
	*up = 10;
	cout << *up << endl;

	up.reset();					// 重置指针
	assert(!up);

	//使用boost库中的make_unique()
	//#include <boost\smart_ptr.hpp\make_unique.hpp> 与std避免潜在冲突
	//scoped_ptr 不需要也不可能有make_scoped()函数,因为不允许拷贝和转移
	auto p = boost::make_unique<int>(10);
	assert (p && *p == 10);
}

int main(){
	
	test_scoped_ptr();

	return 0;
}//scoped_ptr自动帮助我们析构资源