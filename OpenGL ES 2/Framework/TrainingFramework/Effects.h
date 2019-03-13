#pragma once
#include "Pass.h"
class Effects
{
public:
	int m_effectPassCount;
	int m_effectID;
	Pass* m_effectPass;
	Effects();
	~Effects();
};

