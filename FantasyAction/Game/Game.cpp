#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "StageNo1.h"
#include "GameScene.h"
#include "BossStage.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_stageNo1);
}

bool Game::Start()
{
	//m_stageNo1=NewGO<StageNo1>(0, "stageNo1");
	m_bossStage = NewGO<BossStage>(0, "bossStage");

	return true;
}

void Game::Update()
{
	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
}