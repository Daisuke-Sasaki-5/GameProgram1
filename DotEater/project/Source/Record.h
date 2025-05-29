#pragma once

// クラス…処理とデータをまとめたもの、private…データを隠蔽したい
// データはできるだけprivateに書く
// データを外に見せたければ、関数を通して値だけを返す
// 外から操作させる場合でも、直接関数に代入させない

// コンストラクターは、内部が正しく動くようにする
// メンバー変数を初期化

// デストラクターは自分が消えるときに後片付けをする
// newしているのものがあれば、Deleteする
// ロードしている素材(画像・モデル・音)があれば、Deleteする

// クラスと構造体は同じ
// structは何もないところはpublicになる
// classは何もないところはprivateになる

class Record
{
public:
	Record() { x = 0; life = 500; }
	~Record(){}
	int GetX() { return x; } // 変数を見せるにはゲッター関数
	bool isDead() { return life <= 0; } // ライフの変数は見せないけど、知りたい情報を提供する

	void LifeMax() { life = 500; } // ライフを操作する関数
private:
	// 変数はprivateに書いて、外から書き換えないようにする
	float x; 
	int life;
};