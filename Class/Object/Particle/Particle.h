#pragma once
#include "./Class/Object/Object.h"

class Particle : public Object
{
public:

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh">画像</param>
	virtual void Draw(int gh);

	// ID
	int id_;

	// 放出しているかどうか（放出フラグ）
	int isEmission_;

	// ベクトル
	struct Vec2 vec_;

	// フレーム
	struct Frame frame_;
};

