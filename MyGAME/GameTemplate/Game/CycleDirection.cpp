#include "stdafx.h"
#include "CycleDirection.h"
#include "SpriteRender.h"
#include "GameDirector.h"

namespace{
	const int WIDTH = 512;
	const int HEIGHT = 512;
}

CycleDirection::~CycleDirection()
{
	DeleteGO(m_sprite);
}

bool CycleDirection::Start()
{
	m_sprite = NewGO<SpriteRender>(0);

	//�X�v���C�g������
	switch (m_direction) {
	case Forward:
		m_sprite->Init("Assets/Image/forward_dir.dds", WIDTH, HEIGHT);
		break;
	case Reverse:
		m_sprite->Init("Assets/Image/reverse_dir.dds", WIDTH, HEIGHT);
		break;
	case FixedForward:
		m_sprite->Init("Assets/Image/forward.dds", WIDTH, HEIGHT);
		break;
	case FixedReverse:
		m_sprite->Init("Assets/Image/reverse.dds", WIDTH, HEIGHT);
		break;
	defalt:
		break;
	}

	//�\���ꏊ������
	switch (m_side) {
	case Left:
		m_sprite->SetPosition({ 220.0f, 80.0f,0.0f });
		break;
	case Right:
		m_sprite->SetPosition({ -220.0f, 80.0f,0.0f });
		break;
	case Up:
		m_sprite->SetPosition({ 0.0f, 250.0f,0.0f });
		break;
	default:
		break;
	}

	//�����ɂ��Ă���
	m_sprite->SetColor({ 1.0f,1.0f,1.0f,0.0f });
	//�s�{�b�g��ݒ�
	m_sprite->SetPivot({ 0.5f,0.5f });
	m_sprite->SetScale(m_scale);

	return true;
}

void CycleDirection::ChangeSpriteForward()
{
	//��]�������t�]�̂Ƃ��A���]�̃^�C�~���O�Ő��]�X�v���C�g�ɕύX
	if (m_direction == Reverse) {
		m_sprite->Init("Assets/Image/forward_dir.dds", WIDTH, HEIGHT);
	}
}

void CycleDirection::ChangeSpriteReverse()
{
	//��]���������]�̂Ƃ��A�t�]�̃^�C�~���O�ŋt�]�X�v���C�g�ɕύX
	if (m_direction == Forward) {
		m_sprite->Init("Assets/Image/reverse_dir.dds", WIDTH, HEIGHT);
	}
}

void CycleDirection::ChangeFixedSpriteForward()
{
	if (m_direction == FixedReverse) {
		m_sprite->Init("Assets/Image/forward.dds", WIDTH, HEIGHT);
	}
}

void CycleDirection::ChangeFixedSpriteReverse()
{
	if (m_direction == FixedForward) {
		m_sprite->Init("Assets/Image/reverse.dds", WIDTH, HEIGHT);
	}
}

void CycleDirection::Update()
{
	/////////////////////////////////////////////////////
	//���ʕ���
	//�Q�[���v���C���łȂ����Update���������Ȃ�
	if (!GetGameDirector().GetIsGamePlay()) {
		return;
	}

	//�J�n���Ƀt�F�[�h�C������
	alpha += 1.0f / 60.0f;
	if (alpha > 1.0f) {
		alpha = 1.0f;
	}
	/////////////////////////////////////////////////////

	/////////////////////////////////////////////////////
	//��]����X�v���C�g�̂Ƃ�
	if (m_direction == Forward || m_direction == Reverse) {
		//��]�p�x�C��
		if (m_direction == Forward) {
			angle += 120.0f / 60.0f;
			if (angle > 360.0f) {
				angle = 0.0f;
			}
		}
		else if (m_direction == Reverse) {
			angle -= 120.0f / 60.0f;
			if (angle < 0.0f) {
				angle = 360.0f;
			}
		}

		m_sprite->SetColor({ 2.0f,2.0f,2.0f,alpha });
	}
	/////////////////////////////////////////////////////

	/////////////////////////////////////////////////////
	//�Œ�\���X�v���C�g�̂Ƃ�
	if (m_direction == FixedForward || m_direction == FixedReverse) {
		m_sprite->SetColor({ 1.0f,1.0f,1.0f,alpha });
		m_sprite->SetScale({ 0.25f,0.25f,1.0f });
	}
	/////////////////////////////////////////////////////

	m_rotation.SetRotationDeg(Vector3::AxisZ, angle);

	m_sprite->SetRotation(m_rotation);
}
