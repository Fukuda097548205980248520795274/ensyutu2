#include "Hinoko.h"

/// <summary>
/// コンストラクタ
/// </summary>
Hinoko::Hinoko()
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

	// 不透明度
	alpha_ = 255;
}

/// <summary>
/// 放出する
/// </summary>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="theta">角度</param>
/// <param name="time">時間</param>
void Hinoko::Emission(float posX, float posY, float theta, int time)
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
		vel_ = { 4.0f , 4.0f };

		// フレーム
		frame_.current = 0;
		frame_.end = 60 + time;

		// 不透明度
		alpha_ = 255;
	}
}

/// <summary>
/// 動かす
/// </summary>
void Hinoko::Move()
{
	if (isEmission_)
	{
		// 左右にうねうねさせて、上昇する
		shape_.translate.x += vel_.x * vec_.x + cosf((static_cast<float>(frame_.current * 3) / 180.0f) * float(M_PI));
		shape_.translate.y += vel_.y * vec_.y;
		LocalToScreen();

		// フレームの割合で、不透明度を変える
		if (frame_.current <= frame_.end)
		{
			frame_.rate = static_cast<float>(frame_.current) / static_cast<float>(frame_.end);

			alpha_ = static_cast<int>((1.0f - frame_.rate) * 255.0f + frame_.rate * 0.0f);
		}

		// フレームを進める
		frame_.current++;

		// フレームが終了したら消える（放出フラグがfalseになる）
		if (frame_.current > frame_.end)
		{
			isEmission_ = false;

			// ID
			id_ = 0;
			--countId;
		}
	}
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="gh"></param>
void Hinoko::Draw(int gh)
{
	if (isEmission_)
	{
		Novice::DrawQuad
		(
			static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
			static_cast<int>(pos_.screen.rightTop.x), static_cast<int>(pos_.screen.rightTop.y),
			static_cast<int>(pos_.screen.leftBottom.x), static_cast<int>(pos_.screen.leftBottom.y),
			static_cast<int>(pos_.screen.rightBottom.x), static_cast<int>(pos_.screen.rightBottom.y),
			0, 0, 1, 1, gh, 0xFF880000 + alpha_
		);
	}
}