#include "BulletBase.h"

BulletBase::BulletBase()
{
	m_isUsed = false;
	m_aim = NULL;
	m_iSpeed = SPEED_DEFAULT;
	m_iAtkValue = 1;
}
BulletBase::~BulletBase()
{

}

void BulletBase::setUsed(bool isUsed) {
	this->m_isUsed = isUsed;
	setVisible(isUsed);
}
bool BulletBase::isUsed() {
	return this->m_isUsed;
}

void BulletBase::lockAim(Entity * entity) {
	if (entity != NULL) {
		this->m_aim = entity;
		onLockAim(entity);
	}
}

Entity*BulletBase::getAim() {
	return this->m_aim;
}

bool BulletBase::isArrive() {
	return this->m_isArrive;
}