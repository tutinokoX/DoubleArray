#include <vector>

struct CELL
{
	int *next;
	int *prev;
};

class DoubleArray
{
private:
	// ダブル配列の本体
	std::vector <int> BASE;
	std::vector <int> CHECK;

	std::vector <CELL> LIST;	// 双方向リスト

	std::vector <std::string> KEYGROUP;	// キー集合の格納変数
	std::vector <std::string> CODE;		// 文字コードの格納



public:
	DoubleArray();
	~DoubleArray();

	bool data_set(const std::string &filename);

	void static_insert();
	bool find(const std::string &str);
	void find_test();
	void dump_test();
};

