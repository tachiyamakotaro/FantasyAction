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
	/*m_modelRender.Init("Assets/modelData/bossStage.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_staticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());*/

	return true;
}

void BossStageLevel::Update()
{

}

void BossStageLevel::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
}


/*
 *	èÈÇÃï«ÇÃê›íË
 */
bool CastleWall::Start()
{
	m_modelRender.Init("Assets/modelData/tkm_file/jouheki.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_staticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void CastleWall::Update()
{
}

void CastleWall::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


/*
 *	èÈÇÃè∞ÇÃê›íË
 */
bool CastleFloor::Start()
{
	m_modelRender.Init("Assets/modelData/tkm_file/sironoyuka.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_staticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void CastleFloor::Update()
{
}

void CastleFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
