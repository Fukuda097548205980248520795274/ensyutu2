#include "Boss.h"

/// <summary>
/// 動かす
/// </summary>
/// <param name="attackNo">攻撃の種類</param>
void Boss::Move(int attackNo)
{
	attackNo = 1;
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="gh">画像</param>
void Boss::Draw(int gh)
{
	Novice::DrawQuad
	(
		static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
		static_cast<int>(pos_.screen.rightTop.x), static_cast<int>(pos_.screen.rightTop.y),
		static_cast<int>(pos_.screen.leftBottom.x), static_cast<int>(pos_.screen.leftBottom.y),
		static_cast<int>(pos_.screen.rightBottom.x), static_cast<int>(pos_.screen.rightBottom.y),
		0, 0, 1, 1, gh, 0xFFFFFFFF
	);
}