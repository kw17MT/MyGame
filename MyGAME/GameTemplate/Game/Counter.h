#pragma once
class Counter : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

	//�\���ł��郁�j���[�̎�ށB
	int menuNum = 3;

	//�O�D�`�[�Y�@�P�D�G�b�O�@�Q�D���^�X�@�R�D�p�e�@�S�D�g�}�g
	int burger01[3] = { 3,0,2 };
	int burger02[4] = { 3,4,4,2 };
	int burger03[4] = { 2,4,0,3 };

	//�J�E���^�[�ԍ��@�P�����A�Q���E
	int CounterNo = 0;
	//���i�̃n���o�[�K�[��������̂��̕ϐ�
	int StackNum = 0;

public:
	Counter();
	bool Start();
	void Update();
	void Delete();
	void SetPosition(Vector3 pos) { m_charaCon.SetPosition(pos); }
	void SetCounterNo(int num) { CounterNo = num; }
	void SetStackNum(int num) { StackNum = num; }
	void SetStack0() { StackNum = 0; }

	bool Judge();

	void Render(RenderContext& rc) { model.Draw(rc); }

	int Delay = 0;
};
