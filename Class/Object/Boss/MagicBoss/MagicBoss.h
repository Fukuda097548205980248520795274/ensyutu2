#pragma once
#include "./Class/Object/Boss/Boss.h"

class MagicBoss : public Boss
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MagicBoss();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MagicBoss();

	/// <summary>
	/// 動かす
	/// </summary>
	/// <param name="attackNo">攻撃の種類</param>
	void Move(int attackNo) override;

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh">画像</param>
	void Draw(int gh) override;
};

