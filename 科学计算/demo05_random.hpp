/*
 *	random
 *	rand48, mt19937, lagged_fibonaccil9937
 */

 #include <boost/random.hpp>
 using namespace boost;

 #include <iostream>
 using namespace std;

void test_random_number(){
	mt19937 rng(time(0));

	cout << mt19937::min() << "<->" << mt19937::max() << endl;

	for(int i = 0; i < 100; ++i){
		cout << rng() << ", ";
	}
	rng.discard(5);

	vector<int> vec(10);
	rng.generate(vec.begin(), vec.end());
}

//随机数分布器
void test_fenbu_usage(){
	mt19937 rng(time(0));
	random::uniform_int_distribution<> ui(0, 255);		// 0-255之间的整数
	for(int i = 0; i < 100; ++i){
		cout << ui(rng) << ", ";
	}
}

//变量发生器
void test_variate_generator(){
	mt19937 rng(time(0));
	random::uniform_int_distribution<> ui(0, 255);	

	variate_generator<mt19937, random::uniform_int_distribution<>> gen(rng, us);
	for(int i = 0; i < 100; ++i){
		cout << gen() << ", ";
	}
}

//产生一定长度的随机数据块
template<typename Rng>
void rand_bytes(unsigned char * buf, int buf_len){

	typedef variate_generator<Rng, uniform_smallint<>> var_gen_t;

	//static变量 -- 保证gen随机数发生器会初始化一次,避免了多次构造的代价
	static var_gen_t gen(
						  Rng((typename Rng::result_type)(time(0)),
						  uniform_smallint<>(1, 255)
						);

	for(int i = 0; i < buf_len; ++i){
		buf[i] = gen();
	}
}

// 真随机数发生器

 int main(){

 	//test_random_number();
 	test_fenbu_usage();
 	return 0;
 }