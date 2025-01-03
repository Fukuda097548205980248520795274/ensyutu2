#pragma once
#include "./Class/Object/Boss/Boss.h"

class HellBoss : public Boss
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	HellBoss();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HellBoss();

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

