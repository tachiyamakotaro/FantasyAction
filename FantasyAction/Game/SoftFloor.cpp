#include "stdafx.h"
#include "SoftFloor.h"

SoftFloor::SoftFloor()
{
}

SoftFloor::~SoftFloor()
{
}

bool SoftFloor::Start()
{
	m_modelRender.Init("Assets/modelData/softFloor.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void SoftFloor::Update()
{

}

void SoftFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
