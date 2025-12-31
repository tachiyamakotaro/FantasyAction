#include "stdafx.h"
#include "GameScene.h"
#include "StageNo1.h"
#include <codecvt>
#include <locale>
#include "StageCount.h"
#include "BossStage.h"
#include "Game.h"
#include "SoundManager.h"

namespace
{
	float IMAGE_HEIGHT = 1920.0f;
	float IMAGE_WIDTH = 1080.0f;

	Vector2 IMAGE = { 1920.0f, 1080.0f };

	std::string filePath = "Assets/sprite/";
	std::string fileExtention = ".DDS";



	struct SceanInfo
	{
		std::string fileName;
		
		std::string sceanText;
		
		const std::string GetFulPath() const
		{
			return filePath + fileName + fileExtention;
		}
	};

	SceanInfo sceanInfo[GameScene_num] = {
		{"Title1"/*,u8"スタートボタンでゲームスタート"*/},
		{"GoalPedestal", u8"ステージクリア！\nスタートボタンで次のステージ"},
		{"gameOver", u8"ゲームオーバー\nスタートボタンでリトライ"},
		{"GameClear"/*, u8"ゲームクリア！\nスタートボタンでタイトルへ"*/},
	};
}

bool GameScene::Start()
{
	m_stageCount = FindGO<StageCount>("stageCount");
	return true;
}

void GameScene::Update()
{
	m_sceneSprite.Update();
}

void GameScene::SetText(int scenenum)
{
	std::string str = sceanInfo[scenenum].sceanText;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wstr = converter.from_bytes(str);
	const wchar_t* text = wstr.c_str();
	m_sceneFont.SetText(text);
	m_sceneFont.SetPosition(0.0f, 0.0f, -10.0f);
	m_sceneFont.SetColor(g_vec4White);
}

void GameScene::SetSprite(int spritenum)
{
	std::string filePath = sceanInfo[spritenum].GetFulPath();
	m_sceneSprite.Init(filePath.c_str(), IMAGE.x, IMAGE.y);
}

void GameScene::BlinkFont()
{

}

//void GameScene::InGameTransition()
//{
//	//ゲームシーンに遷移する。
//	if (m_stageCount->GetStageCount() == 0)
//	{
//		m_stageNo1 = NewGO<StageNo1>(0, "stageNo1");
//	}
//	if (m_stageCount->GetStageCount() == 1)
//	{
//		m_bossStage = NewGO<BossStage>(0, "bossStage");
//	}
//}

void GameScene::Render(RenderContext& rc)
{
	m_sceneSprite.Draw(rc);
	m_sceneFont.Draw(rc);
}

const bool GameScene::IsStartTrigger() const
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		return true;
	}
	return false;
}

/// <summary>
/// ここからタイトルの設定
/// </summary>

Title::~Title()
{
	DeleteGO(m_titleBGM);
	//DeleteGO(m_buttonSe);
}

bool Title::Start()
{
	int scene = TitleScene;
	SetSprite(scene);

	SetText(scene);

	m_stageCount = FindGO<StageCount>("stageCount");

	m_stageClearCount = m_stageCount->GetStageCount();

	SoundManager* sound = FindGO<SoundManager>("soundManager");
	m_titleBGM = sound->PlayingSound(Sound::enSound_Title);

	return true;
}

void Title::Update()
{
	GameScene::Update();
	m_stageClearCount = m_stageCount->GetStageCount();
	Transition();
}

void Title::Transition()
{

	if (GameScene::IsStartTrigger())
	{
		InGameTransition();
		SoundManager* sound = FindGO<SoundManager>("soundManager");
		m_buttonSe = sound->PlayingSound(Sound::enSound_Button, false);

		DeleteGO(this);
	}
}

void Title::InGameTransition()
{
	//ゲームシーンに遷移する。
	m_game = NewGO<Game>(0, "game");
}


/// <summary>
/// ここからステージクリアの設定
/// </summary>

StageClear::~StageClear()
{
	DeleteGO(m_stageClearBGM);
}

bool StageClear::Start()
{
	int scene = StageClearScene;
	SetSprite(scene);

	SetText(scene);

	m_stageCount = FindGO<StageCount>("stageCount");

	m_stageClearCount = m_stageCount->GetStageCount();

	SoundManager* sound = FindGO<SoundManager>("soundManager");
	m_stageClearBGM = sound->PlayingSound(Sound::enSound_StageClearBGM);

	return true;
}

void StageClear::Update()
{
	GameScene::Update();
	m_stageClearCount = m_stageCount->GetStageCount();
	Transition();
}

void StageClear::Transition()
{

	if (GameScene::IsStartTrigger())
	{
		InGameTransition();
		SoundManager* sound = FindGO<SoundManager>("soundManager");
		m_buttonSe = sound->PlayingSound(Sound::enSound_Button, false);


		DeleteGO(this);
	}
}

void StageClear::InGameTransition()
{
	//ゲームシーンに遷移する。
	m_bossStage = NewGO<BossStage>(0, "bossStage");
}

/// <summary>
/// ここからゲームオーバーの設定
/// </summary>

GameOver::~GameOver()
{
	DeleteGO(m_gameOverBGM);
}

bool GameOver::Start()
{
	int scene = GameOverScene;
	SetSprite(scene);
	SetText(scene);

	m_stageCount = FindGO<StageCount>("stageCount");

	m_stageClearCount = m_stageCount->GetStageCount();

	SoundManager* sound = FindGO<SoundManager>("soundManager");
	m_gameOverBGM = sound->PlayingSound(Sound::enSound_GameOverBGM);
	return true;
}

void GameOver::Update()
{
	GameScene::Update();
	m_stageClearCount = m_stageCount->GetStageCount();
	Transition();
}

void GameOver::Transition()
{
	if (GameScene::IsStartTrigger())
	{
		InGameTransition();
		SoundManager* sound = FindGO<SoundManager>("soundManager");
		m_buttonSe = sound->PlayingSound(Sound::enSound_Button, false);

		DeleteGO(this);
	}
}

void GameOver::InGameTransition()
{
	if (m_stageClearCount == 0)
	{
		m_stageNo1 = NewGO<StageNo1>(0, "stageNo1");
	}
	if (m_stageClearCount >= 1)
	{
		m_bossStage = NewGO<BossStage>(0, "bossStage");
	}
}


/// <summary>
/// ここからゲームクリアの設定
/// </summary>

GameClear::~GameClear()
{
	DeleteGO(m_gameClearBGM);
}

bool GameClear::Start()
{
	int scene = GameClearScene;
	SetSprite(scene);
	//SetText(scene);
	m_stageCount = FindGO<StageCount>("stageCount");
	m_stageClearCount = m_stageCount->GetStageCount();

	SoundManager* sound = FindGO<SoundManager>("soundManager");
	m_gameClearBGM = sound->PlayingSound(Sound::enSound_GameClearBGM);
	return true;
}

void GameClear::Update()
{
	GameScene::Update();
	m_stageClearCount = m_stageCount->GetStageCount();
	Transition();
}

void GameClear::Transition()
{
	if (GameScene::IsStartTrigger())
	{
		TitleTransition();
		SoundManager* sound = FindGO<SoundManager>("soundManager");
		m_buttonSe = sound->PlayingSound(Sound::enSound_Button, false);

		DeleteGO(this);
	}
}

void GameClear::TitleTransition()
{
	//タイトルシーンに遷移する。
	m_title = NewGO<Title>(0, "title");
	m_stageClearCount = 0;
}
