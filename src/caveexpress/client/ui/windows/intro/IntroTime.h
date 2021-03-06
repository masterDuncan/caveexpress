#pragma once

#include "common/Compiler.h"
#include "ui/windows/intro/Intro.h"

class IntroTime: public Intro {
public:
	IntroTime (IFrontend* frontend);
protected:
	void addIntroNodes(UINode* parent) override;
};
