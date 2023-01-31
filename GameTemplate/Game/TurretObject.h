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
	virtual void SetModelPosition(const Vector3& position);

	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetModelPosition() const;

	/// <summary>
	/// �摜�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="position"></param>
	virtual void SetSpritePosition(const Vector3& position);

	/// <summary>
	/// �摜�̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetSpritePosition() const;

	/// <summary>
	/// ���f���̉�]��ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	virtual void SetModelRotation(const float rotation);

	/// <summary>
	/// ���f���̉�]���擾
	/// </summary>
	/// <returns></returns>
	virtual Quaternion GetModelRotation() const;

	/// <summary>
	/// ���f�������v���ɉ�]
	/// </summary>
	virtual void SetModelRotationTurnRight();

	/// <summary>
	/// ���f���𔽎��v���ɉ�]
	/// </summary>
	virtual void SetModelRotationTurnLeft();

	/// <summary>
	/// �^���b�g�̍U���Ԑ���ݒ�
	/// </summary>
	virtual void SetAttackReady(bool ready);

	/// <summary>
	/// �^���b�g�̍U���Ԑ����擾
	/// </summary>
	/// <returns></returns>
	virtual bool GetAttackReady() const;

	/// <summary>
	/// �^���b�g�̏�Ԃ��擾
	/// </summary>
	/// <returns></returns>
	virtual bool GetAlive() const;

	/// <summary>
	/// �^���b�g��HP�����Z����
	/// </summary>
	/// <param name="value"></param>
	virtual void AddTurretHP(float value);

	/// <summary>
	/// �^���b�g��HP�����Z����
	/// </summary>
	/// <param name="value"></param>
	virtual void SubTurretHP(float value);

	/// <summary>
	/// �f�o�t��ݒ�
	/// </summary>
	virtual void SetDebuff();
};