#include "Snowfall.h"

/// <summary>
/// コンストラクタ
/// </summary>
Snowfall::Snowfall()
{
	// ID
	id_ = 0;

	// 放出されているかどうか（放出フラグ）
	isEmission_ = false;

	// 図形
	shape_.scale = { 6.0f , 6.0f };
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
/// デストラクタ
/// </summary>
Snowfall::~Snowfall()
{

}

/// <summary>
/// 放出する
/// </summary>
/// <param name="posX">X軸の位置</param>
void Snowfall::Emission(float posX)
{
	if (isEmission_ == false)
	{
		// 放出する（放出フラグをtrueにする）
		isEmission_ = true;

		// ID
		id_ = ++countId;

		// 位置
		shape_.translate = { posX , 0.0f };
		LocalToScreen();

		// フレーム
		frame_.current = 0;
		frame_.end = 600;
	}
}

/// <summary>
/// 動かす
/// </summary>
void Snowfall::Move()
{
	if (isEmission_)
	{
		// フレームの割合で、小さくなる
		frame_.rate = static_cast<float>(frame_.current) / static_cast<float>(frame_.end);
		shape_.scale.y = (1.0f - frame_.rate) * 6.0f + frame_.rate * 0.0f;

		// フレームを進める
		frame_.current++;

		LocalToScreen();

		// フレームが終了したら消える（放出フラグがfalseになる）
		if (frame_.current > frame_.end)
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
/// <param name="shape"></param>
void Snowfall::Hit(const struct Shape* shape)
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
void Snowfall::Draw(int gh)
{
	if (isEmission_)
	{
		Novice::DrawQuad
		(
			static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
			static_cast<int>(pos_.screen.rightTop.x), static_cast<int>(pos_.screen.rightTop.y),
			static_cast<int>(pos_.screen.leftBottom.x), static_cast<int>(pos_.screen.leftBottom.y),
			static_cast<int>(pos_.screen.rightBottom.x), static_cast<int>(pos_.screen.rightBottom.y),
			0, 0, 1, 1, gh, 0xFFFFFFAA
		);
	}
}