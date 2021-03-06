#pragma once
class SkinModelRender;
#include "SkinModelRender.h"

class Floor : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;				//床の位置
	Vector3 m_scale = Vector3::One;					//床の拡大率

	bool isRed = false;								//赤い床にするかどうか
	Light m_lig;									//床独自のライト
public:
	~Floor();

	/**
	 * @brief モデルの初期化を行う
	 * @return true
	*/
	bool Start();

	/**
	 * @brief 位置の更新を行う
	*/
	void Update();

	/**
	 * @brief 新しい位置を設定する。
	 * @param pos 新しい位置
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }

	/**
	 * @brief 赤い床にするか青い床にするか
	 * @param filePath モデルのファイルパス
	*/
	void ChangeModel(const char* filePath) { m_skinModelRender->ChangeModel(filePath); }

	/**
	 * @brief 赤い床かどうか設定する
	 * @param red TRUE＝赤　FALSE＝青
	*/
	void SetRed(bool red) { isRed = red; }

private:
	SkinModelRender* m_skinModelRender = nullptr;
};

