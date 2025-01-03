#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	// 図形
	shape_.scale = { 24.0f , 32.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 320.0f , 0.0f };

	// 位置
	pos_.local = { {-1.0f , 1.0f} , {1.0f , 1.0f} , {-1.0f , -1.0f} , {1.0f , -1.0f} };
	LocalToScreen();

	// 移動速度
	vel_ = { 0.0f , 0.0f };

	// ジャンプ
	jump_.isJump = false;
	jump_.fallingVel = 0.0f;
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

}

/// <summary>
/// 移動する
/// </summary>
/// <param name="keys">キー</param>
/// <param name="preKeys">前のキー</param>
void Player::Move(const char* keys, const char* preKeys)
{
	// null を探す
	if (keys == nullptr || preKeys == nullptr)
	{
		return;
	}

	// 横移動を初期化する
	vel_.x = 0.0f;

	// Aキーで、左に移動する
	if (keys[DIK_A])
	{
		if (shape_.translate.x - shape_.scale.x > 0.0f)
		{
			vel_.x = -4.0f;
		}
	}

	// Dキーで、右に移動する
	if (keys[DIK_D])
	{
		if (shape_.translate.x + shape_.scale.x < static_cast<float>(kScreenWidth))
		{
			vel_.x = 4.0f;
		}
	}

	// 動かす
	shape_.translate.x += vel_.x;
	LocalToScreen();


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
/// ジャンプする
/// </summary>
/// <param name="keys">キー</param>
/// <param name="preKeys">前のキー</param>
void Player::Jump(const char* keys, const char* preKeys)
{
	// null を探す
	if (keys == nullptr || preKeys == nullptr)
	{
		return;
	}


	// Jキーで、ジャンプする（ジャンプフラグがtrueになる）
	if (!preKeys[DIK_J] && keys[DIK_J])
	{
		if (jump_.isJump == false)
		{
			jump_.isJump = true;
			jump_.fallingVel = -0.5f;

			// 上昇する
			vel_.y = 12.0f;
		}
	}

	// ジャンプしている（ジャンプフラグがtrueである）ときの動き
	if (jump_.isJump)
	{
		// 落下する
		vel_.y += jump_.fallingVel;

		// 動かす
		shape_.translate.y += vel_.y;
		LocalToScreen();


		// 地面についたら、ジャンプしなくなる（ジャンプフラグがfalseになる）
		if (shape_.translate.y - shape_.scale.y <= 0.0f)
		{
			jump_.isJump = false;

			jump_.fallingVel = 0.0f;
			vel_.y = 0.0f;
		}
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
void Player::Draw(int gh)
{
	Novice::DrawQuad
	(
		static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
		static_cast<int>(pos_.screen.rightTop.x), static_cast<int>(pos_.screen.rightTop.y),
		static_cast<int>(pos_.screen.leftBottom.x), static_cast<int>(pos_.screen.leftBottom.y),
		static_cast<int>(pos_.screen.rightBottom.x), static_cast<int>(pos_.screen.rightBottom.y),
		0, 0, 1, 1, gh, 0x00FF00FF
	);
}