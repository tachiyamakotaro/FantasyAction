#pragma once

enum
{
	StageClearScene,
	GameOverScene,
	GameScene_num
};

class StageNo1;
class BossStage;
class StageCount;

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

private:
	SpriteRender m_sceneSprite;
	FontRender   m_sceneFont;
	StageNo1* m_stageNo1 = nullptr;
	BossStage* m_bossStage = nullptr;
	StageCount* m_stageCount = nullptr;
};

class GameClear :public GameScene
{
public:
	bool Start();
	void Update();
	void Transition();
	void InGameTransition();

private:
	StageCount* m_stageCount = nullptr;
	StageNo1* m_stageNo1 = nullptr;
	BossStage* m_bossStage = nullptr;

	int m_stageClearCount = 0;
};

class GameOver :public GameScene
{
public:
	bool Start();
	void Update();
	void Transition();
	void InGameTransition();

private:
	StageCount* m_stageCount = nullptr;
	StageNo1* m_stageNo1 = nullptr;
	BossStage* m_bossStage = nullptr;

	int m_stageClearCount = 0;
};

