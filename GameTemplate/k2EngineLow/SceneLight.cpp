#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow 
{
	SceneLight g_sceneLight;

	SceneLight::SceneLight()
	{
		Vector3 derectionLightDerection = { 1.0f,-0.5f,-1.0f };
		m_light.m_directionLight.SetDirection(derectionLightDerection);	//���K�����Đݒ�

		m_light.m_directionLight.SetColor({ 1.0f,1.0f,1.0f });			//�J���[��ݒ�

		SetAmbientLight({ 0.3f,0.3f,0.3f });							//������ݒ�

		m_light.m_pointLight.SetPosition({ 0.0f,50.0f,50.0 });			//�|�W�V������ݒ�

		m_light.m_pointLight.SetColor({ 50.0f,0.0f,0.0f });				//�J���[��ݒ�

		m_light.m_pointLight.SetRange(100.0f);							//�e���͈͂�ݒ�

		m_light.m_spotLight.SetPosition({ 0.0f,50.0f,100.0f });			//�|�W�V������ݒ�

		m_light.m_spotLight.SetColor({ 0.0f,0.0f,0.0f });				//�J���[��ݒ�

		Vector3 spotLightDerection = { 1.0f,-1.0f,1.0f };
		m_light.m_spotLight.SetDirection(spotLightDerection);			//���K�����Đݒ�

		m_light.m_spotLight.SetRange(300.0f);							//�e���͈͂�ݒ�

		m_light.m_spotLight.SetAngle(Math::DegToRad(25.0f));			//�p�x��ݒ�
	}
};