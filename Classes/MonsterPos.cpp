#include "MonsterPos.h"
#include "EnumPosType.h"

MonsterPos::MonsterPos()
{
	m_pos = Point(0, 0);
	m_isDebug = false;
}
MonsterPos::~MonsterPos()
{

}

MonsterPos*MonsterPos::create(Point pos)
{
	MonsterPos *tPos = new MonsterPos();
	if (tPos && tPos->init(pos))
	{
		tPos->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(tPos);
	}
	return tPos;
}

MonsterPos*MonsterPos::create(Point pos, bool isDebug)
{
	MonsterPos *tPos = new MonsterPos();
	if (tPos && tPos->init(pos, isDebug))
	{
		tPos->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(tPos);
	}
	return tPos;
}

bool MonsterPos::init(Point pos)
{
	bool bRet = false;
	do 
	{
		setPos(pos);
		bRet = true;
	} while (0);

	return bRet;
}

bool MonsterPos::init(Point pos, bool isDebug)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!init(pos));
		m_isDebug = isDebug;
		bRet = true;
	} while (0);
	return bRet;
}

void MonsterPos::draw(Renderer *renderer, const kmMat4 &transform, uint32_t flags) {
	if (m_isDebug) {
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(MonsterPos::onDraw, this, transform, flags);
		renderer->addCommand(&_customCommand);
	}
}

void MonsterPos::onDraw(const kmMat4 &transform, uint32_t flags)
{
	/* »æÖÆ²âÊÔ·½¿ò */

	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);

	glLineWidth(4.0f);	// ÉèÖÃ»­±Ê´ÖÏ¸

						/* »æÖÆÔ² */
	DrawPrimitives::drawCircle(m_pos, MONSTER_RADIUS, 360, 20, false);

	glLineWidth(1);	// »Ö¸´»­±Ê´ÖÏ¸

	kmGLPopMatrix();// ½áÊø»æÖÆ
}

bool MonsterPos::isClickMe(Point pos) {
	Point srcPos = Point(m_pos.x - MONSTER_RADIUS, m_pos.y + MONSTER_RADIUS);
	Point destPos = Point(m_pos.x + MONSTER_RADIUS, m_pos.y - MONSTER_RADIUS);

	if (pos.x >= srcPos.x && pos.x <= destPos.x && pos.y <= srcPos.y && pos.y >= destPos.y) {
		return true;
	}

	return false;
}
