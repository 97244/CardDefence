#include "TowerBorder.h"

TowerBorder::TowerBorder()
{
	m_iLevel = 1;
	m_hero = NULL;
	m_cancelBtn = NULL;
	m_deleteBtn = NULL;
	m_upgradeBtn = NULL;
	m_isOprBtnShow = false;
}
TowerBorder::~TowerBorder()
{

}
bool TowerBorder::init()
{
	return true;
}

void TowerBorder::upgrade()
{
	if (getSprite() != NULL)
	{
		getSprite()->stopAllActions();
	}

	std::string sFilePath = StringUtils::format("sprite/hero/border_%d.png", m_iLevel);
	Sprite *sprite = Sprite::create(sFilePath.c_str());
	bindSprite(sprite);

	m_iLevel++;

	if (m_iLevel == 2)
	{
		auto rotateBy = RotateBy::create(25.0f, 360, 360);
		auto repeat = RepeatForever::create(rotateBy);
		sFilePath = StringUtils::format("sprite/hero/magic_border_%d.png", m_iLevel);
		sprite = Sprite::create(sFilePath.c_str());
		sprite->setOpacity(80);
		sprite->runAction(repeat);
		this->addChild(sprite, 10);
	}
}

bool TowerBorder::isClickMe(Point pos)
{
	Size size = getSprite()->getContentSize();
	Point borderPos = getPosition();
	Point srcPos = Point(borderPos.x - size.width / 2, borderPos.y + size.height / 2);
	Point dstPos = Point(borderPos.x + size.width / 2, borderPos.y - size.height / 2);

	if (pos.x >=srcPos.x && pos.x<=dstPos.x && pos.y<=srcPos.y && pos.y>=dstPos.y)
	{
		return true;
	}

	return false;
}

void TowerBorder::bindHero(Hero *hero)
{
	this->m_hero = hero;
}

Hero*TowerBorder::getHero()
{
	return this->m_hero;
}

void TowerBorder::deleteHero()
{
	if (m_hero != NULL)
	{
		m_hero->removeFromParent();
	}
}

void TowerBorder::showTowerOprBtns()
{
	if (m_isOprBtnShow == true)
	{
		return;
	}

	if (m_cancelBtn == NULL)
	{
		auto heroOprBtn = Button::create();
		heroOprBtn->loadTextureNormal("button2.png");
		m_cancelBtn = (Button *)heroOprBtn->clone();
		m_deleteBtn = (Button *)heroOprBtn->clone();
		m_upgradeBtn = (Button*)heroOprBtn->clone();

		resetOprBtns();

		m_cancelBtn->setTitleText("cancel");
		m_deleteBtn->setTitleText("delete");
		m_upgradeBtn->setTitleText("upgrade");

		m_cancelBtn->addTouchEventListener(this,toucheventselector(TowerBorder::cancelClick));
		m_deleteBtn->addTouchEventListener(this, toucheventselector(TowerBorder::deleteClick));
		m_upgradeBtn->addTouchEventListener(this, toucheventselector(TowerBorder::upgradeClick));


		this->addChild(m_cancelBtn);
		this->addChild(m_deleteBtn);
		this->addChild(m_upgradeBtn);

		//this->getParent()->addChild(m_cancelBtn, 999);
		//this->getParent()->addChild(m_deleteBtn, 999);
		//this->getParent()->addChild(m_upgradeBtn, 999);
	}

	m_cancelBtn->setEnabled(true);
	m_deleteBtn->setEnabled(true);
	m_upgradeBtn->setEnabled(true);

	m_cancelBtn->runAction(EaseBounceOut::create(MoveBy::create(0.5f, Point(0, 100))));
	m_deleteBtn->runAction(EaseBounceOut::create(MoveBy::create(0.5f, Point(-100, 0))));
	m_upgradeBtn->runAction(EaseBounceOut::create(MoveBy::create(0.5f, Point(100, 0))));

	m_isOprBtnShow = true;
}

void TowerBorder::resetOprBtns()
{
	/* 让按钮恢复到中点的位置 */
	Size size = this->getContentSize();
	Point pos = Point(0, 0);
	m_cancelBtn->setPosition(pos);
	m_deleteBtn->setPosition(pos);
	m_upgradeBtn->setPosition(pos);
}

void TowerBorder::deleteOprBtns()
{
	if (m_cancelBtn != NULL)
	{
		m_cancelBtn->setEnabled(false);
	}

	if (m_deleteBtn != NULL)
	{
		m_deleteBtn->setEnabled(false);
	}
		
	if (m_upgradeBtn != NULL)
	{
		m_upgradeBtn->setEnabled(false);
	}
		
	resetOprBtns();
	m_isOprBtnShow = false;
}


void TowerBorder::cancelClick(Ref*pSender, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		deleteOprBtns();
	}
}

void TowerBorder::deleteClick(Ref*pSender, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		deleteHero();
		m_hero = NULL;
		deleteOprBtns();
	}
}

void TowerBorder::upgradeClick(Ref*pSender, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		m_hero->upgrade();
		deleteOprBtns();
	}
}