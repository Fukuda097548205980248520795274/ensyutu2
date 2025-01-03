#pragma once
#include "./Class/Object/Particle/Particle.h"

class Snowfall : public Particle
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Snowfall();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Snowfall();

	/// <summary>
	/// 放出する
	/// </summary>
	/// <param name="posX">X軸の位置</param>
	void Emission(float posX);

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
};