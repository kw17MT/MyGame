#include "stdafx.h"
#include "TrashCan.h"
#include "SkinModelRender.h"
#include "Player.h"
#include "PlayerGene.h"

bool TrashCan::Start()
{
	player[0] = FindGO<Player>("player01");
	player[1] = FindGO<Player>("player02");
	m_playerGene = FindGO<PlayerGene>("playerGene");

	//ゴミ箱モデルの設定
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/trashcan/trashcan.tkm", nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

	m_skinModelRender->SetScale(m_trashcanScale);
	//ゴミ箱に近づくと矢印が出るように
	m_targeting = NewGO<SkinModelRender>(0);
	m_targeting->Init("Assets/modelData/Arrow_Purple.tkm", nullptr, enModelUpAxisZ, m_position);
	m_targeting->InitShader("Assets/shader/modelTomei.fx", "FrontCulling", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_targeting->SetScale(m_targetScale);

	if (trashcanNo == 1) {
	m_targetPos = m_position;
	m_targetPos.y += 50.0f;
	m_targetPos.x -= 75.0f;
	m_targeting->SetPosition(m_targetPos);

	m_rot.SetRotationDegY(45.0f);
	}
	if (trashcanNo == 2) {
		m_targetPos = m_position;
		m_targetPos.y += 50.0f;
		m_targetPos.x += 75.0f;
		m_targeting->SetPosition(m_targetPos);

		m_rot.SetRotationDegY(-45.0f);
	}

	m_targeting->SetRotation(m_rot);

	return true;
}

float TrashCan::CalcDistance(Vector3 v1, Vector3 v2)
{
	Vector3 v3 = v1 - v2;
	float ans = v3.Length();

	return ans;
}

void TrashCan::Update()
{
	if (m_playerGene->GetPlayerGeneState() == true) {
		return;
	}
	if (player[0] == nullptr) {
		player[0] = FindGO<Player>("player01");
	}
	if (player[1] == nullptr) {
		player[1] = FindGO<Player>("player02");
	}

	float player01Distance = CalcDistance(player[0]->GetPosition(), m_position);
	float player02Distance = CalcDistance(player[1]->GetPosition(), m_position);

	//矢印の大きさ変更用。近づくと大きくなり、離れると小さくなる。
	if (trashcanNo == 1) {
		if (player01Distance < distance) {
			m_targetScale.x += 0.1f;
			m_targetScale.y += 0.1f;
			m_targetScale.z += 0.1f;

			if (m_targetScale.x >= 1.0f) {
				m_targetScale.x = 1.0f;
				m_targetScale.y = 1.0f;
				m_targetScale.z = 1.0f;
			}
			canTrash = true;
		}
		else {
			m_targetScale.x -= 0.1f;
			m_targetScale.y -= 0.1f;
			m_targetScale.z -= 0.1f;

			if (m_targetScale.x <= 0.0f) {
				m_targetScale.x = 0.0f;
				m_targetScale.y = 0.0f;
				m_targetScale.z = 0.0f;
			}
			canTrash = false;
		}
		m_targeting->SetScale(m_targetScale);
	}

	if (trashcanNo == 2) {
		if (player02Distance < distance) {
			m_targetScale.x += 0.1f;
			m_targetScale.y += 0.1f;
			m_targetScale.z += 0.1f;

			if (m_targetScale.x >= 1.0f) {
				m_targetScale.x = 1.0f;
				m_targetScale.y = 1.0f;
				m_targetScale.z = 1.0f;
			}
			canTrash = true;
		}
		else {
			m_targetScale.x -= 0.1f;
			m_targetScale.y -= 0.1f;
			m_targetScale.z -= 0.1f;

			if (m_targetScale.x <= 0.0f) {
				m_targetScale.x = 0.0f;
				m_targetScale.y = 0.0f;
				m_targetScale.z = 0.0f;
			}
			canTrash = false;
		}
		m_targeting->SetScale(m_targetScale);
	}

	if (targetUp == true) {
		m_targetPos.y += 1.0f;
		if (m_targetPos.y >= 75.0f) {
			targetUp = false;
		}
	}
	if (targetUp == false) {
		m_targetPos.y -= 1.0f;
		if (m_targetPos.y <= 50.0f) {
			targetUp = true;
		}
	}

	m_targeting->SetPosition(m_targetPos);
	//m_targeting->SetPosition(m_position);
	m_skinModelRender->SetPosition(m_position);
}