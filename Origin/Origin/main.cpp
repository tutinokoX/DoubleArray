

#include "DoubleArray.h"

using namespace std;

int main() {

	DoubleArray da;

	da.KeygroupSet("KEYSET/wordnet-3.0-word-100000");
	da.StaticInsert();

	da.FindTest();
	da.DumpTest();

	//da.~DoubleArray();
}

