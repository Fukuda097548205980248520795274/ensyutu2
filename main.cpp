#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include "Constant.h"
#include "Enumeration.h"
#include "./Class/Object/Player/Player.h"
#include "./Class/Object/Particle/Rain/Rain.h"
#include "./Class/Object/Particle/Raindrops/Raindrops.h"
#include "./Class/Object/Particle/Thunder/Thunder.h"
#include "./Class/Object/Particle/Hinoko/Hinoko.h"
#include "./Class/Object/Boss/HellBoss/HellBoss.h"
#include "./Class/Object/Boss/IceBoss/IceBoss.h"
#include "./Class/Object/Boss/MagicBoss/MagicBoss.h"
#include "./Class/Object/Particle/Snow/Snow.h"
#include "./Class/Object/Particle/Snowfall/Snowfall.h"

const char kWindowTitle[] = "LC1B_20_フクダソウワ";

int Rain::countId;
int Raindrops::countId;
int Thunder::countId;
int Thunder::coolTime;
int Hinoko::countId;
int Hinoko::coolTime;
int Snow::countId;
int Snowfall::countId;

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

	/*   切り替え   */

	// ステージの種類
	STAGE stageNo = STAGE_2;


	/*   キャラクター   */

	// プレイヤー
	Player* player = new Player();

	// ボス
	HellBoss* hellBoss = new HellBoss();
	IceBoss* iceBoss = new IceBoss();
	MagicBoss* magicBoss = new MagicBoss();


	/*   パーティクル   */

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

	// 雪
	Snow* snow[kSnowNum];
	for (int i = 0; i < kSnowNum; i++)
	{
		snow[i] = new Snow();
	}


	/*   画像   */

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

		// ステージ切り替え
		switch (stageNo)
		{
		case STAGE_1:
			// ステージ1

			/*   ボス   */




			/*   放出する   */

			/// 雨
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


			/// 雷

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


			/// 火の粉

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
							} else
							{
								hinoko[i]->Emission(static_cast<float>(rand() % (kScreenWidth + 300)), -10.0f, 140.0f, 0);
							}

							break;
						}
					}
				}
			}


			/*   動かす   */

			/// 雨
			for (int i = 0; i < kRainNum; i++)
			{
				rain[i]->Move();
				rain[i]->Hit(&player->shape_);
			}

			/// 雷
			for (int i = 0; i < kThunderNum; i++)
			{
				thunder[i]->Move();
			}

			/// 火の粉
			for (int i = 0; i < kHinokoNum; i++)
			{
				hinoko[i]->Move();
			}


			/*   切り替え   */

			// Spaceキーで、ステージ2に切り替える
			if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
			{
				stageNo = STAGE_2;
			}

			break;

		case STAGE_2:
			// ステージ2

			/*   放出する   */

			// 雪
			for (int i = 0; i < kSnowNum; i++)
			{
				if (snow[i]->id_ == 0)
				{
					snow[i]->Emission(static_cast<float>(rand() % (kScreenWidth + 400)), 700.0f, static_cast<float>(rand() % 360), 260.0f);

					break;
				}
			}


			/*   動かす   */

			for (int i = 0; i < kSnowNum; i++)
			{
				snow[i]->Move();
				snow[i]->Hit(&player->shape_);
			}


			/*   切り替え   */

			// Spaceキーで、ステージ3に切り替える
			if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
			{
				stageNo = STAGE_3;
			}

			break;

		case STAGE_3:
			// ステージ3


			/*   切り替え   */

			// Spaceキーで、ステージ1に切り替える
			if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
			{
				stageNo = STAGE_1;
			}

			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// ステージ切り替え
		switch (stageNo)
		{
		case STAGE_1:
			// ステージ1

			/*-------------------
				画像を描画する
			-------------------*/

			// 背景
			Novice::DrawBox
			(0, 0, kScreenWidth, kScreenHeight, 0.0f, 0x333333FF, kFillModeSolid);

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
			(0, 670, kScreenWidth, 50, 0.0f, 0x000000FF, kFillModeSolid);

			break;

		case STAGE_2:
			// ステージ2

			// 背景
			Novice::DrawBox
			(0, 0, kScreenWidth, kScreenHeight, 0.0f, 0x000033FF, kFillModeSolid);

			// 雪
			for (int i = 0; i < kSnowNum; i++)
			{
				snow[i]->Draw(ghWhite);
			}

			// 地面
			Novice::DrawBox
			(0, 670, kScreenWidth, 50, 0.0f, 0x660000FF, kFillModeSolid);

			break;

		case STAGE_3:
			// ステージ3

			break;
		}

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

	// ボス
	delete hellBoss;
	delete iceBoss;
	delete magicBoss;

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

	// 雪
	for (int i = 0; i < kSnowNum; i++)
	{
		delete snow[i];
	}


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
