/*
 *	UUID(Universally Unique Identifier)--GUID,128位数字(16字节),全球唯一标识符
 * 	用途:数据库记录RowID 表示某个系统的用户,表示网络传输消息,唯一的标识一个实体
 *
 *  生成器 -- 创建唯一的生成器
 *
 *  生成UUID必须通过生成器,但是没有效率,因此我们可以从UUID类派生自己的类
 *
 *  将UUID转换字符串
 * 
 *  SHA1算法将任意的文本压缩成一个只有20字节(160位)的摘要,防篡改,身份鉴定
 */

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
using namespace boost::uuids;

#include <boost/lexical_cast.hpp>
#include <iostream>
using namespace std;
void test_uuid_usages(){
	uuid u;
	assert(u.size() == 16 && u.static_size() == 16);	//size和static_size总返回16

	vector<unsigned char> v(16, 7);
	std::copy(v.begin(), v.end(), u.begin());			// 标准复制方法
	assert(u.data[0] == u.data[1] && u.data[15] == 7);

	cout << u << endl;									//uuid重载了输出流
	std::fill_n(u.data + 10, 6, 8);						// 
	cout << u << endl;	

	assert(!u.is_nil());								// is_nil是否无效

	cout << u.variant() << endl;						// UUID的变体号--表示UUID的布局类型
	cout << u.version() << endl;						// UUID的算法标本
}


void test_generator_uuid(){
	//NIL生成器
	uuid u = nil_generator()();		//nil_generator是一个类名
	assert(u.is_nil());

	u = nil_uuid();
	assert(u.is_nil());

	//字符串生成器
	string_generator sgen;  //没有连字符的全十六进制数字
	try{
		
		uuid u1 = sgen("0123456789abcdef0123456789abcdef");
		cout << u1 << endl;
	}catch(std::runtime_error& e){			// 跑出runtime_error异常
		cout << "1" << "-";
		std::cout << e.what() << endl;
	}
	
	try{
		//在第5 7 9 11字节前是使用连字符,其他位置不行
		uuid u2 = sgen("01234567-89ab-cdef-0123-456789abcdef");
		cout << u2 << endl;
	}
	catch(std::runtime_error& e){
		cout << "2" << "-";
		std::cout << e.what() << endl;
	}

	try{
		uuid u3 = sgen(L"{01234567-89ab-cdef-0123-456789abcdef}");
		cout << u3 << endl;
	}
	catch(std::runtime_error& e){
		cout << "3" << "-";
		std::cout << e.what() << endl;
	}

	//名字生成器 -- 为一个组织内的所有成员创建UUID标识
	uuid www_xxx_com = string_generator()("{01234567-89ab-cdef-0123-456789abcdef}");
	name_generator ngen(www_xxx_com);

	uuid u4 = ngen("mario");
	assert(!u4.is_nil() && u4.version() == uuid::version_name_based_sha1);

	uuid u5 = ngen("link");
	cout << u5 << endl;


	//随机生成器 -- basic_random_generator<T> 模板类.T为随机数生成器
	random_generator rgen;			//random_generator常用的 
	uuid u6 = rgen();

	assert(u6.version() == uuid::version_random_number_based);
	cout << u6 << endl;

}

//继承UUID 产生特定的UUID号
class uuid_t : public uuid{
private:
	static random_generator& rand_uuid(){
		static random_generator gen;
		return gen;
	}

	static string_generator& string_uuid(){
		static string_generator gen;
		return gen;
	}
public:
	uuid_t():uuid(rand_uuid()()){}
	uuid_t(int):uuid(nil_uuid()){}
	uuid_t(const char* str):uuid(string_uuid()(str)){}

	uuid_t(const uuid& u, const char* str):uuid(name_generator(u)(str)){}

	operator uuid(){
		return static_cast<uuid&>(*this);
	}
	operator uuid()const{
		return static_cast<const uuid&>(*this);
	}

};


void test_uuid_to_string(){
	random_generator rgen;			//random_generator常用的 
	uuid u1 = rgen();

	cout << to_string(u1) << endl;	//to_wstring()

	cout << boost::lexical_cast<uuid>("01234567-89ab-cdef-0123-456789abcdef") << endl;	
	cout << boost::lexical_cast<string>(u1) << endl;
}

void test_sha1_usage(){
	using namespace boost::uuids::detail;

	sha1 sha;

	const char *szMsg = "a short message";
	sha.process_byte(0x10);
	sha.process_bytes(szMsg, strlen(szMsg));
	sha.process_block(szMsg, szMsg+strlen(szMsg));

	unsigned int digest[5];
	sha.get_digest(digest);
	for(int i = 0; i < 5; ++i){
		cout << hex << digest[i];
	}
}


int main(){
	//test_uuid_usages();
	//test_generator_uuid();
	//test_uuid_to_string();
	test_sha1_usage();

	return 0;
}