

#include "DoubleArray.h"

using namespace std;

int main(int argc , char *argv[]) {

	if(argc != 3) {
		cerr << "引数が違います" << endl;
		cerr << "./da [keyset_pass] [end_char]" << endl;
		cerr << endl << " now => ";
		for(int i = 0 ; i < argc ; i++) cerr << argv[i] << " ";
		cerr << endl;
		return -1;
	}
	string file_pass = argv[1];
	string end_char = argv[2];


	DoubleArray da;

	da.KeygroupSet(file_pass , end_char);
	da.StaticInsert();

	da.FindTest();
	da.DumpTest();

	//da.~DoubleArray();
}

