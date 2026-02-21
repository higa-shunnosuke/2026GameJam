#include "Rock.h"

#include "../../System/ResourceManager.h"
#include <DxLib.h>

Rock::Rock()
	:m_rockImage()
{

}

Rock::~Rock()
{

}

void Rock::Initialize()
{
	// ‰æ‘œ“Ç‚İ‚İ
	ResourceManager& rm = ResourceManager::GetInstance();
	m_rockImage = rm.GetImageResource("Assets/Sprites/Rock/Rock.PNG")[0];

	// zlayer‚Ìİ’è
	m_zLayer = 10;

	// “–‚½‚è”»’è‚Ìİ’è
	m_collision.m_type = e_ObjectType::rock;
	m_collision.m_radius = 40;
}

void Rock::Draw() const
{
	DrawRotaGraphF(m_location.x, m_location.y, 0.1f, 0.0f, m_rockImage, TRUE);

#if _DEBUG
	// “–‚½‚è”»’è‚ğ‰Â‹‰»
	DrawCircle(m_location.x, m_location.y, m_collision.m_radius, GetColor(255, 0, 0), FALSE);
#endif
}