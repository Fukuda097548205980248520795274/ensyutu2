#pragma once
#include "./Class/Object/Particle/Particle.h"

class Thunder : public Particle
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Thunder();

	/// <summary>
	/// 放出する
	/// </summary>
	void Emission();

	/// <summary>
	/// 動かす
	/// </summary>
	void Move();

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh">画像</param>
	void Draw(int gh) override;

	// IDを数える値
	static int countId;

	// クールタイム
	static int coolTime;

	// 不透明度
	int alpha_;
};