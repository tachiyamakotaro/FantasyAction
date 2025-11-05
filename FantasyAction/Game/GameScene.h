#pragma once

enum
{
	ClearScene,
	GameOverScene,
	GameScene_num
};

class StageNo1;

class GameScene:public IGameObject
{
public:
	void Update();
	virtual void SetText(int scenenum);
	void SetSprite(int spritenum);
	void BlinkFont();
	void Render(RenderContext& rc);

private:
	SpriteRender m_sceneSprite;
	FontRender   m_sceneFont;
};

class GameClear :public GameScene
{
public:
	bool Start();
	void Update();
	void Transition();
	void InGameTransition();

private:
	StageNo1* m_stageNo1 = nullptr;
};

class GameOver :public GameScene
{
public:
	bool Start();
	void Update();
	void Transition();
	void InGameTransition();

private:
	StageNo1* m_stageNo1 = nullptr;
};

