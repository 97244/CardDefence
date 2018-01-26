#pragma once
#include "PosBase.h"
#include "EnumPosType.h"
#include "MonsterPos.h"
class PosLoadUtil :public Node {
public:
	static PosLoadUtil*getInstance();
	virtual bool init();

	Vector<PosBase*>loadPosWithFile(
		const char *sFilePath,
		EnumPosType enPosType,
		Node* container,
		int iLevel,
		bool isDebug);
private:
	static PosLoadUtil* m_posLoadUtil;
};