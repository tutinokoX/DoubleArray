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

	// ���O���ɂ��ďd��������
	sort(KEYGROUP.begin(), KEYGROUP.end());
	KEYGROUP.erase(unique(KEYGROUP.begin(), KEYGROUP.end()), KEYGROUP.end());

	// ���񃁃����m��
	MemoryAllocation(KEYGROUP.size());

	// �R�[�h�̊i�[
	CodeSet();


	
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
	for (auto str : ks.Output()) {

		int next = 0;
		int base = 0;
		size_t ok_c = 0;
		vector <int> buf_task;
		buf_task.clear();
		search_location = first_check;

		// CHECK�̏�Ԃ���i�[�ł���ꏊ��T��
		while (1) {

			base = search_location - CODE[str.front()];
			if (base < 0) base = 0;

			for (auto one : str) {

				next = base + CODE[one];
				buf_task.push_back(next);

				if (CHECK.size() > (size_t)next) if (CHECK[next] >= 0) break;
				ok_c++;
			}
			if (ok_c == str.size()) break;
			search_location = LIST[search_location].next;
			ok_c = 0;
			buf_task.clear();
		}

		// �������Ǘ�
		if (next >= CHECK.size()) MemoryAllocation(next + 100);


		// �_�u���z��Ɋi�[
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
		if (LIST.size() - 1 > LIST[0].prev) MemoryAllocation(LIST.size() + 10);

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


void DoubleArray::FindTest(){

	size_t count = 0;
	for (auto str : KEYGROUP) {
		// cout << str << " : " << (Find(str) ? "ok" : "no") << endl;;
		if (Find(str)) count++;
	}


	cout << "*************************************************" << endl;
	cout << "[ �����e�X�g ]" << endl;
	cout << "	file   :  " << FILENAME << endl;
	cout << "	result :  " << ((double)count * (double)(100.0 / KEYGROUP.size())) << " [%]  ( "
		<< count << "/" << KEYGROUP.size() << " )" << endl;
	cout << endl;
}



void DoubleArray::DumpTestRecursion(const int &_current ) {

	// �����m�F
	if (BASE[_current] == -1) {
		count++;
		return;
	}

	// �S��������
	for (auto code : CODE) {

		// ���̕����̏ꏊ�m�F�@����Ȃ�ċA�C���̏ꏊ���J�����g�ɂ���
		int next = BASE[_current] + CODE[code.first];
		if (CHECK[next] == _current ) DumpTestRecursion( next );
	}

}

void DoubleArray::DumpTest() {
	
	DumpTestRecursion(0);

	cout << "*************************************************" <<endl;
	cout << "[ �_���v�e�X�g ]" << endl;
	cout << "	file   :  " << FILENAME << endl;
	cout << "	result :  " << ((double)count * (double)(100.0 / KEYGROUP.size())) << " [%]  ( " 
		<< count << "/" << KEYGROUP.size() << " )" << endl;
	cout << endl;
}



