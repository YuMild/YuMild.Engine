#pragma once

class Game : public IGameObject
{
public:

	bool Start();
	void Render(RenderContext& renderContext);
	void Update();

private:

	//モデルレンダー
	ModelRender m_playerModelRender;
	ModelRender stageModelRender;

	//キャラクターコントローラー
	CharacterController m_characterController;

	//プレイヤー
	Vector3 m_playerPosition;
	Vector3 m_moveSpeed;

	//ポイントライト
	Vector3 m_pointLightPosition;
};