// Search:
	HEADER_GC_AUTH_SUCCESS_OPENID	= 154,
	
	
// Add below:
	HEADER_GC_LOCALE_CHAT			= 158,
	
	
//Add:
typedef struct packet_locale_chat
{
    BYTE		header;
    WORD		size;
    BYTE		type;
    DWORD		format;
} TPacketGCLocaleChat;