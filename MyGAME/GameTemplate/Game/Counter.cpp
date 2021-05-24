#include "stdafx.h"
#include "Counter.h"
#include "Burger.h"
#include "Kitchen.h"
#include "Score.h"
#include "CLevel2D.h";
#include "PlayerGene.h"
#include "Player.h"
#include "SkinModelRender.h"
#include "SpriteRender.h"
#include "SoundSource.h"
#include "GameDirector.h"
#include "effect/Effect.h"

Counter::~Counter()
{
	DeleteGO(m_skinModelRender);
	
	if (m_spriteJudge01 != nullptr) {
		DeleteGO(m_spriteJudge01);
	}
	
	if (m_spriteJudge02 != nullptr) {
		DeleteGO(m_spriteJudge02);
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (m_spriteCompareFlagFalse[i][j] || m_spriteCompareFlagTrue[i][j]) {
				DeleteGO(m_spriteCompare[i][j]);
			}
		}
	}
	
	////P1側チェック画像は画像配列 3番、2番を使用
	//if (CounterNo == 1) {
	//	for (int i = 3; i > 1; i--) {
	//		for (int j = 0; j < 5; j++) {
	//			if (m_spriteCompare[i][j] != nullptr) {
	//				DeleteGO(m_spriteCompare[i][j]);
	//			}
	//		}
	//	}
	//}

	////P2側チェック画像は画像配列 0番、1番を使用
	//if (CounterNo == 2) {
	//	for (int s = 0; s < 2; s++) {
	//		for (int t = 0; t < 5; t++) {
	//			if (m_spriteCompare[s][t] != nullptr) {
	//				DeleteGO(m_spriteCompare[s][t]);
	//			}
	//		}
	//	}
	//}

}

Counter::Counter()
{

	//ハンバーガーのデータを作る。
	/*HamBurger cheese;
	cheese.push_back(3);
	cheese.push_back(0);
	cheese.push_back(2);
	m_hamBurgers[enCheeseBurger] = cheese;

	HamBurger tomato;
	tomato.push_back(3);
	tomato.push_back(4);
	tomato.push_back(4);
	tomato.push_back(2);
	m_hamBurgers[enTomatoBurger] = tomato;

	HamBurger egg;
	egg.push_back(2);
	egg.push_back(4);
	egg.push_back(1);
	egg.push_back(3);
	m_hamBurgers[enEggBurger] = egg;*/
}

bool Counter::Start()
{
	l2 = FindGO<CLevel2D>("clevel2d");

	m_playerGene = FindGO<PlayerGene>("playerGene");

	m_skinModelRender = NewGO<SkinModelRender>(0);

	//具材の積まれた判定を積まれていない状態にする
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			m_guzaiJudge[i][j] = 2;
		}
	}

	m_skinModelRender->Init("Assets/modelData/counter/counter.tkm", nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_showHamBurgers[0] = enCheeseBurger;
	m_showHamBurgers[1] = enTomatoBurger;
	m_showHamBurgers[2] = enEggBurger;
	m_showHamBurgers[3] = enBasicBurger;
	m_showHamBurgers[4] = enDoubleBurger;
	m_showHamBurgers[5] = enVegetableBurger;
	m_showHamBurgers[6] = enBaconBurger;
	m_showHamBurgers[7] = enBLTBurger;
	m_showHamBurgers[8] = enOnionBurger;
	m_showHamBurgers[9] = enHighcalBurger;
	m_showHamBurgers[10] = enOnOnionBurger;

	return true;
}

//////////////////////判別するところ////////////////////////////////////////////////////////////////////////////////
bool Counter::Judge()
{
	//CLevel2D* l2 = FindGO<CLevel2D>("clevel2d");

	if (CounterNo == 1) {
		Kitchen* ki01 = FindGO<Kitchen>("kitchen01");
		Player* pl01 = FindGO<Player>("player01");

		//最終結果を記録するもの。
		bool correct01 = true;
		//判別していく過程で正しかったらインクリメントされていく。正解数みたいなもの。
		int correctCount01 = 0;
		//満点となる数。sizeofの中身を変えることでいろんな種類のバーガーに対応できると思う。←変えてもいい。
		//int correctGuzaiNum01 = sizeof(burger01) / sizeof(int);

		return l2->GetIsMatchHamBurger(pl01->GuzaiNo, StackNum, CounterNo);
		//作ったバーガーの層によって回すFOR文の回数が変わる。
		//StackNumはバーガーができる瞬間にこちら側に保存される。（in Kitchen.cpp)
		//判別過程で一度でも間違えたらFALSE
		/*for (int i = 0; i < enHamBurgerNum; i++)
		{
			//ハンバーガーのデータ持ってくるお。
			HamBurger hamBurger = m_hamBurgers[i];
			//長さ違ったら。
			if (StackNum != hamBurger.size())
				//以下の処理しなーい。
				continue;
			
			//同じだお。
			bool isSame = true;
			for (int j = 0; j < hamBurger.size(); j++)
			{
				//具材が違ってたら。
				if (pl01->GuzaiNo[j] != hamBurger[j])
				{
					//違うお。
					isSame = false;
					break;
				}
			}
			//同じだったお。
			if (isSame == true)
			{
				return true;
			}
		}
		//同じじゃなかったらtrue以外ありえない。
		return false;
		/*for (int i = 0; i < StackNum; i++) {
			
			if (burger01[i] == pl01->GuzaiNo[i]) {
				correctCount01++;
				continue;
			}
			else{
				correct01 = false;
				break;
			}
		}
		//ここまでの文では途中まで完璧にできていたらTRUEになる。
		//したの文で、最終的に層の数が違っていたらFALSEにする。
		if (correctCount01 != correctGuzaiNum01) {
			correct01 = false;
		}

		return correct01;
		*/
	}

	if (CounterNo == 2) {
		Kitchen* ki02 = FindGO<Kitchen>("kitchen02");
		Player* pl02 = FindGO<Player>("player02");

		bool correct02 = true;
		int correctCount02 = 0;
		//int correctGuzaiNum02 = sizeof(burger01) / sizeof(int);

		return l2->GetIsMatchHamBurger(pl02->GuzaiNo, StackNum, CounterNo);
		/*
		for (int i = 0; i < enHamBurgerNum; i++)
		{
			//ハンバーガーのデータ持ってくるお。
			HamBurger hamBurger = m_hamBurgers[i];
			//長さ違ったら。
			if (StackNum != hamBurger.size())
				//以下の処理しなーい。
				continue;

			//同じだお。
			bool isSame = true;
			for (int j = 0; j < hamBurger.size(); j++)
			{
				//具材が違ってたら。
				if (pl02->GuzaiNo[j] != hamBurger[j])
				{
					//違うお。
					isSame = false;
					break;
				}
			}
			//同じだったお。
			if (isSame == true)
			{
				return true;
			}
		}
		//同じじゃなった！
		return false;*/
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//バーガーを最終的に消してスコアを発生させる。
//カウンターに近いところでBボタンを押すといったん載せて消す。
void Counter::Delete()
{
	if (CounterNo == 1) {

		//Player* pl01 = FindGO<Player>("player01");
		if (pl01 == nullptr) {
			pl01 = FindGO<Player>("player01");
		}

		Vector3 plPos = pl01->GetPosition();

		Vector3 CounterPos01 = m_position;

		//カウンターからプレイヤーの距離
		float pl2Counter = (plPos.x - CounterPos01.x) * (plPos.x - CounterPos01.x) + (plPos.y - CounterPos01.y) * (plPos.y - CounterPos01.y) + (plPos.z - CounterPos01.z) * (plPos.z - CounterPos01.z);
		pl2Counter = sqrt(pl2Counter);

		//プレイヤーがバーガーをもっていたら
		if (pl01->have == 2) {
			Burger* bu01 = FindGO<Burger>("burger01");

			//キッチンに置く準備
			//できたハンバーガーの組成をJudge関数で調べ、あっていたらカウンターに置ける。
			if (g_pad[0]->IsTrigger(enButtonA) && pl2Counter < 100.0f) {
				bu01->putOnKitchen = 1;
				//バーガーが合っている場合
				if (Judge() == true) {
					m_burgerCorrectFlag = true;
					//bu01->putOnKitchen = 1;
					if (m_spriteFlag01 == false) {
						m_spriteJudge01 = NewGO<SpriteRender>(0);
						m_spriteJudge01->Init("Assets/Image/BurgerJudgeMark/Correct.dds", 100, 100);
						m_spriteJudge01->SetPosition(m_spritePos01);
						m_spriteFlag01 = true;
						//音を鳴らす
						CSoundSource* se = NewGO<CSoundSource>(0);
						se->Init(L"Assets/sound/crrect_answer2.wav", false);
						se->SetVolume(0.7f);
						se->Play(false);
						//次の具材No.を保存するため、９で初期化。
						pl01->SetGuzaiNo9();
					}
				}
				//バーガーが間違っている場合。
				else {
					m_burgerMistakeFlag = true;
					if (m_spriteFlag01 == false) {
						m_spriteJudge01 = NewGO<SpriteRender>(0);
						m_spriteJudge01->Init("Assets/Image/BurgerJudgeMark/Miss.dds", 100, 100);
						m_spriteJudge01->SetPosition(m_spritePos01);
						m_spriteFlag01 = true;
						
						//音を鳴らす
						CSoundSource* se = NewGO<CSoundSource>(0);
						se->Init(L"Assets/sound/blip01.wav",false);
						se->SetVolume(0.7f);
						se->Play(false);
						pl01->SetGuzaiNo9();
					}
				}
			}

			if (bu01 != nullptr) {
				//バーガーが合っている場合
				if (m_burgerCorrectFlag == true) {
					Delay++;
					//バーガーを動かす。
					CounterPos01.y += 100.0f;
					CounterPos01.z += m_burgerPos.z;
					m_burgerPos.z += 10.0f;
					bu01->SetPosition(CounterPos01);
					//置いたら30フレーム後に消去
					if (Delay == 60) {
						//ここで積み上げてた具材の数をScoreに渡してあげる。
						Score* sco = FindGO<Score>("score");
						if (m_bonusPoint == true) {
							sco->SetBasePoint01(StackNum * 2);
							m_bonusPoint = false;
						}
						else {
							sco->SetBasePoint01(StackNum);
						}
						
						pl01->have = 0;

						bu01->ClearModel();
						DeleteGO(bu01);
						Delay = 0;
						
						StackNum = 0;
						m_playerGene->AddSubmitBurgerNum();
						m_burgerPos.z = 0.0f;
						m_burgerCorrectFlag = false;
					}
				}
				//バーガーが間違っている場合。
				if (m_burgerMistakeFlag == true) {
					Delay++;
					//バーガーを動かす。
					CounterPos01.y += 100.0f;
					CounterPos01.x += m_burgerPos.x;
					m_burgerPos.x += 10.0f;
					bu01->SetPosition(CounterPos01);

					if (Delay == 60) {
						Burger* bur01 = FindGO<Burger>("burger01");
						
						pl01->have = 0;
						bu01->ClearModel();
						DeleteGO(bu01);
						Delay = 0;
						
						StackNum = 0;
						m_burgerPos.x = 0.0f;
						m_burgerMistakeFlag = false;
					}
				}
			}
		}
	}

	if (CounterNo == 2) {

		//Player* pl02 = FindGO<Player>("player02");
		if (pl02 == nullptr) {
			pl02 = FindGO<Player>("player02");
		}

		Vector3 plPos = pl02->GetPosition();

		Vector3 CounterPos02 = m_position;

		float pl2Counter = (plPos.x - CounterPos02.x) * (plPos.x - CounterPos02.x) + (plPos.y - CounterPos02.y) * (plPos.y - CounterPos02.y) + (plPos.z - CounterPos02.z) * (plPos.z - CounterPos02.z);
		pl2Counter = sqrt(pl2Counter);

		//プレイヤーがバーガーをもっていたら
		if (pl02->have == 2) {
			Burger* bu02 = FindGO<Burger>("burger02");

			//キッチンに置く準備
			//できたハンバーガーの組成をJudge関数でしらべ、あっていたらカウンターに置ける。
			if (g_pad[1]->IsTrigger(enButtonA) && pl2Counter < 100.0f) {
				bu02->putOnKitchen = 1;
				//バーガーが合っている場合
				if (Judge() == true) {
					m_burgerCorrectFlag = true;
					//bu02->putOnKitchen = 1;
					if (m_spriteFlag02 == false) {
						m_spriteJudge02 = NewGO<SpriteRender>(0);
						m_spriteJudge02->Init("Assets/Image/BurgerJudgeMark/Correct.dds", 100, 100);
						m_spriteJudge02->SetPosition(m_spritePos02);
						m_spriteFlag02 = true;
						//音を鳴らす
						CSoundSource* se = NewGO<CSoundSource>(0);
						se->Init(L"Assets/sound/crrect_answer2.wav", false);
						se->SetVolume(0.7f);
						se->Play(false);
						//次の具材No.を保存するため、９で初期化。
						pl02->SetGuzaiNo9();
						
					}
				}
				//バーガーが間違っている場合。
				else {
					m_burgerMistakeFlag = true;
					if (m_spriteFlag02 == false) {
						m_spriteJudge02 = NewGO<SpriteRender>(0);
						m_spriteJudge02->Init("Assets/Image/BurgerJudgeMark/Miss.dds", 100, 100);
						m_spriteJudge02->SetPosition(m_spritePos02);
						m_spriteFlag02 = true;
						//音を鳴らす
						CSoundSource* se = NewGO<CSoundSource>(0);
						se->Init(L"Assets/sound/blip01.wav", false);
						se->SetVolume(0.7f);
						se->Play(false);
						pl02->SetGuzaiNo9();
						
					}
				}
			}

			if (bu02 != nullptr) {
				//正解したとき。
				if (m_burgerCorrectFlag == true) {
					Delay++;
					CounterPos02.y += 100.0f;
					CounterPos02.z += m_burgerPos.z;
					m_burgerPos.z += 10.0f;
					bu02->SetPosition(CounterPos02);
					//置いたら30フレーム後に消去
					if (Delay == 60) {
						//ここで積み上げてた具材の数をScoreに渡してあげる。
						Score* sco = FindGO<Score>("score");
						if (m_bonusPoint == true) {
							sco->SetBasePoint02(StackNum * 2);
							m_bonusPoint = false;
						}
						else {
							sco->SetBasePoint02(StackNum);
						}
						
						
						pl02->have = 0;
						DeleteGO(bu02);
						Delay = 0;
						
						StackNum = 0;
						m_playerGene->AddSubmitBurgerNum();
						m_burgerPos.z = 0.0f;
						m_burgerCorrectFlag = false;
					}
				}
				if (m_burgerMistakeFlag == true) {
					Delay++;
					CounterPos02.y += 100.0f;
					CounterPos02.x += m_burgerPos.x;
					m_burgerPos.x -= 10.0f;
					bu02->SetPosition(CounterPos02);

					if (Delay == 60) {
						Burger* bur02 = FindGO<Burger>("burger02");
						
						pl02->have = 0;
						bu02->ClearModel();
						DeleteGO(bu02);
						Delay = 0;
						
						StackNum = 0;
						m_burgerPos.x = 0.0f;
						m_burgerMistakeFlag = false;
					}
				}
			}
		}
	}
}

void Counter::HamBurgerCompare()
{
	CLevel2D* l2 = FindGO<CLevel2D>("clevel2d");
	//1P側の処理
	if (CounterNo == 1) {
		for (int i = 2; i >= CounterNo; i--) {
			//Player* pl01 = FindGO<Player>("player01");
			if (pl01 == nullptr) {
				pl01 = FindGO<Player>("player01");
			}
			HamBurger hamburger = GetHamBurgerFactory().GetHamBurger(m_showHamBurgers[i]);
			//具材をキッチンに積んでいないとき…
			for (int k = 0; k < 5; k++) {
				if (pl01->GuzaiNo[k] == 9) {
					//画像が出ていれば消す
					if (m_spriteCompareFlagTrue[i + 1][k] == true || m_spriteCompareFlagFalse[i + 1][k] == true) {
						DeleteGO(m_spriteCompare[i + 1][k]);
						m_spriteCompareFlagTrue[i + 1][k] = false;
						m_spriteCompareFlagFalse[i + 1][k] = false;
					}
				}
			}
			//メニューと合っているか調べる
			for (int j = 0; j < hamburger.size(); j++) {
				//積んでなければ何もしない。
				if (pl01->GuzaiNo[j] == 9) {
					m_guzaiJudge[i + 1][j] = 2;
				}
				else {
					if (pl01->GuzaiNo[j] == hamburger[j]) {
						//メニューと一致
						m_guzaiJudge[i + 1][j] = 1;
					}
					else {
						//メニューと不一致
						m_guzaiJudge[i + 1][j] = 0;
					}
				}

				Vector3 SetPos = { -95.0f,-255.0f,0.0f };
				SetPos.x += i * 120.0f;
				SetPos.y += j * 30.0f;
				SetPos.y += l2->GetSlideAmount(i);
				//メニューと一致しているかで決める。
				switch (m_guzaiJudge[i+1][j])
				{
					
				case 0: {
					//一致の画像が出ていれば消す。
					if (m_spriteCompareFlagTrue[i + 1][j] == true) {
						DeleteGO(m_spriteCompare[i + 1][j]);
						m_spriteCompareFlagTrue[i + 1][j] = false;
					}
					//不一致の画像が出ていなければ出す。
					if (m_spriteCompareFlagFalse[i + 1][j] == false) {
						m_spriteCompare[i + 1][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i + 1][j]->Init("Assets/Image/JudgeMark/Batsu_White_Black512.dds", 40, 40);
						m_spriteCompare[i + 1][j]->SetPosition(SetPos);
						m_spriteCompareFlagFalse[i + 1][j] = true;
					}
				}break;
				case 1: {
					//不一致の画像が出ていれば消す。
					if (m_spriteCompareFlagFalse[i + 1][j] == true) {
						DeleteGO(m_spriteCompare[i + 1][j]);
						m_spriteCompareFlagFalse[i + 1][j] = false;
					}
					//一致の画像が出ていなければ出す。
					if (m_spriteCompareFlagTrue[i + 1][j] == false) {
						m_spriteCompare[i + 1][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i + 1][j]->Init("Assets/Image/JudgeMark/Check_White_Red512.dds", 30, 30);
						m_spriteCompare[i + 1][j]->SetPosition(SetPos);
						m_spriteCompareFlagTrue[i + 1][j] = true;
					}
				}break;
				default:
					break;
				}
				//チェックマークの座標を更新。
				if (m_spriteCompareFlagFalse[i + 1][j] == true || m_spriteCompareFlagTrue[i + 1][j] == true) {
					m_spriteCompare[i + 1][j]->SetPosition(SetPos);
				}
				//すでに出したチェック画像は、バーガーの段数を超えて処理する。
				for (int l = hamburger.size(); l < 5; l++) {
					Vector3 SetPos = { -95.0f,-255.0f,0.0f };
					SetPos.x += i * 120.0f;
					SetPos.y += l * 30.0f;
					SetPos.y += l2->GetSlideAmount(i);
					if (pl01->GuzaiNo[l] != 9) {
						if (m_spriteCompareFlagFalse[i + 1][l] == true || m_spriteCompareFlagTrue[i + 1][l] == true) {

							DeleteGO(m_spriteCompare[i + 1][l]);
							m_spriteCompareFlagFalse[i + 1][l] = false;
							m_spriteCompareFlagTrue[i + 1][l] = false;
							//m_spriteCompare[i + 1][l]->SetPosition(SetPos);
						}
					}
				}
			}
		}
	}
	//2P側の処理
	if (CounterNo == 2) {
		for (int i = 0; i < CounterNo; i++) {
			//Player* pl02 = FindGO<Player>("player02");
			if (pl02 == nullptr) {
				pl02 = FindGO<Player>("player02");
			}
			HamBurger hamburger = GetHamBurgerFactory().GetHamBurger(m_showHamBurgers[i]);
			for (int k = 0; k < 5; k++) {
				if (pl02->GuzaiNo[k] == 9) {
					if (m_spriteCompareFlagTrue[i][k] == true || m_spriteCompareFlagFalse[i][k] == true) {
						DeleteGO(m_spriteCompare[i][k]);
						m_spriteCompareFlagTrue[i][k] = false;
						m_spriteCompareFlagFalse[i][k] = false;
					}
				}
			}
			for (int j = 0; j < hamburger.size(); j++) {
				if (pl02->GuzaiNo[j] == 9) {
					m_guzaiJudge[i][j] = 2;
				}
				else {
					if (pl02->GuzaiNo[j] == hamburger[j]) {
						m_guzaiJudge[i][j] = 1;
					}
					else {
						m_guzaiJudge[i][j] = 0;
					}
				}
				Vector3 SetPos = { -155.0f,-255.0f,0.0f };
				SetPos.x += i * 120.0f;
				SetPos.y += j * 30.0f;
				SetPos.y += l2->GetSlideAmount(i);
				switch (m_guzaiJudge[i][j])
				{
				case 0: {
					if (m_spriteCompareFlagTrue[i][j] == true) {
						DeleteGO(m_spriteCompare[i][j]);
						m_spriteCompareFlagTrue[i][j] = false;
					}
					if (m_spriteCompareFlagFalse[i][j] == false) {
						m_spriteCompare[i][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i][j]->Init("Assets/Image/JudgeMark/Batsu_White_Black512.dds", 40, 40);
						m_spriteCompare[i][j]->SetPosition(SetPos);
						m_spriteCompareFlagFalse[i][j] = true;
					}
				}break;
				case 1: {
					if (m_spriteCompareFlagFalse[i][j] == true) {
						DeleteGO(m_spriteCompare[i][j]);
						m_spriteCompareFlagFalse[i][j] = false;
					}
					if (m_spriteCompareFlagTrue[i][j] == false) {
						m_spriteCompare[i][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i][j]->Init("Assets/Image/JudgeMark/Check_White_Blue512.dds", 30, 30);
						m_spriteCompare[i][j]->SetPosition(SetPos);
						m_spriteCompareFlagTrue[i][j] = true;
					}
				}break;
				default:
					break;
				}
				if (m_spriteCompareFlagFalse[i][j] == true || m_spriteCompareFlagTrue[i][j] == true) {
					m_spriteCompare[i][j]->SetPosition(SetPos);
				}
				for (int l = hamburger.size(); l < 5; l++) {
					Vector3 SetPos = { -155.0f,-255.0f,0.0f };
					SetPos.x += i * 120.0f;
					SetPos.y += l * 30.0f;
					SetPos.y += l2->GetSlideAmount(i);
					if (m_spriteCompareFlagFalse[i][l] == true || m_spriteCompareFlagTrue[i][l] == true) {
						if (pl02->GuzaiNo[l] != 9) {
							if (m_spriteCompareFlagFalse[i][l] == true || m_spriteCompareFlagTrue[i][l] == true) {

								DeleteGO(m_spriteCompare[i][l]);
								m_spriteCompareFlagFalse[i][l] = false;
								m_spriteCompareFlagTrue[i][l] = false;
								//m_spriteCompare[i + 1][l]->SetPosition(SetPos);
							}
						}
						//m_spriteCompare[i][l]->SetPosition(SetPos);
					}
				}
			}
		}
	}
}

void Counter::Update()
{
	Delete();
	HamBurgerCompare();
	
	if (m_spriteFlag01 == true) {
		m_spriteTime01++;
		if (m_spriteTime01 > 60) {
			DeleteGO(m_spriteJudge01);
			m_spriteFlag01 = false;
			m_spriteTime01 = 0;
		}
	}
	if (m_spriteFlag02 == true) {
		m_spriteTime02++;
		if (m_spriteTime02 > 60) {
			DeleteGO(m_spriteJudge02);
			m_spriteFlag02 = false;
			m_spriteTime02 = 0;
		}
	}
	m_skinModelRender->SetPosition(m_position);
}