//Search:
			Set(HEADER_GC_DRAGON_SOUL_REFINE,		CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

			
//Add below:
			Set(HEADER_GC_LOCALE_CHAT, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCLocaleChat), DYNAMIC_SIZE_PACKET));