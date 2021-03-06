#pragma once

#include "common/EntityType.h"
#include "ui/nodes/UINodeSelector.h"
#include "common/ThemeType.h"
#include "sprites/Sprite.h"
#include "common/SpriteDefinition.h"

struct EntityTypeWrapper {
	const EntityType* type;
	SpritePtr sprite;
	EntityAngle angle;
};

class UINodeEntitySelector: public UINodeSelector<EntityTypeWrapper> {
private:
	const ThemeType* _theme;

	void addEntity (const EntityType& type, const ThemeType& theme);
public:
	UINodeEntitySelector (IFrontend *frontend, int cols, int rows);
	virtual ~UINodeEntitySelector ();

	void addEntities (const ThemeType& theme);

	inline const ThemeType& getTheme () const
	{
		return *_theme;
	}

	// UINode
	void update (uint32_t deltaTime) override;

	// UINodeSelector
	void renderSelectorEntry (int index, const EntityTypeWrapper& data, int x, int y, int colWidth, int rowHeight, float alpha) const override;
};
