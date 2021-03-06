#pragma once

#include "common/Compiler.h"
#include "ui/windows/intro/Intro.h"

class IntroGame: public Intro {
public:
	IntroGame (IFrontend* frontend);
protected:
	void addIntroNodes(UINode* parent) override;
};
