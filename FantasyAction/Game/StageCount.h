#pragma once
class StageCount:public IGameObject
{
public:
	StageCount() {};
	void AddStageCount();

	int GetStageCount()
	{
		return m_stageCount;
	}

	void SetStageCount(const int& stageCount)
	{
		m_stageCount = stageCount;
	}

private:
	~StageCount() {};
	bool Start();

private:
	int m_stageCount=0;
};

