#pragma once

#include "network/IProtocolHandler.h"
#include "network/messages/TextMessage.h"

class TextMessageHandler: public IClientProtocolHandler {
private:
	IUINodeMap *_mapNode;
public:
	TextMessageHandler (IUINodeMap* mapNode) :
			_mapNode(mapNode)
	{
	}

	void execute (const IProtocolMessage& message) override
	{
		const TextMessage *msg = static_cast<const TextMessage*>(&message);
		_mapNode->displayText(msg->getMessage());
	}
};
