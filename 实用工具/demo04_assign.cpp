/*
 * 初始化大量数据 -- assign提供了简便性
 *	
 * assign库重载了'+=', ',', '()'
 */
#include <boost/assign.hpp>
using namespace boost::assign;			// 开启assign库的功能

#include <iostream>
#include <forward_list>
#include <stack>
#include <queue>

using namespace std;

string get_string(){
	return "bbbb";
}

void test_list_insert_usgae(){

	/* vector */
	vector<int> v;
	v += 1,2,3,4,5, 6*6;				// 重载了 '+=' ',' 运算符
										// 含有<表达式> 6*6
	for(auto x : v){
		cout << x << " ";				// [output]1 2 3 4 5 36
	}
	cout << endl;

	/* string */
	string s;
	s += "hello", "world", "!!!!";
	for(auto x : s){
		cout << x << " ";				// [output]h e l l o
	}
	cout << endl;

	/* set */
	set<string> ss;
	ss += "hello", "world", "!!!!", "aaa", "cccc", get_string();
	for(auto x : ss){
		cout << x << " ";				// [output]!!!! aaa bbbb cccc hello world -- 顺序不对
										// <函数对象>
	}
	cout << endl;

	/* map */
	map<int, string> m;
	m += make_pair(3, "third"), make_pair(1, "one"), make_pair(2, "Two");
	for(auto x : m){
		cout << x.first << "-->" << x.second << " ";	// [output]1-->one 2-->Two 3-->third
														// 按键值升序排列
	}
	cout << endl;

	/* 实现原理 */
	// assign库提供 push_back(), push_front(), insert(), 这些函数可作用于同名成员函数的容器
	// boost库仅仅对 C++98 标准的容器 set list vector等重载了 "+="
	// operator+= 作用于容器时调用工厂函数push_back(),产生list_inserter对象,以这个对象为起点
	// 随后的operator() 和 operator, 会被执行


	/* operator() */
	vector<int> v1;
	push_back(v1)(1)(2)(3)(4)(5);

	list<string> l1;
	push_back(l1)("c")("cpp")("lua")("swift")("java");

	forward_list<string> f1;
	push_front(f1)("matrix")("reload");

	set<double> s2;
	insert(s2)(3.14)(0.618)(1.732);

	map<int, string> m1;
	insert(m1)(1, "one")(2, "two");

	
}

void test_generic_list_usage(){
	/* generic_list */
	vector<int> v2 = list_of(1)(2)(3)(4);		//list_of产生generic_list对象

	deque<string> d1 = list_of("power")("a")("b");
	for(auto x : d1){
		cout << x << " ";	// [output]power a b
							// 按键值升序排列
	}
	cout << endl;

	map<int, string> m2 = list_of(make_pair(1, "one")) (make_pair(2, "two"));
	for(auto x : m2){
		cout << x.first << "-->" << x.second << " ";	// [output]1-->one 2-->Two 
														// 按键值升序排列
														// list_of处理map容器不方便
	}
	cout << endl;

	map<int, string> m3 = map_list_of(1, "one")(2, "two")(3, "three");
	map<int, string> m4 = pair_list_of(1, "one")(2, "two")(3, "three");
	for(auto x : m3){
		cout << x.first << "-->" << x.second << " ";	// [output]1-->one 2-->Two 
														// 按键值升序排列
														// map_list_of接受两个参数,省去了make_pair
	}
	cout << endl;
	for(auto x : m4){
		cout << x.first << "-->" << x.second << " ";	// [output]1-->one 2-->Two 
														// 按键值升序排列
														// pair_list_of接受两个参数,省去了make_pair
	}
	cout << endl;
}
int get_int(){
	return 2;
}
/* 重复输入 */
void test_assign_repeat(){
	vector<int> v1 = list_of(1).repeat(3, 2)(4)(5)(6);		// repeat(size_t coutm U v)
	for(auto x : v1){	
		cout << x << " ";	// [output]1 2 2 2 4 5 6    -- 3个 2
							// 按键值升序排列
	}
	cout << endl;

	vector<int> v2 ;
	push_back(v2).repeat(5, get_int());			// repeat(size_t count,  Func f)
	for(auto x : v2){	
		cout << x << " ";	// [output]2 2 2 2 2		-- 5个 2				
	}
	cout << endl;

	vector<int> v3;
	push_back(v3).range(v2.begin(), v2.end());	//range(Sequence begin, Sequence end)
	for(auto x : v3){	
		cout << x << " ";	// [output]2 2 2 2 2		-- 赋值v2序列给v3
	}
	cout << endl;
}

/* 操作非标准容器 */
void test_non_std_usage(){
	stack<int> stk = (list_of(1), (2), (3)).to_adapter();	//list_of()最后调用to_adapter()
	stk += 4, 5 , 6;										// stack可以调用"+=""
	while(!stk.empty()){
		cout << stk.top()<< " ";	// [output]6 5 4 3 2 1		-- 后进先出
		stk.pop();
	}
	cout << endl;

	queue<string> q = (list_of("one")("two")("three")).to_adapter();
	push(q)("four");				// queue调用assign的push
	while(!q.empty()){
		cout << q.front()<< " ";	// [output]one two three four		-- 先进先出
		q.pop();
	}

	/*priority_queue<double> pq = (list_of(3.14)(2.18)(1.28)).to_adapter();
	push(pq)("four");				// priority_queue调用assign的push
	while(!pq.empty()){
		cout << pq.top()<< " ";	// [output]one two three four		-- 先进先出
		pq.pop();
	}*/
}

/* 接受引用参数 */
void test_assign_ref_param(){
	int a = 1, b = 2, c = 3;
	vector<int> v = ref_list_of<3>(a)(b)(c);
	for (auto &x :v){
		x += 1;				//每个元素加1
	}
	for(auto x : v){	
		cout << x << " ";	// [output]2 3 4		-- 赋值v2序列给v3
	}
	cout << endl;
	cout << a << " " << b << " " << c << endl;		// 1 2 3
}

int main(){
	//test_list_insert_usgae();
	//test_generic_list_usage();
	//test_assign_repeat();
	//test_non_std_usage();
	test_assign_ref_param();
	return 0;
}