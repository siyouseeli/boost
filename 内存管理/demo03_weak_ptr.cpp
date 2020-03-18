/*
 *	weak_ptr : 没有重载operator* 和operator->不具有普通指针的行为
 *			   更像shared_ptr<>的助手
 *
 *  对象的自我管理: 使用weak_ptr观测shared_ptr,并不影响计数.使用时调用lock()弱拥有变为强拥有
 *  
 *	打破循环引用 -- 循环链表中用shared_ptr, 对方可能持有的引用计数为2, 会造成内存泄漏,替换成weak_ptr
 */
#include <boost\scoped_ptr.hpp>
#include <map>
#include <iostream>
#include <memory>		//被纳入C++11标准
#include <vector>
#include <stdio.h>
using namespace std;
using namespace boost;



void test_weak_ptr_usage(){
	shared_ptr<int> sp1(new int);
	*sp1 = 10;

	//从shared_ptr构造weak_ptr -- 来自weak_ptr的构造函数
	weak_ptr<int> wkp1(sp1);
	//从weak_ptr构造weak_ptr -- 来自weak_ptr的赋值函数
	weak_ptr<int> wkp2 = wkp1;	

	cout << "shared_ptr的引用计数为: " << sp1.use_count() << endl;
	cout << "构造一次.赋值一次,weak_ptr的引用计数为: " << wkp1.use_count() << endl;	// 1
	
	cout << "weak_ptr:wkp1的指针有效期= " << wkp1.expired() << endl;
	cout << "weak_ptr:wkp2的指针有效期= " << wkp2.expired() << endl;

	

	shared_ptr<int> sp2 = wkp1.lock();		// weak_ptr只能通过lock()函数获得shared_ptr-- 弱关系转为强关系
	cout << "shared_ptr:sp1的引用计数为: " << sp1.use_count() << endl;
	cout << "shared_ptr:sp2的引用计数为: " << sp2.use_count() << endl;
}

#include <boost/enable_shared_from_this.hpp>
class self_shared : public enable_shared_from_this<self_shared>{
public:
	self_shared(int n) : x(x){
		std::cout << "contruct func" << endl;
	}
	void print(){
		cout << "self_shared: " << x << endl;
	}
};
void test_weak_ptr_self_manange(){
	auto sp = make_shared<self_shared>(313);
	sp->print();

	auto p = sp->shared_from_this();		// 继承自enable_shared_from_this,获取shared<>的智能指针
	p->x = 1000;
	p->print();

}


int main(){

	//test_weak_ptr_usage();
	test_weak_ptr_self_manange();


	return 0;
}
