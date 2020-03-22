
/*
 * minmax_element是一个算法族-- last__first,同时返回容器中的最大值和最小值
 *
 *	
 */
#include <boost/algorithm/minmax_element.hpp>
using namespace boost;
#include <iostream>
#include <vector>
#include <map>
using namespace std;
void test_minmax_element(){
	vector<int> v = {633, 90, 67, 83, 2, 100};
	auto x = minmax_element(v.begin(), v.end());
	
	cout << "max element="<<*x.first << ", " << "min element=" << *x.second << endl;
}


int main(int argc, char *argv[]) {
	test_minmax_element();
}