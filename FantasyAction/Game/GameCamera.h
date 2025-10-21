#pragma once
#include "camera/SpringCamera.h"

class Player;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void CameraSet();
	void CameraMove();

	Player* m_player = nullptr;
	Vector3 m_toCameraPos;
	Vector3 m_cameraSpeed;
	Quaternion m_toCameraRot;
	SpringCamera m_springCamera;
	float m_t = 0.1f;
};

