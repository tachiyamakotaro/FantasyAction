#include "stdafx.h"
#include "GameScene.h"
#include "StageNo1.h"
#include <codecvt>
#include <locale>

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
		{"GoalPedestal", u8"ステージクリア！\nスタートボタンで次のステージ"},
		{"gameOver", u8"ゲームオーバー\nスタートボタンでリトライ"},
	};
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

void GameScene::Render(RenderContext& rc)
{
	m_sceneSprite.Draw(rc);
	m_sceneFont.Draw(rc);
}

/// <summary>
/// ここからゲームクリアの設定
/// </summary>
bool GameClear::Start()
{
	int scene = ClearScene;
	SetSprite(scene);

	SetText(scene);

	return true;
}

void GameClear::Update()
{
	GameScene::Update();
	Transition();
}

void GameClear::Transition()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		InGameTransition();

		DeleteGO(this);
	}
}

void GameClear::InGameTransition()
{
	//ゲームシーンに遷移する。
	m_stageNo1 = NewGO<StageNo1>(0,"stageNo1");
}

/// <summary>
/// ここからゲームオーバーの設定
/// </summary>
bool GameOver::Start()
{
	int scene = GameOverScene;
	SetSprite(scene);
	SetText(scene);
	return true;
}

void GameOver::Update()
{
	GameScene::Update();
	Transition();
}

void GameOver::Transition()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		InGameTransition();
		DeleteGO(this);
	}
}

void GameOver::InGameTransition()
{
	//ゲームシーンに遷移する。
	m_stageNo1 = NewGO<StageNo1>(0, "stageNo1");
}
