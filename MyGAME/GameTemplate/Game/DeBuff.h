#pragma once

class PathMove;

class DeBuff : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

	//�ǂ���ɗ���Ă���o�t�A�C�e����
	//�P�A���@�Q�A�E
	int BuffNo = 0;

	//�ړ��������s���N���X�B
	std::unique_ptr<PathMove> m_pathMove;

public:
	//���f���f�[�^�A�e�A�����ʒu�ݒ�B
	DeBuff();

	bool Start();

	//�A�C�e���̈ړ��AA�{�^���ŏ����鏈���B
	void Update();

	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	//�ǂ��瑤�ɗ���Ă��邩�̐ݒ�B
	void SetBuffNo(int num) { BuffNo = num; }

	void Render(RenderContext& rc) { model.Draw(rc); }

	//Update()�ŃC���N�������g����B
	int time = 0;
	int BuffExist = 0;

	bool m_isDeBuffLane = false;
};

