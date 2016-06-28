

#include "DoubleArray.h"

using namespace std;

int main(int argc , char *argv[]) {

	DoubleArray da;

	if (argc > 2) {
		cerr << " err : input ... ( > " << argv[0] << " [filename] )" << endl;
		return -1;
	}

	string filename;
	if(argc == 2) filename = argv[1];
	// else filename = "KEYSET/test.num";
	// else filename = "KEYSET/keyset.num";
	// else filename = "KEYSET/ipadic-2.7.0-titles-100000";
	else filename = "KEYSET/wordnet-3.0-word-100000";

	da.KeygroupSet(filename);
	da.StaticInsert();

	da.FindTest();
	da.DumpTest();

	da.SaveArray("code_sort");

	//da.~DoubleArray();
}

