#pragma once
#include "cocos2d.h"
#include "EnumStrKey.h"
USING_NS_CC;
#include "CsvUtil.h"
class I18N :public Ref {

public:
	static I18N*getInstance();
	virtual bool init();

	const char*getcString(EnumStrKey enStrKey);
	const char*getcString(int iKey);
private:
	void loadStringsFromConf(const char*filePath);
	static I18N* m_I18N;
	std::map<int, std::string> m_StringMap;
};