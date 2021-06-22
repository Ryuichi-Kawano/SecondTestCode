#pragma once

/// <summary>
/// シングルトンクラス
/// このクラスの「オブジェクトが1つしかない」事を
/// 保証するクラス
/// </summary>
class Singleton
{
private:
	///コンストラクタをprivateに置くことで
	///クライアントが生成できないようにする。
	Singleton() {};
	//コピーと代入の禁止
	Singleton(const Singleton&)=delete;//コピーコンストラクタ
	void operator=(const Singleton&)=delete;//代入
	int counter = 0;
public:
	//インスタンス取得関数
	static Singleton& Instance() {
		static Singleton instance;//これが唯一のオブジェクト
		return instance;
	}
	void Out();
};

