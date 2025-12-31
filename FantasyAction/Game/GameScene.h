#pragma once

enum
{
	TitleScene,
	StageClearScene,
	GameOverScene,
	GameClearScene,
	GameScene_num
};

class StageNo1;
class BossStage;
class StageCount;
class Game;

class GameScene:public IGameObject
{
public:
	bool Start();
	void Update();
	virtual void SetText(int scenenum);
	void SetSprite(int spritenum);
	void BlinkFont();
	void InGameTransition();
	void Render(RenderContext& rc);

	const bool IsStartTrigger()const;

	void SetFontColor(const Vector4& color)
	{
		m_sceneFont.SetColor(color);
	}

private:
	SpriteRender m_sceneSprite;
	FontRender   m_sceneFont;
	StageNo1* m_stageNo1 = nullptr;
	BossStage* m_bossStage = nullptr;
	StageCount* m_stageCount = nullptr;
};

class Title :public GameScene
{
public:
	~Title() override;
	bool Start();
	void Update();
	void Transition();
	void InGameTransition();

private:
	StageCount* m_stageCount = nullptr;
	StageNo1* m_stageNo1 = nullptr;
	BossStage* m_bossStage = nullptr;
	Game* m_game = nullptr;
	SoundSource* m_titleBGM;
	SoundSource* m_buttonSe;

	int m_stageClearCount = 0;
};

class StageClear :public GameScene
{
public:
	~StageClear() override;
	bool Start();
	void Update();
	void Transition();
	void InGameTransition();

private:
	StageCount* m_stageCount = nullptr;
	StageNo1* m_stageNo1 = nullptr;
	BossStage* m_bossStage = nullptr;
	SoundSource* m_stageClearBGM;
	SoundSource* m_buttonSe;

	int m_stageClearCount = 0;
};

class GameOver :public GameScene
{
public:
	~GameOver() override;
	bool Start();
	void Update();
	void Transition();
	void InGameTransition();

private:
	StageCount* m_stageCount = nullptr;
	StageNo1* m_stageNo1 = nullptr;
	BossStage* m_bossStage = nullptr;
	SoundSource* m_gameOverBGM;
	SoundSource* m_buttonSe;

	int m_stageClearCount = 0;
};

class GameClear :public GameScene
{
public:
	~GameClear() override;
	bool Start();
	void Update();
	void Transition();
	void TitleTransition();

private:
	Title* m_title = nullptr;
	StageCount* m_stageCount = nullptr;
	SoundSource* m_gameClearBGM;
	SoundSource* m_buttonSe;

	int m_stageClearCount = 0;
};

