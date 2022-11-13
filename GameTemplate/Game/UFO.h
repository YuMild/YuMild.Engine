#pragma once

#include "EnemyObject.h"

class SpawnManager;

/// <summary>
/// UFO
/// </summary>
class UFO : public EnemyObject
{
public:

	UFO();
	~UFO();
	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const override
	{
		return m_position;
	}

private:

	/// <summary>
	/// 動作を管理
	/// </summary>
	void Move();

	//クラス
	SpawnManager*			m_spawnManager;

	//モデル
	ModelRender				m_modelRender;

	//UFO
	Vector3					m_position;
	Quaternion				m_rotation;

	//パス移動
	std::vector<Vector3>	m_pointList;
	Vector3					m_target;
	int						m_pointNum;
};