#pragma once
class Player;

//開始と"同時に"プレイヤー2体を"同じところ"に出すとエラーが発生。
//それを回避するための生成器
//あとポジションの調整も
class PlayerGene : public IGameObject
{
private:
	Vector3 player01Pos = { 1000.0f,0.0f,0.0f };
	Vector3 player02Pos = { -1000.0f, 0.0f, 0.0f };
	Quaternion player01Rot;
	Quaternion player02Rot;

	int playerNum = 0;
	bool isWorking = true;
public:
	~PlayerGene() {};

	bool Start();
	void Update();

	Player* player[2];
};

