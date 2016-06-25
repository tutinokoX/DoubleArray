

#include "DoubleArray.h"

using namespace std;

int main() {

	DoubleArray da;

	da.KeygroupSet("KEYSET/ipadic-2.7.0-titles-100000" , "p");
	da.StaticInsert();

	da.FindTest();
	da.DumpTest();

	//da.~DoubleArray();
}

