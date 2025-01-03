#pragma once
#include <Novice.h>
#include "Structure.h"
#include "Constant.h"
#include "./Function/Matrix/Matrix.h"

class Object
{
public:

	/// <summary>
	/// ローカル座標をワールド座標に変換する
	/// </summary>
	void LocalToScreen();

	// 図形
	struct Shape shape_;

	// 位置
	struct Pos2 pos_;

	// 移動速度
	struct Vec2 vel_;
};

