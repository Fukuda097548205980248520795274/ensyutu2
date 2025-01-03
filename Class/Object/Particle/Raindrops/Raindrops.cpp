#include "Raindrops.h"

/// <summary>
/// コンストラクタ
/// </summary>
Raindrops::Raindrops()
{
	// ID
	id_ = 0;

	// 放出されているかどうか（放出フラグ）
	isEmission_ = false;

	// 図形
	shape_.scale = { 2.0f , 2.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 0.0f , 0.0f };

	// 位置
	pos_.local = { {-1.0f , 1.0f} , {1.0f , 1.0f} , {-1.0f , -1.0f} , {1.0f , -1.0f} };
	LocalToScreen();

	// 移動速度
	vel_ = { 0.0f , 0.0f };

	// ベクトル
	vec_ = { 0.0f , 0.0f };

	// フレーム
	frame_.current = 0;
	frame_.end = 0;
	frame_.rate = 0.0f;
}

/// <summary>
/// 放出する
/// </summary>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="thera">角度</param>
void Raindrops::Emission(float posX, float posY, float theta)
{
	if (isEmission_ == false)
	{
		// 放出する（放出フラグをtrueにする）
		isEmission_ = true;

		// ID
		id_ = ++countId;

		// 位置
		shape_.translate = { posX , posY };
		LocalToScreen();

		// ベクトル
		vec_ = { cosf((theta / 180.0f) * float(M_PI)) , sinf((theta / 180.0f) * float(M_PI)) };

		// 移動速度
		vel_ = { 2.0f , 2.0f };
	}
}

/// <summary>
/// 動かす
/// </summary>
void Raindrops::Move()
{
	if (isEmission_)
	{
		// 動かす
		shape_.translate.x += vec_.x * vel_.x;
		shape_.translate.y += vec_.y * vel_.y;
		LocalToScreen();

		// 落下する
		vel_.y -= 0.5f;

		// 地面についたら消える（放出フラグがfalseになる）
		if (shape_.translate.y - shape_.scale.y < 0.0f)
		{
			isEmission_ = false;

			// IDを取り消す
			id_ = 0;
			--countId;
		}
	}
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="shape">図形</param>
void Raindrops::Hit(const struct Shape* shape)
{
	// null を探す
	if (shape == nullptr)
	{
		return;
	}

	// 触れたらきえる（放出フラグがfalseになる）
	if (this->shape_.translate.x + this->shape_.scale.x > shape->translate.x - shape->scale.x &&
		this->shape_.translate.x - this->shape_.scale.x < shape->translate.x + shape->scale.x)
	{
		if (this->shape_.translate.y + this->shape_.scale.y > shape->translate.y - shape->scale.y &&
			this->shape_.translate.y - this->shape_.scale.y < shape->translate.y + shape->scale.y)
		{
			isEmission_ = false;

			// IDを取り消す
			id_ = 0;
			--countId;
		}
	}
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="gh">画像</param>
void Raindrops::Draw(int gh)
{
	if (isEmission_)
	{
		Novice::DrawQuad
		(
			static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
			static_cast<int>(pos_.screen.rightTop.x), static_cast<int>(pos_.screen.rightTop.y),
			static_cast<int>(pos_.screen.leftBottom.x), static_cast<int>(pos_.screen.leftBottom.y),
			static_cast<int>(pos_.screen.rightBottom.x), static_cast<int>(pos_.screen.rightBottom.y),
			0, 0, 1, 1, gh, 0xFFFFFF33
		);
	}
}