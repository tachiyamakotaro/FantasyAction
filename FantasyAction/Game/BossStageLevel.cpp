#include "stdafx.h"
#include "BossStageLevel.h"

BossStageLevel::BossStageLevel()
{

}

BossStageLevel::~BossStageLevel()
{

}

bool BossStageLevel::Start()
{
	m_modelRender.Init("Assets/modelData/bossStage.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_staticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void BossStageLevel::Update()
{

}

void BossStageLevel::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}