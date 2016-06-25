

#include "DoubleArray.h"

using namespace std;

int main() {

	DoubleArray da;

	da.KeygroupSet("KEYSET/test.num");
	da.StaticInsert();

	da.FindTest();
	da.DumpTest();

	//da.~DoubleArray();
}

