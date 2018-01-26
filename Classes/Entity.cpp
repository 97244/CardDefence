#include "Entity.h"

Entity::Entity() {
	m_sprite = NULL;
	m_sName = "";
	m_iHP = 1;
	m_iDefense = 1;
	m_isDead = false;
	m_iSpeed = 1;
	m_iLevel = 1;
}

Entity::~Entity() {
}

void Entity::bindSprite(Sprite* sprite) {
	if (this->m_sprite != NULL) {
		m_sprite->removeFromParentAndCleanup(true);
	}

	this->m_sprite = sprite;
	this->addChild(m_sprite);

	Size size = m_sprite->getContentSize();
	this->setContentSize(size);

	onBindSprite();
}

Sprite* Entity::getSprite() {
	return this->m_sprite;
}

void Entity::hurtMe(int iHurtValue) {
	if (m_isDead) {
		return;
	}

	/* 最小伤害值为1 */
	if (iHurtValue <= getiDefense()) {
		iHurtValue = 1;
	}

	int iCurHP = getiHP();      /* 当前HP */
	int iAfterHP = iCurHP - iHurtValue; /* 被攻击后的HP */

	onHurt(iHurtValue);

	if (iAfterHP > 0) {
		setiHP(iAfterHP);
	}
	else {
		m_isDead = true;
		/* 死亡 */
		onDead();
	}

}

bool Entity::isDead() {
	return this->m_isDead;
}

void Entity::onDead() {
}

void Entity::onBindSprite() {
}

void Entity::onHurt(int iHurtValue) {
}
