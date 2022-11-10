#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow 
{
	SceneLight g_sceneLight;

	SceneLight::SceneLight()
	{
		Vector3 derectionLightDerection = { 1.0f,-0.5f,-1.0f };
		m_light.m_directionLight.SetDirection(derectionLightDerection);	//正規化して設定

		m_light.m_directionLight.SetColor({ 1.0f,1.0f,1.0f });			//カラーを設定

		SetAmbientLight({ 0.3f,0.3f,0.3f });							//環境光を設定

		m_light.m_pointLight.SetPosition({ 0.0f,50.0f,50.0 });			//ポジションを設定

		m_light.m_pointLight.SetColor({ 50.0f,0.0f,0.0f });				//カラーを設定

		m_light.m_pointLight.SetRange(100.0f);							//影響範囲を設定

		m_light.m_spotLight.SetPosition({ 0.0f,50.0f,100.0f });			//ポジションを設定

		m_light.m_spotLight.SetColor({ 0.0f,0.0f,0.0f });				//カラーを設定

		Vector3 spotLightDerection = { 1.0f,-1.0f,1.0f };
		m_light.m_spotLight.SetDirection(spotLightDerection);			//正規化して設定

		m_light.m_spotLight.SetRange(300.0f);							//影響範囲を設定

		m_light.m_spotLight.SetAngle(Math::DegToRad(25.0f));			//角度を設定
	}
};