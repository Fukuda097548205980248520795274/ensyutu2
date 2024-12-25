#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include "Constant.h"
#include "./Class/Object/Player/Player.h"
#include "./Class/Object/Particle/Rain/Rain.h"
#include "./Class/Object/Particle/Raindrops/Raindrops.h"
#include "./Class/Object/Particle/Thunder/Thunder.h"
#include "./Class/Object/Particle/Hinoko/Hinoko.h"

const char kWindowTitle[] = "LC1B_20_フクダソウワ";

int Rain::countId;
int Raindrops::countId;
int Thunder::countId;
int Thunder::coolTime;
int Hinoko::countId;
int Hinoko::coolTime;

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

	// 雷
	Thunder* thunder[kThunderNum];
	for (int i = 0; i < kThunderNum; i++)
	{
		thunder[i] = new Thunder();
	}

	// 火の粉
	Hinoko* hinoko[kHinokoNum];
	for (int i = 0; i < kHinokoNum; i++)
	{
		hinoko[i] = new Hinoko();
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

		/*   プレイヤー   */

		// 操作する
		player->Move(keys, preKeys);
		player->Jump(keys, preKeys);


		/*   ボス   */




		/*   放出する   */

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


		// 雷

		// クールタイムを進める
		if (Thunder::coolTime > 0)
		{
			Thunder::coolTime--;
		}

		// クールタイムが完了したら、放出する
		if (Thunder::coolTime <= 0)
		{
			for (int i = 0; i < kThunderNum; i++)
			{
				if (thunder[i]->id_ == 0)
				{
					// クールタイムを入れる
					Thunder::coolTime = 30 + rand() % 600;

					thunder[i]->Emission();

					break;
				}
			}
		}


		// 火の粉
		
		// クールタイムを進める
		if (Hinoko::coolTime > 0)
		{
			Hinoko::coolTime--;
		}

		// クールタイムが完了したら放出する
		if (Hinoko::coolTime <= 0)
		{
			for (int j = 0; j < 5; j++)
			{
				for (int i = 0; i < kHinokoNum; i++)
				{
					if (hinoko[i]->id_ == 0)
					{
						Hinoko::coolTime = 5;

						if (j > 2)
						{
							hinoko[i]->Emission(static_cast<float>(rand() % (kScreenWidth + 300)), -30.0f, 140.0f, rand() % 90);
						} 
						else
						{
							hinoko[i]->Emission(static_cast<float>(rand() % (kScreenWidth + 300)), -10.0f, 140.0f, 0);
						}

						break;
					}
				}
			}
		}


		/*   動かす   */

		// 雨
		for (int i = 0; i < kRainNum; i++)
		{
			rain[i]->Move();
		}

		// 雷
		for (int i = 0; i < kThunderNum; i++)
		{
			thunder[i]->Move();
		}

		// 火の粉
		for (int i = 0; i < kHinokoNum; i++)
		{
			hinoko[i]->Move();
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

		// 背景
		Novice::DrawBox
		(0 , 0 , kScreenWidth , kScreenHeight , 0.0f , 0x333333FF , kFillModeSolid);

		// 火の粉
		for (int i = 0; i < kHinokoNum; i++)
		{
			hinoko[i]->Draw(ghWhite);
		}

		// 雨
		for (int i = 0; i < kRainNum; i++)
		{
			rain[i]->Draw(ghWhite);
		}

		// 雷
		for (int i = 0; i < kThunderNum; i++)
		{
			thunder[i]->Draw(ghWhite);
		}

		// 地面
		Novice::DrawBox
		(0,670,kScreenWidth , 50 , 0.0f , 0x000000FF , kFillModeSolid);

		// プレイヤー
		player->Draw(ghWhite);

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

	// 雷
	for (int i = 0; i < kThunderNum; i++)
	{
		delete thunder[i];
	}

	// 火の粉
	for (int i = 0; i < kHinokoNum; i++)
	{
		delete hinoko[i];
	}


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
