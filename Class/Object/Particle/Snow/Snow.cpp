#include "Snow.h"

/// <summary>
/// コンストラクタ
/// </summary>
Snow::Snow()
{
	// ID
	id_ = 0;

	// 放出されているかどうか（放出フラグ）
	isEmission_ = false;

	// 図形
	shape_.scale = { 3.0f , 3.0f };
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

	// 降雪
	for (int i = 0; i < kSnowfallNum; i++)
	{
		snowfall[i] = new Snowfall();
	}
}

/// <summary>
/// デストラクタ
/// </summary>
Snow::~Snow()
{
	// 降雪
	for (int i = 0; i < kSnowfallNum; i++)
	{
		delete snowfall[i];
	}
}

/// <summary>
/// 放出する
/// </summary>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="shapeTheta">図形の角度</param>
/// <param name="thera">角度</param>
void Snow::Emission(float posX, float posY, float shapeTheta , float theta)
{
	if (isEmission_ == false)
	{
		// 放出する（放出フラグをtrueにする）
		isEmission_ = true;

		// ID
		id_ = ++countId;

		// 位置
		shape_.translate = { posX , posY };
		shape_.theta = shapeTheta;
		LocalToScreen();

		// ベクトル
		vec_ = { cosf((theta / 180.0f) * float(M_PI)) , sinf((theta / 180.0f) * float(M_PI)) };

		// 移動速度
		vel_ = { 8.0f , 8.0f };
	}
}

/// <summary>
/// 動かす
/// </summary>
void Snow::Move()
{
	if (isEmission_)
	{
		// 動かす
		shape_.translate.x += vec_.x * vel_.x;
		shape_.translate.y += vec_.y * vel_.y;
		LocalToScreen();

		// 左に流されていく
		vel_.x += 0.1f;

		// 地面についたら消える（放出フラグがfalseになる）
		if (shape_.translate.y - shape_.scale.y < 0.0f)
		{
			isEmission_ = false;

			// 降雪を残す
			for (int i = 0; i < kSnowfallNum; i++)
			{
				if (snowfall[i]->id_ == 0)
				{
					snowfall[i]->Emission(shape_.translate.x);

					break;
				}
			}

			// IDを取り消す
			id_ = 0;
			--countId;
		}
	}

	// 降雪を動かす
	for (int i = 0; i < kSnowfallNum; i++)
	{
		snowfall[i]->Move();
	}
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="shape">図形</param>
void Snow::Hit(const struct Shape* shape)
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

	// 降雪
	for (int i = 0; i < kSnowfallNum; i++)
	{
		snowfall[i]->Hit(shape);
	}
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="gh">画像</param>
void Snow::Draw(int gh)
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

	// 降雪
	for (int i = 0; i < kSnowfallNum; i++)
	{
		snowfall[i]->Draw(gh);
	}
}