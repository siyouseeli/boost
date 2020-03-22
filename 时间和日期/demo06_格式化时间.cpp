
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
	date d(2020, 3, 15);
	date_facet* dfacet = new date_facet("%Y年%m月%d日");
	cout.imbue(locale(cout.getloc(), dfacet));
	cout << d << endl;
	
	time_facet* dfacet_ = new time_facet("%Y年%m月%d日%H点%M分%S秒%F秒");
	cout << ptime(date(2020, 3, 15)) + hours(1) + minutes(30) + seconds(10) + millisec(100) << endl;
}