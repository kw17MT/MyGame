#include "stdafx.h"
#include "Dish.h"
#include "SkinModelRender.h"
#include "Level.h"
#include "Guzai.h"
#include "PlayerGene.h"
#include "PathMove.h"

namespace
{
	const float MOVESPEED = 130.0f;
}

bool Dish::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	/*m_skinModelRender->Init("Assets/modelData/gu/egg.tkm", nullptr, enModelUpAxisZ, m_position);*/
	m_skinModelRender->Init("Assets/modelData/object/conveyor.tkm", nullptr, enModelUpAxisZ, m_position);
	Vector3 scale = { 0.2f,0.2f,0.2f };
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

	SetScale({ 1.0f,0.2f,1.0f });

	playerGene = FindGO<PlayerGene>("playerGene");
	
	m_pathMove = std::make_unique<PathMove>();
	m_pathMove.get()->Init(m_position, MOVESPEED, enNormalLane);

	m_skinModelRender->SetNewModel();

	return true;
}

void Dish::Move()
{
	//皿をウェイポイントで移動させる。
	m_position = m_pathMove.get()->Move();
	m_skinModelRender->SetPosition(m_position);
	//最後のポイントまで到達したら。
	if (m_pathMove.get()->GetIsFinalPoint())
	{
	}

	//具材を皿の上に移動させる
	if (isHavingGuzai == true) {
		m_guzaiPos = m_position;
		m_guzaiPos.y += 10.0f;
		m_guzai->SetPosition(m_guzaiPos);
	}
}

void Dish::Update()
{
	//最初だけすべての皿の上に出す。
	if (isCompletedFirstPop == false) {
		if (playerGene->GetPlayerGeneState() == false) {
				m_guzai = NewGO<Guzai>(0);
				isHavingGuzai = true;

				isCompletedFirstPop = true;
		}
	}

	

		//このままだと、とった瞬間にまた出してしまう
		//具材が持たれていたら、皿に具材がないことを知らせる。
		//具材がとられている間ずっとインクリメントしてしまうため変数が大きくなりすぎてすぐに補充してしまう

		//具材デストラクタでnoHavingDishの変数を1度インクリメントしている。
		if (m_guzai->state == 1) {
			isHavingGuzai = false;
			//playerGene->AddNoHavingDishCounter();
		}

		//空の皿が規定数より多いので、空の皿だけに補充を開始する。
		if (playerGene->GetNoHavingDishCounter() >= maxNum2Refill) {
			if (isHavingGuzai == false) {
				m_guzai = NewGO<Guzai>(0);
				isHavingGuzai = true;
				
				//補充した皿の枚数を１足す
				playerGene->AddRefilledNum();
			}
			//補充した皿の数が空だった皿の数と同じになったら、０で初期化
			if (playerGene->GetRefilledNum() >= maxNum2Refill) {
				playerGene->ResetNohavingDishCounter();
				playerGene->ResetRefilledNum();
			}
		}

		Move();

	//m_skinModelRender->SetScale(m_scale);
}