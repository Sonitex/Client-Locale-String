//Include the following header files:
#include "buffer_manager.h"
#include "../../common/length.h"

//Add:
#define STRING_SIZE 32 + 1
enum Formats
{
	FORMAT_TYPE_INT,
	FORMAT_TYPE_UNSIGNED_INT,
	FORMAT_TYPE_SHORT_INT,
	FORMAT_TYPE_SIGNED_CHAR,
	FORMAT_TYPE_LONG,
	FORMAT_TYPE_UNSIGNED_LONG,
	FORMAT_TYPE_LONG_INT,
	FORMAT_TYPE_LONG_LONG_INT,
	FORMAT_TYPE_FLOAT,
	FORMAT_TYPE_STRING,

	FORMAT_TYPE_MAX_NUM

};

typedef struct SFormat
{
	int				iType;
	char			szName[4 + 1];
	UINT			iSize;
} TFormat;

TFormat FormatTable[FORMAT_TYPE_MAX_NUM] =
{
	{FORMAT_TYPE_INT,			"d",		sizeof(int) },
	{FORMAT_TYPE_UNSIGNED_INT,		"u",		sizeof(unsigned int) },
	{FORMAT_TYPE_SHORT_INT,			"h",		sizeof(short int) },
	{FORMAT_TYPE_SIGNED_CHAR,		"hh",		sizeof(signed char) },

	{FORMAT_TYPE_LONG,			"l",		sizeof(long) },
	{FORMAT_TYPE_UNSIGNED_LONG,		"lu",		sizeof(unsigned long) },
	{FORMAT_TYPE_LONG_INT,			"ld",		sizeof(long int) },
	{FORMAT_TYPE_LONG_LONG_INT,		"lld",		sizeof(long long int) },

	{FORMAT_TYPE_FLOAT,			"f",		STRING_SIZE },

	{FORMAT_TYPE_STRING,			"s",		STRING_SIZE },
};

bool IsFormatSpecifier(const char* specifier)
{
	for (const auto& format : FormatTable)
	{
		int result = strcmp(format.szName, specifier);
		if (result == 0)
			return true;
	}

	return false;
}

int	GetFormatSpecifierType(const char* specifier)
{
	for (const auto& format : FormatTable)
	{
		int result = strcmp(format.szName, specifier);
		if (result == 0)
			return format.iType;
	}

	return -1;
}

UINT GetFormatSpecifierSize(int type)
{
	return FormatTable[type].iSize;
}

int LocateFormatSpecifier(const char* c_szFormat, size_t iSize)
{
	std::string specifier = "";
	std::string specifierCopy = "";
	int specifierType = 0;
	for (int iPos = 0; iPos < iSize; iPos++)
	{
		if (!isalpha(c_szFormat[iPos]))
			continue;

		if (!isdigit(c_szFormat[iPos]))
		{
			specifierCopy += c_szFormat[iPos];

			if (IsFormatSpecifier(specifierCopy.c_str()))
			{
				specifier = specifierCopy;
				specifierType = GetFormatSpecifierType(specifier.c_str());
			}
		}
	}

	return specifierType;
}

void FindFormatSpecifiers(const char* c_szFormat, va_list& arg, WORD* iSize, TEMP_BUFFER* buf)
{
	size_t formatSize = strlen(c_szFormat);

	for (int iPos = 0; iPos < formatSize; iPos++)
	{
		if (c_szFormat[iPos] == '%' &&
			c_szFormat[iPos + 1] != '%' &&
			c_szFormat[iPos + 1] != ' ')
		{
			char stringBuffer[CHAT_MAX_LEN + 1];
			memcpy(stringBuffer, c_szFormat + iPos, formatSize);

			int iType = LocateFormatSpecifier(stringBuffer, formatSize);
			if (iType != -1)
			{
				iSize += GetFormatSpecifierSize(iType);

				switch (iType)
				{
					case FORMAT_TYPE_INT:
					{
						int iVal = va_arg(arg, int);
						buf->write(&iVal, sizeof(iVal));
					} break;

					case FORMAT_TYPE_UNSIGNED_INT:
					{
						unsigned int iVal = va_arg(arg, unsigned int);
						buf->write(&iVal, sizeof(iVal));
					} break;

					case FORMAT_TYPE_SHORT_INT:
					{
						short sVal = va_arg(arg, short);
						buf->write(&sVal, sizeof(sVal));
					} break;

					case FORMAT_TYPE_SIGNED_CHAR:
					{
						signed char cVal = va_arg(arg, signed char);
						buf->write(&cVal, sizeof(cVal));
					} break;

					case FORMAT_TYPE_LONG:
					{
						long lVal = va_arg(arg, long);
						buf->write(&lVal, sizeof(lVal));
					} break;

					case FORMAT_TYPE_UNSIGNED_LONG:
					{
						unsigned long lVal = va_arg(arg, unsigned long);
						buf->write(&lVal, sizeof(lVal));
					} break;

					case FORMAT_TYPE_LONG_INT:
					{
						long lVal = va_arg(arg, long int);
						buf->write(&lVal, sizeof(lVal));
					} break;

					case FORMAT_TYPE_LONG_LONG_INT:
					{
						long long llVal = va_arg(arg, long);
						buf->write(&llVal, sizeof(llVal));
					} break;

					case FORMAT_TYPE_FLOAT:
					{
						double fVal = va_arg(arg, double);

						char cVal[STRING_SIZE];
						snprintf(cVal, sizeof(cVal), "%.2f", fVal);

						buf->write(&cVal, sizeof(cVal));
					} break;

					case FORMAT_TYPE_STRING:
					{
						const char* strVal = va_arg(arg, const char*);
						char cVal[STRING_SIZE];
						strncpy(cVal, strVal, sizeof(cVal));
						buf->write(&cVal, sizeof(cVal));
					} break;
				}
			}
		}
	}
}
