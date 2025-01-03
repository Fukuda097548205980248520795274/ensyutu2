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
/// <param name="attackNo">攻撃の種類</param>
void HellBoss::Move(int attackNo)
{
	// フレームを進める
	frame_.current++;

	// 30フレームで攻撃する
	if (frame_.current > 30)
	{
		// 攻撃していない（攻撃フラグがfalseである）ときは、攻撃方法を決める
		if (isAttack_ == false)
		{
			this->attackNo_ = attackNo;

			// 攻撃する（攻撃フラグがtrueになる）
			isAttack_ = true;
		} 
		else
		{
			// 攻撃切り替え
			switch (attackNo_)
			{
			case 0:

				break;

			case 1:

				break;

			case 2:

				break;
			}
		}
	}
	else
	{
		shape_.translate.x += vel_.x;
		shape_.translate.y += vel_.y;
		LocalToScreen();
	}


	/*   位置ずれ調整   */

	// 地面
	if (shape_.translate.y - shape_.scale.y < 0.0f)
	{
		shape_.translate.y = shape_.scale.y;
		LocalToScreen();
	}

	// 左端
	if (shape_.translate.x - shape_.scale.x < 0.0f)
	{
		shape_.translate.x = shape_.scale.x;
		LocalToScreen();
	}

	// 右端
	if (shape_.translate.x + shape_.scale.x > static_cast<float>(kScreenWidth))
	{
		shape_.translate.x = static_cast<float>(kScreenWidth) - shape_.scale.x;
		LocalToScreen();
	}
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