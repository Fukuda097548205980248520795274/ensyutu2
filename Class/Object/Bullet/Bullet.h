#pragma once
#include "./Class/Object/Object.h"

class Bullet : public Object
{
public:

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh">画像</param>
	virtual void Draw(int gh);

	// ID
	int id_;

	// 発射されているかどうか（発射フラグ）
	int isShot_;

	// ベクトル
	struct Vec2 vec_;

	// フレーム
	struct Frame frame_;
};