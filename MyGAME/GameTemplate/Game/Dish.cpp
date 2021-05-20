#include "stdafx.h"
#include "Dish.h"
#include "SkinModelRender.h"
#include "Level.h"
#include "Guzai.h"
#include "PlayerGene.h"
#include "PathMove.h"
#include "DishSpeedManeger.h"
#include "SoundSource.h"
#include "DishGene.h"

namespace
{
	const float MOVESPEED = 130.0f;
}

bool Dish::Start()
{
	m_lig.ambientLight.Set(0.98f, 0.98f, 0.98f);
	m_lig.directionalLight.direction.x = 1.0f;
	m_lig.directionalLight.direction.y = 1.0f;
	m_lig.directionalLight.direction.z = 1.0f;
	m_lig.directionalLight.color.Set(100.0f, 100.0f, 100.0f);
	m_lig.directionalLight.direction.Normalize();

	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/object/dish.tkm", nullptr, enModelUpAxisZ, m_position, &m_lig);
	m_scale = { 1.0f,1.0f,1.0f };
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);



	playerGene = FindGO<PlayerGene>("playerGene");
	m_speedManeger = FindGO<DishSpeedManeger>("speedManeger");
	m_dishGene = FindGO<DishGene>("dishGene");

	m_pathMove = std::make_unique<PathMove>();
	m_pathMove.get()->Init(m_position, MOVESPEED, enNormalLane);

	m_pathMove.get()
	
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
		//m_guzaiPos.y += 10.0f;
		m_guzaiPos.y += m_guzaiYPos;
		m_guzai->SetPosition(m_guzaiPos);
		if (m_guzaiYPos > 800.0f) {
			m_guzaiYPos -= 4.0f;
		}
		else if (m_guzaiYPos > 10.0f) {
			m_guzaiYPos -= 20.0f;
			if (m_dishGene->GetFallingSound() == false) {
				//音を鳴らす
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/falling2.wav", false);
				se->SetVolume(0.5f);
				se->Play(false);
				m_dishGene->SetFallingSound(true);
			}
			
		}
	}
	else {
		m_guzaiYPos = 1000.0f;
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
	else {
		if (m_dishGene->GetSetSound() == false) {
			//音を鳴らす
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/thi-n.wav", false);
			se->SetVolume(1.0f);
			se->Play(false);
			m_dishGene->SetSetSound(true);
		}
		
	}
	
	
	//自分の上の具材が持たれているならば
	if (m_guzai->state == 1) {
		isHavingGuzai = false;
	}

	//空の皿が規定数より多いので、空の皿だけに補充を開始する。
	if (playerGene->GetNoHavingDishCounter() >= maxNum2Refill) {
		m_guzaiTimer++;
		if (m_guzaiTimer > 60) {
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
				m_dishGene->SetFallingSound(false);
				m_dishGene->SetSetSound(false);
			}
			m_guzaiTimer = 0;
		}
	}

	if (m_speedManeger->GetSpeedUpState() == true) {
		float moveSpeed = MOVESPEED * 2.0f;
		m_pathMove.get()->ChangeMoveSpeed(moveSpeed);
	}
	if (m_speedManeger->GetSpeedUpState() == false) {
		m_pathMove.get()->ChangeMoveSpeed(MOVESPEED);
	}


	Move();

	m_skinModelRender->SetScale(m_scale);
}