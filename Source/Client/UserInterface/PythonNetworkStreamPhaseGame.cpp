//Include the following header file:
#include "LocaleStringManager.h"


//Search:
			case HEADER_GC_CHAT:
				ret = RecvChatPacket();
				break;

				
//Add below:
			case HEADER_GC_LOCALE_CHAT:
				ret = RecvLocaleChatPacket();
				break;
				
				
				
//Search:
bool CPythonNetworkStream::RecvChatPacket()
{
	[...]
}


//Add below:
bool CPythonNetworkStream::RecvLocaleChatPacket()
{
	TPacketGCLocaleChat kChat;

	if (!Recv(sizeof(kChat), &kChat))
		return false;

	std::string localeString = "";
	bool bSuccess = LocaleStringManager::Instance().FillLocaleString(kChat.format, localeString);

	if (!bSuccess)
		return false;

	if(!localeString.empty())
		CPythonChat::Instance().AppendChat(kChat.type, localeString.c_str());

	return true;
}