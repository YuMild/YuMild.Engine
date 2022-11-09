#pragma once

class SpawnManager;

/// <summary>
/// UFO
/// </summary>
class UFO : public IGameObject
{
public:

	UFO();
	~UFO();
	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	void Move();

private:

	SpawnManager*			m_spawnManager;

	ModelRender				m_modelRender;

	Vector3					m_position;
	Quaternion				m_rotation;

	//ƒpƒXˆÚ“®“I‚È
	std::vector<Vector3>	m_pointList;
	Vector3					m_target;
	int						m_pointNum;
};