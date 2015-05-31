#include "UICampaignMapWindow.h"
#include "client/ui/nodes/UINodeMapSelector.h"
#include "client/ui/nodes/UINodeButton.h"
#include "common/campaign/CampaignManager.h"
#include "client/ui/windows/campaignmapwindow/ResetCampaignListener.h"

UICampaignMapWindow::UICampaignMapWindow (IFrontend *frontend, CampaignManager &campaignManager) :
	UIMapSelectorWindow(new UINodeMapSelector(frontend, campaignManager), tr("Maps"), UI_WINDOW_CAMPAIGN_MAPS, frontend, WINDOW_FLAG_FULLSCREEN | WINDOW_FLAG_MAIN)
{
#if 0
	UINodeButton *resetButton = new UINodeButton(frontend);
	resetButton->setImage("icon-reset");
	resetButton->putUnderRight(_mapSelector);
	resetButton->addListener(UINodeListenerPtr(new ResetCampaignListener(_mapSelector, campaignManager)));
	add(resetButton);
#endif
}