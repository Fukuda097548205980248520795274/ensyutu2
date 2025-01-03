#include "Thunder.h"

/// <summary>
/// コンストラクタ
/// </summary>
Thunder::Thunder()
{
	// ID
	id_ = 0;

	// 放出されているかどうか（放出フラグ）
	isEmission_ = false;

	// 図形
	shape_.scale = { 0.0f , 0.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 0.0f , 0.0f };

	// 位置
	pos_.local = { {0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f} };
	LocalToScreen();

	// 移動速度
	vel_ = { 0.0f , 0.0f };

	// ベクトル
	vec_ = { 0.0f , 0.0f };

	// フレーム
	frame_.current = 0;
	frame_.end = 0;
	frame_.rate = 0.0f;

	// 透明度
	alpha_ = 255;
}

/// <summary>
/// 放出する
/// </summary>
void Thunder::Emission()
{
	if (isEmission_ == false)
	{
		// 放出する（放出フラグをtrueにする）
		isEmission_ = true;

		// ID
		id_ = ++countId;

		// フレーム
		frame_.current = 0;
		frame_.end = 120;
		frame_.current = 0;
	}
}

/// <summary>
/// 動かす
/// </summary>
void Thunder::Move()
{
	if (isEmission_)
	{
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
void Thunder::Draw(int gh)
{
	if (isEmission_)
	{
		Novice::DrawQuad
		(
			0, 0,
			kScreenWidth, 0,
			0, kScreenHeight,
			kScreenWidth, kScreenHeight,
			0, 0, 1, 1, gh, 0xFFFFFF00 + alpha_
		);
	}
}