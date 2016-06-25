
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
	// ダブル配列の本体
	std::vector <int> BASE;
	std::vector <int> CHECK;

	std::vector <CELL> LIST;			// 双方向リスト

	std::vector <std::string> KEYGROUP;	// キー集合の格納変数
	std::map <std::string, int> CODE;				// 文字コードの格納

	std::string FILENAME;

	// 内部関数
	void CodeSet();		// コードの格納
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

