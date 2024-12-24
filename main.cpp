#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include "Constant.h"
#include "./Class/Object/Player/Player.h"
#include "./Class/Object/Particle/Rain/Rain.h"
#include "./Class/Object/Particle/Raindrops/Raindrops.h"

const char kWindowTitle[] = "LC1B_20_フクダソウワ";

int Rain::countId;
int Raindrops::countId;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kScreenWidth, kScreenHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 乱数
	unsigned int currentTimer = static_cast<unsigned int>(time(nullptr));
	srand(currentTimer);


	/*---------------
	    変数を作る
	---------------*/

	// プレイヤー
	Player* player = new Player();

	// 雨
	Rain* rain[kRainNum];
	for (int i = 0; i < kRainNum; i++)
	{
		rain[i] = new Rain();
	}

	// 白い図形
	int ghWhite = Novice::LoadTexture("./NoviceResources/white1x1.png");


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// 操作する
		player->Move(keys, preKeys);
		player->Jump(keys, preKeys);

		// 雨
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < kRainNum; j++)
			{
				if (rain[j]->id_ == 0)
				{
					rain[j]->Emission(static_cast<float>(rand() % (kScreenWidth + 400)), 700.0f, 250.0f);

					break;
				}
			}
		}


		for (int i = 0; i < kRainNum; i++)
		{
			rain[i]->Move();
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*-------------------
		    画像を描画する
		-------------------*/

		// プレイヤー
		player->Draw(ghWhite);

		// 雨
		for (int i = 0; i < kRainNum; i++)
		{
			rain[i]->Draw(ghWhite);
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}


	/*--------------------------
	    インスタンスを削除する
	--------------------------*/

	// プレイヤー
	delete player;

	// 雨
	for (int i = 0; i < kRainNum; i++)
	{
		delete rain[i];
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
