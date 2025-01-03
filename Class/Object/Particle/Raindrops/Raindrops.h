#pragma once
#include "./Class/Object/Particle/Particle.h"

class Raindrops : public Particle
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Raindrops();

	/// <summary>
	/// 放出する
	/// </summary>
	/// <param name="posX">X軸の位置</param>
	/// <param name="posY">Y軸の位置</param>
	/// <param name="thera">角度</param>
	void Emission(float posX, float posY, float theta);

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
	/// <param name="gh">画像</param>
	void Draw(int gh) override;

	// IDを数える値
	static int countId;
};

