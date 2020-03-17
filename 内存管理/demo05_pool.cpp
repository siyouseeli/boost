/*
 *	pool基于 简单分割存储 思想实现 快速紧凑的内存池库,补技能狗管理大量对象,也可为STL的内存分配器
 *  近似于 小型的 垃圾回收机制,不需要delete对象
 */
#include <boost/pool/pool.hpp>
using namespace boost;

#include <iostream>
using namespace std;

void test_pool_usage(){
	pool<> p1(sizeof(int));		//	构造函数传入的 每次分配内存的大小为4个字节
	int *p = static_cast<int *>(p1.malloc());	// 从内存池中分配内存款,大小为4个字节, 类型转换,内存分配失败不会抛出异常(需检查返回值)
	if( p == nullptr){
		cout << "new memory failure" << endl;
	}
	assert(p1.is_from(p));			// is_from()是否来自于内存吃的分配

	p1.free(p);					// free(void* chunk) -- 释放之前分配的内存
	//assert(p == NULL);

	for(int i = 0; i < 100; i++){
		p1.ordered_malloc(10);		//ordered_malloc()连续分配10快内存,同时合并空闲块链表
	}
}//  pool的析构函数调用purge_memory()	



#include <boost/pool/object_pool.hpp>
struct demo_class{
public:
	int a, b, c;
	demo_class(int x = 1, int y = 2, int z = 3):a(x), b(y),c(z){
		cout << "construct..." << endl;
	}
	~demo_class(){
		cout << "decontruct..." << endl;
	}
};

void test_object_pool_usage(){
	// 用于类实例的内存池, 析构时对所有已经分配的内存块调用析构函数
	object_pool<demo_class> p1;		//对象内存池
	auto p = p1.malloc();			//分配一个原始的内存块
	assert(p1.is_from(p));			//判定原始内存块p是否来自内存池p1

	//p指向的内存未经初始化
	assert(p->a != 1 || p->b != 2 || p->c != 3);
	p = p1.construct(7, 8, 9);		//构造一个对象,可以传递参数
	assert(p->a == 7);

	object_pool<string> pls;		// 定义一个分配string对象的内存池
	for(int i = 0; i < 10; ++i){
		string *ps = pls.construct("hello object_pool");
		cout << *ps << endl;
	}
}



#include <boost/pool/singleton_pool.hpp>
struct pool_tag{};
typedef singleton_pool<pool_tag, sizeof(int)> sp1;
void test_signleton_pool_usage(){
	//singleton_pool -- 是一个单例,所有的函数都是static, 通过 :: 操作符调用
	int *p = (int *)sp1::malloc();
	assert(sq1::is_from(p));
	sp1::release_memory();
}

int main(){

	//test_pool_usage();
	test_object_pool_usage();
	return 0;	
}