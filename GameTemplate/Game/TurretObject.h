#pragma once

/// <summary>
/// �^���b�g�̊��N���X
/// </summary>
class TurretObject : public IGameObject
{
public:

	/// <summary>
	/// �f�X�g���N�^�͕K��virtual�ō쐬����
	/// </summary>
	virtual ~TurretObject();

	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetModelPosition() const = 0;
};