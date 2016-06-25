#include <vector>

struct CELL
{
	int *next;
	int *prev;
};

class DoubleArray
{
private:
	// �_�u���z��̖{��
	std::vector <int> BASE;
	std::vector <int> CHECK;

	std::vector <CELL> LIST;	// �o�������X�g

	std::vector <std::string> KEYGROUP;	// �L�[�W���̊i�[�ϐ�
	std::vector <std::string> CODE;		// �����R�[�h�̊i�[



public:
	DoubleArray();
	~DoubleArray();

	bool data_set(const std::string &filename);

	void static_insert();
	bool find(const std::string &str);
	void find_test();
	void dump_test();
};

