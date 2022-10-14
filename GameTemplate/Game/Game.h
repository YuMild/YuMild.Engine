#pragma once

class Game : public IGameObject
{
public:

	bool Start();
	void Render(RenderContext& renderContext);
	void Update();

private:

	//���f�������_�[
	ModelRender m_playerModelRender;
	ModelRender stageModelRender;

	//�L�����N�^�[�R���g���[���[
	CharacterController m_characterController;

	//�v���C���[
	Vector3 m_playerPosition;
	Vector3 m_moveSpeed;

	//�|�C���g���C�g
	Vector3 m_pointLightPosition;
};