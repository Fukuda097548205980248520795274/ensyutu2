#pragma once
#include "./Class/Object/Particle/Particle.h"
#include "./Class/Object/Particle/Snowfall/Snowfall.h"

class Snow : public Particle
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Snow();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Snow();

	/// <summary>
	/// 放出する
	/// </summary>
	/// <param name="posX">X軸の位置</param>
	/// <param name="posY">Y軸の位置</param>
	/// <param name="shapeTheta">図形の角度</param>
	/// <param name="thera">角度</param>
	void Emission(float posX, float posY, float shapeTheta, float theta);

	/// <summary>
	/// 動かす
	/// </summary>
	void Move();

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="shape">図形</param>
	void Hit(const struct Shape* shape);

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh"></param>
	void Draw(int gh) override;

	// IDを数える値
	static int countId;

	// 降雪
	Snowfall* snowfall[kSnowfallNum];
};