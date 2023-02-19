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
	/// ���f���̃|�W�V������ݒ�
	/// </summary>
	/// <param name="position"></param>
	virtual const void SetModelPosition(const Vector3 position);

	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	virtual const Vector3& GetModelPosition() const;

	/// <summary>
	/// �摜�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="position"></param>
	virtual const void SetSpritePosition(const Vector3 position);

	/// <summary>
	/// �摜�̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	virtual const Vector3& GetSpritePosition() const;

	/// <summary>
	/// ���f���̉�]��ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	virtual const void SetModelRotation(const float rotation);

	/// <summary>
	/// ���f���̉�]���擾
	/// </summary>
	/// <returns></returns>
	virtual const Quaternion& GetModelRotation() const;

	/// <summary>
	/// ���f�������v���ɉ�]
	/// </summary>
	virtual const void SetModelRotationTurnRight();

	/// <summary>
	/// ���f���𔽎��v���ɉ�]
	/// </summary>
	virtual const void SetModelRotationTurnLeft();

	/// <summary>
	/// �^���b�g�̍U���Ԑ���ݒ�
	/// </summary>
	virtual const void SetAttackReady(bool ready);

	/// <summary>
	/// �^���b�g�̍U���Ԑ����擾
	/// </summary>
	/// <returns></returns>
	virtual const bool& GetAttackReady() const;

	/// <summary>
	/// �^���b�g�̏�Ԃ��擾
	/// </summary>
	/// <returns></returns>
	virtual const bool& GetAlive() const;

	/// <summary>
	/// �^���b�g��HP�����Z����
	/// </summary>
	/// <param name="value"></param>
	virtual const void AddTurretHP(float value);

	/// <summary>
	/// �^���b�g��HP�����Z����
	/// </summary>
	/// <param name="value"></param>
	virtual const void SubTurretHP(float value);

	/// <summary>
	/// �f�o�t��ݒ�
	/// </summary>
	virtual const void SetDebuff();
};