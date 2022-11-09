#pragma once

namespace
{
	enum ShadowMode
	{
		ShadowDrop,
		ShadowRecieve,
		ShadowRecieveAndDrop,
		ShadowNone,
		Dithering
	};
}

namespace  nsK2EngineLow {
	class ModelRender : public Noncopyable
	{
	public:
		ModelRender();
		~ModelRender();

		/// <summary>
		/// ���f���̕`��
		/// �V���h�E
		/// ShadowDrop = �V���h�E�𗎂Ƃ�
		/// ShadowRecieve = �V���h�E���󂯂�
		/// ShadowRecieveAndDrop = �V���h�E���󂯂��Ƃ�
		/// ShadowNone = �V���h�E�C���O�����Ȃ�
		/// ������
		/// true = �������`��
		/// </summary>
		/// <param name="filePath"></param>
		void Init(const char* filePath,
			int shadow = ShadowNone,
			bool trans = false,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);

		/// <summary>
		/// �V���h�E�}�b�v�𗎂Ƃ����f�����쐬
		/// </summary>
		void InitDrawShadowMapModel(const char* filePath);

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc"></param>
		void Draw(RenderContext& rc);

		/// <summary>
		/// �J�����w��̕`��
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="camera"></param>
		void Draw(RenderContext& rc, Camera& camera);

		/// <summary>
		/// �J�����w��̃V���h�E�}�b�v�̕`��
		/// </summary>
		/// <param name="rc"></param>
		void ShadowMapDraw(RenderContext& rc, Camera& camera);

		/// <summary>
		/// �|�W�V������ݒ�
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		/// <summary>
		/// �X�P�[����ݒ�
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rotation"></param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		///	�A�j���[�V�������Đ�
		/// </summary>
		/// <param name="animNo"></param>
		/// <param name="interpolateTime"></param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		/// <summary>
		/// �A�j���[�V�������Đ��󋵂��擾
		/// </summary>
		/// <returns></returns>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		/// <summary>
		/// �A�j���[�V�����̍Đ����x��ݒ�
		/// </summary>
		/// <param name="animationSpeed"></param>
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

	private:

		/// <summary>
		/// �{�[���f�[�^��ݒ�
		/// </summary>
		/// <param name="filePath"></param>
		void InitSkeleton(const char* filePath);

		/// <summary>
		/// �A�j���[�V�������쐬
		/// </summary>
		/// <param name="animationClips"></param>
		/// <param name="numAnimationClips"></param>
		/// <param name="enModelUpAxis"></param>
		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);

	private:

		AnimationClip*	m_animationClips = nullptr;
		Animation		m_animation;
		int				m_numAnimationClips = 0;
		float			m_animationSpeed = 1.0f;
		Vector3			m_position = Vector3::Zero;
		Vector3			m_scale = Vector3::One;
		Quaternion		m_rotation = Quaternion::Identity;
		Model			m_model;
		Model			m_drawShadowModel;
		Model			m_shadowRecieverModel;
		Skeleton		m_skeleton;
	};
}