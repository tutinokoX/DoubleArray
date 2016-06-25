

#include "DoubleArray.h"
#include "KeySort.h"

using namespace std;

int main() {

	vector <string> str_group;

	str_group.push_back("ag");
	str_group.push_back("age");
	str_group.push_back("bad");
	str_group.push_back("badge");
	str_group.push_back("bot");


	KeySort test(str_group);

	test.DataCheck();

}

