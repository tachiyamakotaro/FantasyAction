#include "stdafx.h"
#include "StageNo1Level.h"

StageNo1Level::StageNo1Level()
{

}

StageNo1Level::~StageNo1Level()
{

}

bool StageNo1Level::Start()
{
	m_modelRender.Init("Assets/modelData/stageNo1.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void StageNo1Level::Update()
{

}

void StageNo1Level::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
