//Search:
	if (!rkNetStream.LoadInsultList(szInsultList))
	{
		Tracenf("CPythonApplication - CPythonNetworkStream::LoadInsultList(%s)", szInsultList);				
	}


//Add below:
	LocaleStringManager& rkLocaleString = LocaleStringManager::Instance();
	char szLocaleStringList[256];
	snprintf(szLocaleStringList, sizeof(szLocaleStringList), "%s/locale_string.txt", localePath);

	if (!rkLocaleString.RegisterLocaleStringTable(szLocaleStringList))
	{
		TraceError("LoadLocaleData - RegisterLocaleStringTable(%s) Error", szLocaleStringList);
		return false;
	}