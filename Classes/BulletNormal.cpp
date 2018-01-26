#include "BulletNormal.h"
#include "GlobalPath.h"
BulletNormal::BulletNormal()
{
	m_iSpeed = SPEED_DEFAULT;
}
BulletNormal::~BulletNormal()
{

}
BulletNormal*BulletNormal::create(Sprite* sprite) {
	BulletNormal*bulletNor = new BulletNormal();
	if (bulletNor && bulletNor->init(sprite)){
		bulletNor->autorelease();
	}
	else {
		CC_SAFE_DELETE(bulletNor);
	}

	return bulletNor;
}
bool BulletNormal::init(Sprite* sprite) {
	bindSprite(sprite);

	return true;
}

bool BulletNormal::init() {
	bool bRet = false;
	do 
	{
		auto sprite = Sprite::create(PATH_BULLET_NOR);
		CC_BREAK_IF(!sprite);
		CC_BREAK_IF(!init(sprite));
		bRet = true;
	} while (0);

	return bRet;
}

void BulletNormal::onLockAim(Entity *aim) {
	m_isArrive = false;
	Point aimWorldPos = aim->getParent()->convertToWorldSpace(aim->getPosition());
	Point dstPos = this->getParent()->convertToNodeSpace(aimWorldPos);

	auto moveTo = MoveTo::create(0.5f, dstPos);
	auto callFunc = CallFunc::create([&]() {
		moveEnd(); 
	});

	auto actions = Sequence::create(moveTo, callFunc, NULL);
	this->runAction(actions);
}

void BulletNormal::moveEnd()
{
	m_isArrive = true;
}