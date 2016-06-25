
#include "KeySort.h"
#include <map>
#include <fstream>
#include <algorithm>

struct CELL_org
{
	struct CELL *next;
	struct CELL *prev;
};

struct CELL
{
	int next;
	int prev;
};


class DoubleArray
{
private:
	// �_�u���z��̖{��
	std::vector <int> BASE;
	std::vector <int> CHECK;

	std::vector <CELL> LIST;			// �o�������X�g

	std::vector <std::string> KEYGROUP;	// �L�[�W���̊i�[�ϐ�
	std::map <std::string, int> CODE;				// �����R�[�h�̊i�[

	std::string FILENAME;

	// �����֐�
	void CodeSet();		// �R�[�h�̊i�[
	void MemoryAllocation(size_t size);
	void DumpTestRecursion(const int &current);

	int count = 0;

public:
	DoubleArray();
	~DoubleArray();

	bool KeygroupSet(const std::string &filename = "KEYSET/sample.keyset");

	void StaticInsert();
	bool Find(const std::string &str);
	void FindTest();

	void DumpTest();
};

