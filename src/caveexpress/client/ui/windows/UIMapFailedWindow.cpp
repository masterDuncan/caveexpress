#include "UIMapFailedWindow.h"
#include "ui/UI.h"
#include "ui/nodes/UINodeBackButton.h"
#include "ui/nodes/UINodeButton.h"
#include "ui/layouts/UIHBoxLayout.h"
#include "caveexpress/client/ui/nodes/UINodeBackgroundScene.h"
#include "ui/nodes/UINodeContinuePlay.h"
#include "ui/windows/main/ReplayNodeListener.h"
#include <string>

UIMapFailedWindow::UIMapFailedWindow (IFrontend *frontend, CampaignManager& campaignManager) :
		UIWindow(UI_WINDOW_MAPFAILED, frontend), _campaignManager(campaignManager)
{
	setInactiveAfterPush();

	_background = new UINodeBackgroundScene(frontend);
	if (System.hasTouch() && !wantBackButton())
		_background->setOnActivate(CMD_UI_POP);
	add(_background);

	UINode *buttons = new UINode(frontend);
	buttons->setLayout(new UIHBoxLayout());
	buttons->setAlignment(NODE_ALIGN_CENTER | NODE_ALIGN_BOTTOM);

	_replayCampaign = new UINodeButton(frontend);
	_replayCampaign->setImage("icon-reload");
	_replayCampaign->addListener(UINodeListenerPtr(new ReplayNodeListener(_campaignManager)));
	buttons->add(_replayCampaign);

	add(buttons);
	if (!wantBackButton()) {
		return;
	}

	add(new UINodeBackButton(frontend, _background));
}

void UIMapFailedWindow::updateReason (bool isMultiplayer, const MapFailedReason& reason, const ThemeType& theme)
{
	_replayCampaign->setVisible(!isMultiplayer);
	_background->updateReason(reason, theme);
}
