/*
 * 实现操作符重载必须具有对称性, 如实现==,就必须实现!= .....
 * 但如果需要全部实现,则需要很多的代码量
 * boost.operators实现了从已知的操作符而推导出其他同性质的操作,减少了代码量
 *
 *	用法, 通过继承类的,实现特定的操作符重载;
 */
#include <boost/operators.hpp>
#include <boost/logic/tribool.hpp>
using namespace boost;

#include <iostream>
using namespace std;
//template<typename T>
//class point : boost::less_than_comparable<point<T>>		// 模板来继承 less_than_comparable的参数写法
class point : less_than_comparable<point>,
			 equality_comparaable<point>{	//less_than_comparaable 要求实现 < 操作符
											//<= >= >自动推导出
	int x, y, z;
public:
	explicit point(int a= 0, int b = 0, int c = 0) : x(a), y(b), z(c){}
	void print() const{
		cout << x << " " << y << " " << z << endl;
	}
public:
	friend bool operator<(const point& l, const point& r){
		return (l.x*l.x + l.y*l.y+l.z+l.z < r.x*r.x+r.y*r.y+r.z*r.z);
	}
	friend bool operator==(const point& l, const point& r){		//新增相等关系
		return (l.x == r.x && l.y==r.y && l.z==r.z);
	}
};
//解决 多重继承问题的多个模板参数
class Point1 : less_than_comparable<point,equality_comparaable<point,addable<point,subtriactable<point>>>>{};


/* 解引用*/
template<typename T>
class my_smart_ptr: public dereferenceable<my_smart_ptr<T>, T*>{	//必须public继承dereferenceable
																	//T*为返回的类型
	T *p;
public:
	my_smart_ptr(T *x) : p(x){}
	~my_smart_ptr(){delete p;}
	T& operator*() const{					// 必须实现*操作符
		return *p;
	}
};

/* 下表操作符 */
template<typename T>
class my_smart_array: public indexable<my_smart_array<T>, int, T&>{
		T *p;
public:
	typedef my_smart_array<T> this_type;
	typedef T*				 iter_type;
	my_smart_array(T *x) : p(x){}
	~my_smart_array(){delete p;}
	friend iter_type operator+(const this_type& a, int n){
		return a.p + n;							// 返回一个迭代器类型	, 可以使用operator*操作
	}
};

/* 布尔转型操作符 */

/* 二元操作符 */
class point2 : totally_ordered<point, 
					addable1<point>, 		// 一个模板的参数的概念类
					addable2<point, int>>{	// 两个模板的参数的概念类
public:
	//...
	point& operator+=(const int& r){
		x += r;
		y += r;
		z += r;
		return *this;
	}
}
void test_less_than_comparable(){
	point p0, p1(1,2,3), p2(3, 0, 5), p3(3,2,1);
	assert(p0 < p1 && p1 < p2);
	assert(p2 > p0);
	assert(p1 <= p3);
	assert(!(p1<p3)&&!(p1>p3));
	assert(p1 != p2);
}

int main(){
	test_less_than_comparable();
	return 0;
}