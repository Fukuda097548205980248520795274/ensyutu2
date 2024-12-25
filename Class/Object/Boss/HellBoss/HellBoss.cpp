#include "HellBoss.h"

/// <summary>
/// コンストラクタ
/// </summary>
HellBoss::HellBoss()
{
	// 図形
	shape_.scale = { 24.0f , 32.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 960.0f , 0.0f };

	// 位置
	pos_.local = { {-1.0f , 1.0f} , {1.0f , 1.0f} , {-1.0f , -1.0f} , {1.0f , -1.0f} };
	LocalToScreen();

	// 移動速度
	vel_ = { 0.0f , 0.0f };

	// 攻撃しているかどうか（攻撃フラグ）
	isAttack_ = false;

	// 攻撃の種類
	attackNo_ = -1;

	// フレーム
	frame_.current = 0;
	frame_.end = 0;
	frame_.rate = 0.0f;
}

/// <summary>
/// デストラクタ
/// </summary>
HellBoss::~HellBoss()
{

}

/// <summary>
/// 動かす
/// </summary>
void HellBoss::Move()
{

}

/// <summary>
/// 描画する
/// </summary>
/// <param name="gh">画像</param>
void HellBoss::Draw(int gh)
{
	Novice::DrawQuad
	(
		static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
		static_cast<int>(pos_.screen.rightTop.x), static_cast<int>(pos_.screen.rightTop.y),
		static_cast<int>(pos_.screen.leftBottom.x), static_cast<int>(pos_.screen.leftBottom.y),
		static_cast<int>(pos_.screen.rightBottom.x), static_cast<int>(pos_.screen.rightBottom.y),
		0, 0, 1, 1, gh, 0xFF0000FF
	);
}