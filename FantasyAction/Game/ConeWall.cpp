#include "stdafx.h"
#include "ConeWall.h"

ConeWall::ConeWall()
{

}

ConeWall::~ConeWall()
{

}

bool ConeWall::Start()
{
	m_modelRender.Init("Assets/modelData/coneWall.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	return true;
}

void ConeWall::Update()
{

}

void ConeWall::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
