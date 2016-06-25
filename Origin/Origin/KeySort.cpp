/*

����̃v���O�����ł͍����D��T���ŕ��ёւ����s�������C
���D��ł̕��ёւ����l�����̂ł�����̃v���O�������\�z��ڕW�Ƃ���D

�X�s�[�h�������ق����̗p����\��


���݂̃v���O�����ł͕�����������Ƃ��đ�����Ă��邪�C��������ł������̎��Ԃ�
�g���̂ŁC���ёւ��r���ő���ł�����@���l����D
*/

#include "KeySort.h"

using namespace std;


// �R���X�g���N�^
KeySort::KeySort(const vector <string> &str_group, const string &endpoint)
{
	vector <string> _str_group = str_group;
	for (string& str : _str_group) str += endpoint;
	_str_group.push_back("\n");
	recursion_sort(_str_group);
}


// �f�X�g���N�^
KeySort::~KeySort()
{
	vector<vector<string>>().swap(CONTAINER);
}


// ----------------------------------------------------------------------------
// ���O	�F recursion_sort
// �@�\	�F ������Q����ёւ��̂��߂̍ċA�֐�
// ����	�F (in)	const vector <string>	$str_group	: �i�[���镶����Q
// �o��	�F �Ȃ�
//
// ���l	�F ���̊֐��͍ċA�ɂ���ĕ��������בւ���
//		   ���בւ���������́C�N���X�ϐ��́uCONTAINER�v�Ɋi�[�����
//		�@ �ċA�̐[���Əo���������Ԃ�2�����z���\��
// ----------------------------------------------------------------------------
void KeySort::recursion_sort(const vector <string> &str_group) {

	vector <string> buf_str_group;
	string now;
	string buf;
	string buf_str;

	for (auto str : str_group) {

		if (str.empty()) continue;

		// ������̍ŏ��̕����݂̂��擾
		now = str.front();

		// �擪�̕����񂪕ύX�����ꏊ�������͕���������ׂĊm�F������
		if ((buf != now && !buf.empty()) || now == "\n") {

			buf_str += buf;		// �i�[������𑝂₷
			hierarchy++;		// �K�w���グ��

			// �������̊m��
			if (max_hierarchy < hierarchy) {
				CONTAINER.resize(hierarchy);
				max_hierarchy = hierarchy;
			}

			// �V�����K�w�ֈړ��@�����񂪂Ȃ���΋�̂܂܈ړ�
			if (!buf_str_group.empty()) buf_str_group.push_back("\n");
			recursion_sort(buf_str_group);
			buf_str_group.clear();
		}

		// �V�����K�w�̂��߂̕�������m�� �擪�������폜���Ċi�[
		if (!str.substr(1).empty()) buf_str_group.push_back(str.substr(1));

		buf = now;
	}

	// �����񂪊i�[����Ă��Ȃ���΁C�K�w���ЂƂ����Ė߂�
	if (buf.empty()) {
		hierarchy--;
		return;
	}

	// �R���e�i�Ɋi�[
	CONTAINER[hierarchy].push_back(buf_str);
	hierarchy--;
	return;
}

void KeySort::DataCheck() {

	for (auto hie : CONTAINER) {
		for (auto str : hie) {
			
			cout << str << endl;
		}

	}
}