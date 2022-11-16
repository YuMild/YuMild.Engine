#pragma once

/// <summary>
/// �G�l���M�[
/// </summary>
class Energy : public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

private:

	/// <summary>
	/// ����̊Ǘ�
	/// </summary>
	void Move();

	/// <summary>
	/// �摜�̊Ǘ�
	/// </summary>
	void Sprite();

	//�摜
	SpriteRender	m_windowSR;
	SpriteRender	m_circleSR;
	SpriteRender	m_gaugeSR;

	//�G�l���M�[
	float			m_energy = 0.0f;

	//��]
	float			m_rotationNumber = 0.0f;
	Quaternion		m_rotation;
};