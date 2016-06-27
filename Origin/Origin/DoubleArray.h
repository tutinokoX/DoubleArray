
#include "KeySort.h"
#include <map>
#include <fstream>
#include <algorithm>
#include <functional>

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
	// --- �_�u���z��̖{�� --- //
	std::vector <int> BASE;
	std::vector <int> CHECK;
	// --- ---------------- --- //

	std::vector <CELL> LIST;						// �o�������X�g
	std::map <std::string, int> CODE;				// �����R�[�h�̊i�[

	std::vector <std::string> KEYGROUP;				// �L�[�W���̊i�[�ϐ�

	std::string FILENAME;
	std::string ENDPOINT;


	// --- �����֐� --- //
	void CodeSet();									// �R�[�h�̊i�[
	void MemoryAllocation(size_t size);				// �������i�[
	void DumpTestRecursion(const int &current);		// �_���v�e�X�g���̍ċA�֐�
	void CodeSortSet();

	bool Comparison(std::string lhs, std::string rhs);
	int count = 0;

public:

	DoubleArray();
	~DoubleArray();

	bool KeygroupSet(const std::string &filename = "KEYSET/sample.keyset" , const std::string &endpoint = "#" );

	void StaticInsert();
	bool Find(const std::string &str);

	bool SaveArray(const std::string &filename);

	void FindTest();
	void DumpTest();
};

