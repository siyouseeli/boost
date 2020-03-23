/*
 *	CRC
 *
 */

#include <boost/crc.hpp>
using namespace boost;

#include <iostream>
using namespace std;

int main(){

	crc_32_type crc32;

	cout << hex;
	cout << crc32.checksum() << endl;

	crc32.process_byte('a');
	cout << crc32.checksum() << endl;

	crc32.process_bytes("1234567980", 10);
	cout << crc32.checksum() << endl;

	char szCh[] = "1234567890";
	crc32.process_block(szCh, szCh+10);
	cout << crc32.checksum() << endl;
	cout << crc32() << endl;
	
	crc32.reset();
	cout << crc32() << endl;

 	return 0;
}