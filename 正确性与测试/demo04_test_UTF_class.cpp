#define BOOST_TEST_MAIN			//必须定义主测试套件 
#include <boost/test/included/unit_test.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/assign.hpp>
using namespace boost;
#include <iostream>
#include <memory>
using namespace std;
//全局测试夹具类
struct global_fixture{
	global_fixture(){
		cout << "global setup" << endl;
	}
	~global_fixture(){
		cout << "global teardown" << endl;
	}
};

//定义全局夹具
BOOST_GLOBAL_FIXTURE(global_fixture);

//定义测试套件级别的夹具
struct assign_fixture{
	assign_fixture(){
		cout << "suit setup" << endl;
	}
	~assign_fixture(){
		cout << "suit teardonw" << endl;
	}
	
	vector<int> v;
};

BOOST_FIXTURE_TEST_SUITE(s_assign, assign_fixture)
BOOST_AUTO_TEST_CASE(t_assign1){
	using namespace boost::assign;
	
	v += 1,2,3,4;
	BOOST_CHECK_EQUAL(v.size(), 4);
	BOOST_CHECK_EQUAL(v[2], 3);
}
BOOST_AUTO_TEST_CASE(t_assign2){
	using namespace boost::assign;
	
	push_back(v)(10)(20)(30);
	BOOST_CHECK_EQUAL(v.empty(), false);
	BOOST_CHECK_LT(v[0], v[1]);
}
BOOST_AUTO_TEST_SUITE_END()

int test_main(int argc, char* argv[]){}