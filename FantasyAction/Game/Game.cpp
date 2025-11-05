#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "StageNo1.h"
#include "GameScene.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_stageNo1);
}

bool Game::Start()
{
	m_stageNo1=NewGO<StageNo1>(0, "stageNo1");

	return true;
}

void Game::Update()
{
	ReStart();

	m_modelRender.Update();
}

void Game::ReStart()
{
	if (g_pad[0]->IsTrigger(enButtonSelect)) {
		DeleteGO(m_stageNo1);
		m_stageNo1 = NewGO<StageNo1>(0, "stageNo1");
	}
}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
}