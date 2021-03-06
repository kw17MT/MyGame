#pragma once
#include <vector>;
#include "PathMove.h"
class SkinModelRender;
class Guzai;
class PlayerGene;
class PathMove;
class DishSpeedManeger;
class CSoundSource;
class DishGene;
class GuzaiGene;

class Dish : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;					//皿の位置
	Vector3 m_guzaiPos = Vector3::Zero;					//上に乗っける具材の位置
	Vector3 m_scale = Vector3::One;						//皿の拡大情報

	bool m_isHavingGuzai = false;						//自分（この皿）は具材を乗せているか。
	const int m_maxNum2Refill = 5;						//補充を開始する最大値		２はTo
	bool m_isCompletedFirstPop = false;					//全ての皿の上に具材を設置できたか
	float m_guzaiYPos = 1000.0f;						//具材の高さ。
	int m_guzaiTimer = 0;								//具材を再POPさせるときに遅延を生じさせるもの
	bool m_soundFlag = false;							//今、音を鳴らしているか
	int m_guzaiNo = 0;									//具材は何番目の位置に格納されているか

	std::unique_ptr<PathMove> m_pathMove;				//移動処理を行うクラス。

	Light m_lig;										//皿独自のライト
public:
	Dish() {}
	~Dish();

	/**
	 * @brief モデルの初期化と皿独自のライトの設定
	 * @return true
	*/
	bool Start();
	void Update();

	/**
	 * @brief 新しい位置の設定
	 * @param pos 新しい位置
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }

	/**
	 * @brief 新しい拡大率の設定
	 * @param scale 新しい拡大率
	*/
	void SetScale(Vector3 scale) { m_scale = scale; }

	/**
	 * @brief この皿は具材を持っているかどうかの設定
	 * @param state TRUE＝持っている、FALSE＝持っていない。
	*/
	void SetHavingState(bool state) { m_isHavingGuzai = state; }

	/**
	 * @brief 輪の内側にある皿の回転を表示しているものの回転方向を取得
	 * @return 回転方向
	*/
	EnCycleDirection GetCycleDirection() { return m_pathMove->GetCycleDirection(); }

	/**
	 * @brief 皿自身と上の具材の移動をおこなう。
	*/
	void Move();

private:
	SkinModelRender* m_skinModelRender = nullptr;
	Guzai* m_guzai = nullptr;
	PlayerGene* m_playerGene = nullptr;
	DishSpeedManeger* m_speedManeger = nullptr;
	CSoundSource* m_se = nullptr;
	DishGene* m_dishGene = nullptr;
	GuzaiGene* m_guzaiGene = nullptr;

	std::vector<Guzai*> v_m_guzai;
};

