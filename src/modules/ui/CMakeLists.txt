set(ui_SRCS
	UI.cpp
	BitmapFont.cpp
	nodes/UINodeMapSelector.cpp
	nodes/UINodeCampaignSelector.cpp
	nodes/UINodeSlider.cpp
	nodes/UINodeSprite.cpp
	nodes/UINodeBackground.cpp
	nodes/UINodeButton.cpp
	nodes/UINodeBar.cpp
	nodes/UINodeGooglePlayButton.cpp
	nodes/UINodeLabel.cpp
	nodes/UINode.cpp
	nodes/UINodePaymentSelector.cpp
	nodes/UINodeCheckbox.cpp
	nodes/UINodeMapControl.cpp
	nodes/UINodeKey.cpp
	nodes/UINodeMapStringSelector.cpp
	nodes/UINodeSpinner.cpp
	nodes/UINodeTextInput.cpp
	nodes/UINodeMapFingerControl.cpp
	nodes/UINodeMapOnScreenCursorControl.cpp
	nodes/IUINodeMap.cpp
	nodes/UINodeServerSelector.cpp
	FontDefinition.cpp
	layouts/UIFillLayout.cpp
	layouts/UIHBoxLayout.cpp
	layouts/UIVBoxLayout.cpp
	windows/UIMapSelectorWindow.cpp
	windows/UICreateServerWindow.cpp
	windows/UICampaignMapWindow.cpp
	windows/UIMultiplayerWindow.cpp
	windows/UISettingsWindow.cpp
	windows/UIGooglePlayWindow.cpp
	windows/UIModeSelectionWindow.cpp
	windows/UICampaignWindow.cpp
	windows/IUIMapWindow.cpp
	windows/UIPopupWindow.cpp
	windows/UIWindow.cpp
	windows/UIPaymentWindow.cpp
	windows/UIMapOptionsWindow.cpp
	windows/UIGestureWindow.cpp
	windows/UIMapFinishedWindow.cpp
	windows/intro/Intro.cpp
)
add_library(ui ${ui_SRCS})
set_target_properties(ui PROPERTIES FOLDER ui)
target_link_libraries(ui libs texture sprite sound campaign)
