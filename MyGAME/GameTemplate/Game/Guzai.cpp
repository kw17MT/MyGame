#include "stdafx.h"
#include "Guzai.h"
#include "ModelRender.h"
#include "math.h"


bool Guzai::Start()
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/box.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_modelUpAxis = enModelUpAxisY;

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modeldata.m_skeleton = &m_skeleton;

	model.Init(modeldata);

	Vector3 pos = { 0.0f,100.0f,-500.0f };

	m_charaCon.Init(0.0f, 0.0f, pos);

	return true;
}

Vector3 Guzai::GetPosition()
{
	Vector3 Pos = m_charaCon.GetPosition();
	return Pos;
}

void Guzai::SetPosition(Vector3 pos)
{
	m_charaCon.SetPosition(pos);
}

void Guzai::Update()
{
	//�X�P���g�����X�V�B
	m_skeleton.Update(model.GetWorldMatrix());

	ModelRender* mr = FindGO<ModelRender>("player01");
	Vector3 plPos = mr->GetPosition();
	Vector3 GuzaiPos = m_charaCon.GetPosition();

	Vector3 Kitchen01 = { 900.0f, 0.0f, 0.0f };


	float guzai2Pl = (GuzaiPos.x - plPos.x) * (GuzaiPos.x - plPos.x) + (GuzaiPos.y - plPos.y) * (GuzaiPos.y - plPos.y) + (GuzaiPos.z - plPos.z) * (GuzaiPos.z - plPos.z);
	guzai2Pl = sqrt(guzai2Pl);

	//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ��@100���߂��ʒu�ɂ���B
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (mr->have == 0 && guzai2Pl < 200.0f) {
			state = 1;
			mr->have = 1;
		}
	}
	//������Ă������ނ̈ʒu���v���C���[�̏�ɂ���B
	if (state == 1) {
		plPos.y += 100.0f;
		SetPosition(plPos);
	}

	//B�{�^���������ăL�b�`�����߂��ɂ�������A���ς܂�Ă��鐔�ɉ����Ă����ꏊ��ς���B
	if (g_pad[0]->IsPress(enButtonB)) {
		float Diff2Kit = (Kitchen01.x - plPos.x) * (Kitchen01.x - plPos.x) + (Kitchen01.y - plPos.y) * (Kitchen01.y - plPos.y) + (Kitchen01.z - plPos.z) * (Kitchen01.z - plPos.z);
		if (state == 1 && Diff2Kit < 400.0f) {
			state = 0;
			put = 1;
			mr->have = 0;
			
			Kitchen01.y += stack * 100.0f;
			SetPosition(Kitchen01);
			stack++;
		}
	}

	//������Ă��Ȃ��@���@��x���u����Ă��Ȃ�
	if (state == 0 && put == 0) {
		Vector3 moveSpeed = { 0.0f,0.0f,0.0f };
		time++;
		if (time < 500) {
			moveSpeed.z = 2.0f;
		}
		if (time >= 500 && time < 600) {
			moveSpeed.x = 2.0f;
		}
		if (time >= 600) {
			moveSpeed.z = -2.0f;
		}
		if (GuzaiPos.z < -1000.0f) {
			time = 0;
			DeleteGO(this);
		}
		m_charaCon.Execute(moveSpeed, 1.0f);
	}

	

	
	model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}
