#pragma once

class Game;

/// <summary>
/// コンテナ
/// </summary>
class Container : public IGameObject
{
public:

	~Container();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

private:

	/// <summary>
	/// 動作を管理
	/// </summary>
	void Move();

	//クラス
	Game* m_game = nullptr;

	//モデル
	ModelRender		m_containerMR;

	//動作
	Vector3			m_position = Vector3::Zero;
	float			m_scale = 0.0f;
	Vector3			m_target = Vector3::Zero;
};