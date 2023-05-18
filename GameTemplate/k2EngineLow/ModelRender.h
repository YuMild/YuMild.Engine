#pragma once

namespace
{
	enum DrowMode
	{
		Normal,
		Dithering
	};
}

namespace  nsK2EngineLow 
{
	class ModelRender : public Noncopyable
	{
	public:

		ModelRender();
		~ModelRender();

		/// <summary>
		/// </summary>
		/// <param name="filePath"></param>
		/// <param name="shadow"></param>
		/// <param name="trans"></param>
		/// <param name="animationClips"></param>
		/// <param name="numAnimationClips"></param>
		/// <param name="enModelUpAxis"></param>
		/// <param name="emission"></param>
		void Init(const char* filePath,
			int shadow = Normal,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			Texture* emission = nullptr);

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rc"></param>
		void Draw(RenderContext& rc);

		/// <summary>
		/// カメラ指定の描画
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="camera"></param>
		void Draw(RenderContext& rc, Camera& camera);

		/// <summary>
		/// ポジションを設定
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		/// <summary>
		/// スケールを設定
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// 回転を設定
		/// </summary>
		/// <param name="rotation"></param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		///	アニメーションを再生
		/// </summary>
		/// <param name="animNo"></param>
		/// <param name="interpolateTime"></param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		/// <summary>
		/// アニメーションが再生状況を取得
		/// </summary>
		/// <returns></returns>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		/// <summary>
		/// アニメーションの再生速度を設定
		/// </summary>
		/// <param name="animationSpeed"></param>
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

	private:

		/// <summary>
		/// ボーンデータを設定
		/// </summary>
		/// <param name="filePath"></param>
		void InitSkeleton(const char* filePath);

		/// <summary>
		/// アニメーションを作成
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
		Skeleton		m_skeleton;
	};
}