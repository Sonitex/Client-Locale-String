//Include the following header file:
#include "buffer_manager.h"

//Search:
    const char *locale_find(const char *string);

	
//Add below:
    void FindFormatSpecifiers(const char* c_szFormat, va_list& arg, WORD* iSize, TEMP_BUFFER* buf);