#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "StageNo1.h"
#include "GameOver.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_stageNo1);
}

bool Game::Start()
{
	//m_modelRender.Init("Assets/modelData/unityChan.tkm");

	//m_player=NewGO<Player>(0, "player");
	//m_player=FindGO<Player>("player");

	//m_gameCamera=NewGO<GameCamera>(1, "gameCamera");

	m_stageNo1=NewGO<StageNo1>(0, "stageNo1");

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	
	return true;
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();
	//FallDeath();

	//HpZeroDeath();

	m_modelRender.Update();
}

void Game::FallDeath()
{
	
}

void Game::HpZeroDeath()
{
	
}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
}