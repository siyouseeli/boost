/*
 *	intrusive_ptr : 引用计数型智能指针
 *
 *  intrusive_ptr不管理引用计数, 通过两个函数管理引用计数
 *
 *  intrusive_ptr构造函数和reset有 add_ref参数, 表示是否增加引用
 */
#include <boost\smart_ptr.hpp>
using namespace boost;

#include <iostream>
#include <string>
using namespace std;
struct counted_data{
	int m_count = 0;
};
void intrusive_ptr_add_ref(counted_data *p){
	++p->m_count;
}
void intrusive_ptr_release(counted_data * p){
	if(--p->m_count == 0){
		delete p;
	}
}
void test_intrusive_ptr_usage(){
	typedef intrusive_ptr<counted_data> counted_ptr;
	counted_ptr p(new counted_data);
	assert(p);
	assert(p->m_count == 1);

	counted_ptr p2(p);
	assert(p->m_count == 2);

	counted_ptr weak_p(p.get(), false);			// 弱引用
	assert(weak_p->m_count == 2);				// 引用计数不增加

	p2.reset();
	assert(!p2);
	assert(p->m_count == 1);					// 对象正确析构
}

int main(){
	test_intrusive_ptr_usage();
	return 0;
}