//Search:
void CHARACTER::ChatPacket(BYTE type, const char * format, ...)
{
	[...]
}


//Add below:
void CHARACTER::LocaleChatPacket(BYTE type, DWORD dwIndex, const char* c_szFormat, ...)
{
	LPDESC d = GetDesc();

	if (!d || !c_szFormat)
		return;

	bool isNotice = false;
	if (c_szFormat == "%s")
	{
		char chatbuf[CHAT_MAX_LEN + 1];
		va_list args;

		va_start(args, c_szFormat);
		vsnprintf(chatbuf, sizeof(chatbuf), c_szFormat, args);
		va_end(args);

		strlcpy(chatbuf, c_szFormat, sizeof(chatbuf));
		isNotice = true;
	}

	TEMP_BUFFER buf;

	TPacketGCLocaleChat packet;
	packet.header = HEADER_GC_LOCALE_CHAT;
	packet.size = sizeof(TPacketGCLocaleChat);
	packet.type = type;
	packet.format = dwIndex;

	if (!isNotice)
	{
		va_list args;

		va_start(args, c_szFormat);
		FindFormatSpecifiers(c_szFormat, args, &packet.size, &buf);
		va_end(args);
	}

	d->Packet(&packet, sizeof(packet));

	if(buf.size())
		d->Packet(buf.read_peek(), buf.size());
}