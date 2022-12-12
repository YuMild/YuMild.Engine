#pragma once

namespace nsK2EngineLow
{
	/// <summary>
	/// �f�B���N�V�������C�g
	/// </summary>
	struct DirectionLight
	{
	public:
		/// <summary>
		/// ���C�g�̕�����ݒ�
		/// </summary>
		/// <param name="direction"></param>
		void SetDirection(Vector3& direction)
		{
			direction.Normalize();
			m_direction = direction;
		}
		/// <summary>
		/// ���C�g�̕������擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetDirection()const
		{
			return m_direction;
		}
		/// <summary>
		/// ���C�g�̃J���[��ݒ�
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector3& color)
		{
			m_color = color;
		}
	private:
		Vector3 m_direction;
		float m_pad1;
		Vector3 m_color;
		float m_pad2;
	};

	/// <summary>
	/// �|�C���g���C�g
	/// </summary>
	struct PointLight
	{
	public:
		/// <summary>
		/// ���C�g�̃|�W�V������ݒ�
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// ���C�g�̃|�W�V�������擾
		/// </summary>
		/// <returns></returns>
		const Vector3 GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// ���C�g�̃J���[��ݒ�
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector3& color)
		{
			m_color = color;
		}
		/// <summary>
		/// ���C�g�̉e���͈͂�ݒ�
		/// </summary>
		/// <param name="range"></param>
		void SetRange(const float& range)
		{
			m_range = range;
		}
	private:
		Vector3 m_position;
		float m_pad3;
		Vector3 m_color;
		float m_range;
	};

	/// <summary>
	/// �X�|�b�g���C�g
	/// </summary>
	struct SpotLight
	{
	public:
		/// <summary>
		/// ���C�g�̃|�W�V������ݒ�
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// ���C�g�̃J���[��ݒ�
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector3& color)
		{
			m_color = color;
		}
		/// <summary>
		/// ���C�g�̉e���͈͂�ݒ�
		/// </summary>
		/// <param name="range"></param>
		void SetRange(const float& range)
		{
			m_range = range;
		}
		/// <summary>
		/// ���C�g�̕�����ݒ�
		/// </summary>
		/// <param name="direction"></param>
		void SetDirection(Vector3& direction)
		{
			direction.Normalize();
			m_direction = direction;
		}
		/// <summary>
		/// ���C�g�̊p�x�̐ݒ�
		/// </summary>
		/// <param name="angle"></param>
		void SetAngle(const float& angle)
		{
			m_angle = angle;
		}
		/// <summary>
		/// ��]��K�p
		/// </summary>
		/// <param name="rotation"></param>
		void ApplyRotation(const Quaternion& rotation)
		{
			rotation.Apply(m_direction);
		}
		/// <summary>
		/// ���C�g�̕������擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetDirection()const
		{
			return m_direction;
		}
	private:
		Vector3 m_position;
		float m_pad4;
		Vector3 m_color;
		float m_range;
		Vector3 m_direction;
		float m_angle;
	};

	struct Light
	{
		DirectionLight m_directionLight;
		PointLight m_pointLight;
		SpotLight m_spotLight;
		Vector3 m_ambientLight;
		float m_pad5;
		Vector3 m_eyePos;
	};

	class SceneLight
	{
	public:
		SceneLight();
		/// <summary>
		/// ���C�g�̍\���̂��擾
		/// </summary>
		/// <returns></returns>
		Light& GetLight()
		{
			return m_light;
		}
		/// <summary>
		/// ������ݒ�
		/// </summary>
		/// <param name="color"></param>
		void SetAmbientLight(const Vector3& color)
		{
			m_light.m_ambientLight = color;
		}
		/// <summary>
		/// ���_�̃|�W�V������ݒ�
		/// </summary>
		/// <param name="position"></param>
		void SetEyePosition(const Vector3& position)
		{
			m_light.m_eyePos = position;
		}
		/// <summary>
		/// �f�B���N�V�������C�g�̃J���[��ݒ�
		/// </summary>
		/// <param name="color"></param>
		void SetDirectionColor(const Vector3& color)
		{
			m_light.m_directionLight.SetColor(color);
		}
		/// <summary>
		/// �f�B���N�V�������C�g�̕������擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetDirectionLightDirection()const
		{
			return m_light.m_directionLight.GetDirection();
		}
		/// <summary>
		/// �|�C���g���C�g�̃|�W�V������ݒ肷��
		/// </summary>
		/// <param name="position"></param>
		void SetPointLightPosition(const Vector3& position)
		{
			m_light.m_pointLight.SetPosition(position);
		}
		/// <summary>
		/// �|�C���g���C�g�̃|�W�V�������擾
		/// </summary>
		/// <returns></returns>
		const Vector3 GetPointLightPosition()const
		{
			return m_light.m_pointLight.GetPosition();
		}
		/// <summary>
		/// �X�|�b�g���C�g�ɉ�]��K�p
		/// </summary>
		/// <param name="rotation"></param>
		void ApplySpotLightRotation(const Quaternion& rotation)
		{
			m_light.m_spotLight.ApplyRotation(rotation);
		}
		/// <summary>
		/// �X�|�b�g���C�g�̕������擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetSpotLightDirection()const
		{
			return m_light.m_spotLight.GetDirection();
		}

	private:
		Light m_light;
	};

	extern SceneLight g_sceneLight;
}