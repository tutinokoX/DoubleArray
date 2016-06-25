/*

今回のプログラムでは高さ優先探索で並び替えを行ったが，
幅優先での並び替えも考えらるのでそちらのプログラムも構築を目標とする．

スピードが速いほうを採用する予定


現在のプログラムでは文末文字を印として代入しているが，代入処理でも多少の時間を
使ってしまう．並び替え途中で代入できる方法を考える．
*/

#include "KeySort.h"

using namespace std;


// コンストラクタ
KeySort::KeySort(const vector <string> &str_group, const string &endpoint)
{
	_endpoint = endpoint;
	vector <string> _str_group = str_group;
	_str_group.push_back("\n");
	recursion_sort(_str_group);
}


// デストラクタ
KeySort::~KeySort()
{
	vector<vector<string>>().swap(CONTAINER);
}


// ----------------------------------------------------------------------------
// 名前	： recursion_sort
// 機能	： 文字列群を並び替えのための再帰関数
// 引数	： (in)	const vector <string>	$str_group	: 格納する文字列群
// 出力	： なし
//
// 備考	： この関数は再帰によって文字列を並べ替える
//		   並べ替えた文字列は，クラス変数の「CONTAINER」に格納される
//		　 再帰の深さと出現した順番で2次元配列を表現
// ----------------------------------------------------------------------------
void KeySort::recursion_sort(const vector <string> &str_group) {

	vector <string> buf_str_group;
	string now;
	string buf;
	string buf_str;

	for (auto str : str_group) {

		if (str.empty()) continue;

		// 文字列の最初の文字のみを取得
		now = str.front();

		// 先頭の文字列が変更した場所もしくは文字列をすべて確認したら
		if ((buf != now && !buf.empty()) || now == "\n") {

			buf_str += buf;		// 格納文字列を増やす
			hierarchy++;		// 階層を上げる

			// メモリの確保
			if (max_hierarchy < hierarchy) {
				CONTAINER.resize(hierarchy);
				max_hierarchy = hierarchy;
			}

			// 新しい階層へ移動　文字列がなければ空のまま移動
			if (!buf_str_group.empty()) buf_str_group.push_back("\n");
			recursion_sort(buf_str_group);
			buf_str_group.clear();
		}

		// 新しい階層のための文字列を確保 先頭文字を削除して格納
		if (!str.substr(1).empty()) buf_str_group.push_back(str.substr(1));

		buf = now;
	}

	// 文字列が格納されていなければ，階層をひとつ下げて戻る
	if (buf.empty()) {
		hierarchy--;
		return;
	}

	// コンテナに格納
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

// ----------------------------------------------------------------------------
// 名前	： sort_str_group
// 機能	： ダブル配列挿入のための前処理　＝　文字列群を並び替える
// 引数	： (out)	vector < vector <string> >	$convert_str_group	: 変換後の文字列群
// 出力	： なし
//
// 備考	： 
//		   
//		　 
// ----------------------------------------------------------------------------
vector <vector<string>> KeySort::Output() {

	vector <vector<string>> convert_str_group;

	vector <string> buf;

	for (auto hie : CONTAINER) {
		if (hie.empty()) continue;
		for (auto str : hie) {
			string one;
			while (1) {

				if (str.empty()) break;
				one = str.front();
				str.erase(0, 1);
				buf.push_back(one);
				one.clear();

			}
			convert_str_group.push_back(buf);
			buf.clear();
		}
	}
	return convert_str_group;
}