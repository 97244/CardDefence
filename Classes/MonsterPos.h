#pragma once
#include "PosBase.h"
#define MONSTER_RADIUS 10
class Monster;
class MonsterPos : public PosBase
{
public:
	MonsterPos();
	~MonsterPos();


	static MonsterPos*create(Point pos);
	static MonsterPos*create(Point pos, bool isDebug);
	bool init(Point pos);
	bool init(Point pos, bool isDebug);

	virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;


	/* 判断坐标是否进入范围 */
	virtual bool isClickMe(Point pos) override;

private:
	void onDraw(const Mat4& transform, uint32_t flags);
	CustomCommand _customCommand;
	Monster *m_monster;
};