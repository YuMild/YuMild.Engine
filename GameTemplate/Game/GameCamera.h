#pragma once

/// <summary>
/// ゲームカメラ
/// </summary>
class GameCamera : public IGameObject
{
private:

	bool Start()override;
	void Update()override;
};