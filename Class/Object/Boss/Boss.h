#pragma once
#include "./Class/Object/Object.h"

class Boss : public Object
{
public:

	/// <summary>
	/// 動かす
	/// </summary>
	/// <param name="attackNo">攻撃の種類</param>
	virtual void Move(int attackNo);

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh">画像</param>
	virtual void Draw(int gh);

	// 攻撃しているかどうか（攻撃フラグ）
	int isAttack_;

	// 攻撃の種類
	int attackNo_;

	// フレーム
	struct Frame frame_;
};

