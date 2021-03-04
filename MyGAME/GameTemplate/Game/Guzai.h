#pragma once

class Guzai : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

public:	
	bool Start();
	void Update();
	
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);

	void Render(RenderContext& rc)
	{
		model.Draw(rc);
	}

	//Update()でインクリメントする。
	int time = 0;
	//１ならば持たれている。
	int state = 0;
	//１ならばもうキッチンに置かれている。
	int put = 0;
	//何段積んでるか
	int stack = 0;
};

