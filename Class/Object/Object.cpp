#include "Object.h"

/// <summary>
/// ローカル座標をワールド座標に変換する
/// </summary>
void Object::LocalToScreen()
{
	// 全てを結合した行列
	struct Matrix3x3 wvpVpMatrix;

	wvpVpMatrix = Multiply(MakeWorldMatrix(shape_.scale, shape_.theta, shape_.translate),
		MakeInverseMatrix(MakeWorldMatrix({ 1.0f , 1.0f }, 0.0f, { 0.0f , 0.0f })));

	wvpVpMatrix = Multiply(wvpVpMatrix, MakeOrthoMatrix(0.0f, 670.0f, 1280.0f, -50.0f));

	wvpVpMatrix = Multiply(wvpVpMatrix, MakeViewportMatrix(0.0f, 0.0f, 1280.0f, 720.0f));

	pos_.screen.leftTop = Transform(pos_.local.leftTop, wvpVpMatrix);
	pos_.screen.rightTop = Transform(pos_.local.rightTop, wvpVpMatrix);
	pos_.screen.leftBottom = Transform(pos_.local.leftBottom, wvpVpMatrix);
	pos_.screen.rightBottom = Transform(pos_.local.rightBottom, wvpVpMatrix);
}