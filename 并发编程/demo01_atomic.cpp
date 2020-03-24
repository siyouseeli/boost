/*
 *	atomic 实现了C++标准的原子操作库,封装了不同计算机硬件的
 *	底层操作原语,提供了跨平台的原子操作功能.
 *
 *	atomic可以把类型T的操作原子化,但不是任意的类型都可以原子化
 *		标量类型 -- C++的内件算数类型,枚举,指针
 *		只有平方 拷贝/转移构造,赋值和析构函数得类,并可以使用memcmp执行比较操作
 *
 *	并发顺序一致性:
 *		每个atomic的成员函数有一个memory_order参数(操作符重载函数除外) 
 */

#include <boost/atomic.hpp>
using namespace boost;


#include <iostream>
using namespace std;

int main(){

	atomic<int> a(10);
	cout << a.load() << endl;

	atomic<long> l;
	cout << l.load() << endl;		// 初值不确定

	atomic_int a1(10);
	cout << a1.load() << endl;

	atomic_long a2(40);
	cout << a2.load() << endl;

	a.store(20);
	cout << a.load()  << endl;

	a.store(100);
	cout << a.load() << endl;

	atomic_bool b(false);
	assert(!b);


	atomic<int> i1(100);
	assert(i1.exchange(200) == 100);	//exchange()交换成功,则返回原有的值
	assert(i1.load() == 200);

	//atomic<int> -- 特化操作
	atomic<int> n1(100);
	assert(n1.fetch_add(10) == 100);	//fetch_add()加法操作返回原值
	cout << n1.load() << endl;			// 110

	assert(++n1 == 111);
	assert(!(n1++ == 112));
	cout << n1.load() << endl;			//112

	return 0;
}