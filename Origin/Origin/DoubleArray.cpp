#include "DoubleArray.h"


using namespace std;

DoubleArray::DoubleArray()
{
	CHECK.push_back(0);
	BASE.push_back(0);
}


DoubleArray::~DoubleArray()
{
	vector <int>().swap(BASE);
	vector <int>().swap(CHECK);
	vector <CELL>().swap(LIST);
}


void DoubleArray::CodeSet() {

	CODE.clear();

	for (int i = 0; i < 256; i++) {

		// cout << (unsigned char)i << endl;
		string str;
		str = (unsigned char)i;
		CODE.insert(pair<string, int>(str, i));
	}

}

void DoubleArray::CodeSortSet() {

	CODE.clear();

	multimap<string ,int>  CODE_sort;
	multimap<int, string> CODE_buf;
	//vector <int> CODE_sort;

	for (auto key : KEYGROUP) {

		// for(int i= 0 ; i < key.length() ; i++){
		string one;
		while(1){
			if (key.empty()) break;
			char _one = key.front();
			// string one = (key.substr(i, 1).c_str()) & 0xff;
			one = _one & 0xff;
			auto itr = CODE_sort.find(one);
			if (itr != CODE_sort.end()) {

				itr->second++;
			}
			else {
				CODE_sort.insert(pair<string , int>(one , 1));
			}
			key.erase(0, 1);
			one.clear();
			//CODE_sort[one] ++;
		}
	}

	for (auto code : CODE_sort) {

		CODE_buf.insert(pair<int , string>(code.second, code.first));
	}


	for (auto c : CODE_buf) {

		cout << c.first << " , " << c.second << endl;
	}

	int c_count = 1;

	for (auto code : CODE_buf) {

		CODE.insert( pair<string, int>(code.second,  CODE_buf.size()+1 - c_count));
		c_count++;
	}
	CODE.insert(pair<string, int >(ENDPOINT, 0));

	
	for (auto cod : CODE) {

		cout << cod.first << " , " << cod.second << endl;
	}

	for (int i = 0; i < 256; i++) {

		string str;
		str = (unsigned char)i;
		auto itr = CODE.find(str);
		if (itr == CODE.end()) {
			CODE.insert(pair<string, int>(str, c_count));
			c_count++;
		}

	}


}

void DoubleArray::MemoryAllocation(size_t size) {

	CELL buf;
	CHECK.resize(size, -1);
	BASE.resize(size, -2);

	if (LIST.size() > 0) {

		LIST[LIST[0].prev].next = (int)LIST.size();
		buf.next = (int)LIST.size() + 1;
		buf.prev = LIST[0].prev;
		LIST.push_back(buf);
	}

	for (size_t i = LIST.size(); i < size; i++) {

		buf.next = i + 1;
		buf.prev = i - 1;
		LIST.push_back(buf);
	}

	LIST[0].prev = LIST.size() - 1;
	LIST[LIST.size() - 1].next = 0;
}



// 自作比較関数
bool DoubleArray::Comparison(std::string lhs, std::string rhs) {

	string a, b;
	string buf_a, buf_b;
	a = lhs.front();
	b = rhs.front();


	while (1) {
		buf_a = a.front();
		buf_b = b.front();
		
		
		if (CODE[buf_a] != CODE[buf_b]) {
		return (CODE[buf_a] < CODE[buf_b]) ? true : false;
		}
		
		
		a.erase(0, 1);
		if (a.empty()) return true;
		b.erase(0, 1);
		if (b.empty()) return false;
	}
}

/*
// 自作比較関数
bool Comp(std::string lhs, std::string rhs) {

	string a, b;
	string buf_a, buf_b;
	a = lhs.front();
	b = rhs.front();

	while (1) {
		buf_a = a.front();
		buf_b = b.front();

		
		if (&CODE[buf_a] != &CODE[buf_b]) {
		return (&CODE[buf_a] < &CODE[buf_b]) ? true : false;
		}
		

		a.erase(0, 1);
		if (a.empty()) return true;
		b.erase(0, 1);
		if (b.empty()) return false;
	}
}
*/

bool DoubleArray::KeygroupSet(const string &filename , const string &endpoint) {

	FILENAME = filename;
	ENDPOINT = endpoint;
	KEYGROUP.clear();

	ifstream ifs(filename);
	if (ifs.fail()) {
		cerr << "err : file open -> " << filename << endl;
		return false;
	}

	string str;
	while (ifs, getline(ifs, str)) {

		KEYGROUP.push_back(str);
	}

	// コードの格納
	// CodeSet();
	CodeSortSet();

	// 名前順にして重複を消去
	sort(KEYGROUP.begin(), KEYGROUP.end());
	KEYGROUP.erase(unique(KEYGROUP.begin(), KEYGROUP.end()), KEYGROUP.end());


	// コードのソート
	for (int i = 0; i < KEYGROUP.size(); i++) {

		for (int j = KEYGROUP.size() - 1; j > i; j--) {

			if (!Comparison(KEYGROUP[j - 1], KEYGROUP[j])) {
				string buf = KEYGROUP[j];
				KEYGROUP[j] = KEYGROUP[j - 1];
				KEYGROUP[j - 1] = buf;
			}
		}
	}

	cout << "KYEGROUP" << endl;
	for (auto key : KEYGROUP) {
		cout << key << endl;
	}

	//sort(KEYGROUP.begin(), KEYGROUP.end() , Comparison );

	// 初回メモリ確保
	MemoryAllocation(( KEYGROUP.size() > CODE.size() ) ? KEYGROUP.size() : CODE.size() );

	return true;
}



void DoubleArray::StaticInsert() {

	int current = 0;
	int first_check = 0;
	int search_location = 0;

	vector <int> next_task;
	next_task.push_back(current);

	for (string& str : KEYGROUP) str += ENDPOINT;
	KeySort ks(KEYGROUP , ENDPOINT);
	for (vector<string> str : ks.Output()) {

		int next = 0;
		int base = 0;
		size_t ok_c = 0;
		vector <int> buf_task;
		buf_task.clear();
		search_location = first_check;
		int max_next = 0;

		// CHECKの状態から格納できる場所を探す
		while (1) {

			base = search_location - CODE[str.front()];
			if (base < 0) base = 0;

			for (vector<string>::iterator one = str.begin(); one != str.end(); one++) {

				next = base + CODE[*one];
				buf_task.push_back(next); 
				if (buf_task[max_next] < next) max_next = distance(str.begin(), one);

				if (CHECK.size() > (size_t)next) if (CHECK[next] >= 0) break;
				ok_c++;
			}
			if (ok_c == str.size()) break;
			search_location = LIST[search_location].next;
			if (search_location == 0) search_location = LIST.size();
			ok_c = 0;
			max_next = 0;
			buf_task.clear();
		}

		
		// メモリ管理
		if (buf_task[max_next] >= CHECK.size()) MemoryAllocation(buf_task[max_next] + 100);


		// ダブル配列に格納
		BASE[current] = base;
		for (vector <int>::iterator itr = buf_task.begin(); itr != buf_task.end(); itr++) {
	
			CHECK[*itr] = current;
			LIST[LIST[*itr].prev].next = LIST[*itr].next;
			LIST[LIST[*itr].next].prev = LIST[*itr].prev;
			LIST[*itr].next = 0;
			LIST[*itr].prev = 0;

			if (str[distance(buf_task.begin(), itr)] == ks.EndPoint()) BASE[*itr] = -1;
			else next_task.push_back(*itr);
		}

		next_task.erase(next_task.begin());
		current = next_task.front();
		// if (LIST.size() - 1 > LIST[0].prev) MemoryAllocation(LIST.size() + 10);

	}
	CHECK[0] = -1;
}


bool DoubleArray::Find(const string &str) {

	string buf_str = str;
	int next = 0;
	int current = 0;

	string one;
	while (1) {

		if (BASE[next] < 0) break;

		one = buf_str.front();
		next = BASE[current] + CODE[one];
		if (CHECK[next] != current) return false;
		
		buf_str.erase(0, 1);
		one.clear();
		current = next;
	}

	return true;
}

bool DoubleArray::SaveArray(const string &filename) {

	ofstream ofs_base , ofs_check , ofs_code;
	ofs_base.open("./OUTPUT/" + filename+"_BASE.txt");
	ofs_check.open("./OUTPUT/"+ filename + "_CHECK.txt");
	ofs_code.open("./OUTPUT/" + filename + "_CODE.txt");

	if (ofs_base.fail() || ofs_check.fail() , ofs_code.fail()) {

		cerr << "err : input file -> " << filename << endl;
		return false;
	}

	for (auto base : BASE) {
		ofs_base << base << endl;
	}
	for (auto check : CHECK) {
		ofs_check << check << endl;
	}
	for (auto code : CODE) {
		ofs_code << code.second << " : " << code.first << endl;
	}

	return true;
}

void DoubleArray::FindTest(){

	size_t count = 0;
	for (auto str : KEYGROUP) {
		cout << str << " : " << (Find(str) ? "ok" : "no") << endl;;
		if (Find(str)) count++;
	}


	cout << "*************************************************" << endl;
	cout << "[ 検索テスト ]" << endl;
	cout << "	file   :  " << FILENAME << endl;
	cout << "	result :  " << ((double)count * (double)(100.0 / KEYGROUP.size())) << " [%]  ( "
		<< count << "/" << KEYGROUP.size() << " )" << endl;
	cout << endl;
}



void DoubleArray::DumpTestRecursion(const int &_current ) {

	// 文末確認
	if (BASE[_current] == -1) {
		count++;
		return;
	}

	// 全文字検索
	for (auto code : CODE) {

		// 次の文字の場所確認　あるなら再帰，その場所をカレントにする
		int next = BASE[_current] + CODE[code.first];
		if (CHECK[next] == _current ) DumpTestRecursion( next );
	}

}

void DoubleArray::DumpTest() {
	
	DumpTestRecursion(0);

	cout << "*************************************************" <<endl;
	cout << "[ ダンプテスト ]" << endl;
	cout << "	file   :  " << FILENAME << endl;
	cout << "	result :  " << ((double)count * (double)(100.0 / KEYGROUP.size())) << " [%]  ( " 
		<< count << "/" << KEYGROUP.size() << " )" << endl;
	cout << endl;
}



