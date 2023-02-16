#pragma once

class Game;

/// <summary>
/// �R���e�i
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
	/// ������Ǘ�
	/// </summary>
	void Move();

	//�N���X
	Game* m_game = nullptr;

	//���f��
	ModelRender		m_containerMR;

	//����
	Vector3			m_position = Vector3::Zero;
	float			m_scale = 0.0f;
	Vector3			m_target = Vector3::Zero;
};