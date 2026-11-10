#ifndef GOOGLE_H
#define GOOGLE_H


#include "core.h"
#include "core_io.h"
#include "core_encoding.h"
#include "core_string.h"
#include "core_crypto.h"
#include "core_html.h"
#include "core_rest.h"

#ifdef __cplusplus
extern "C"
{
#endif

    static __forceinline BOOL write_log(const wchar_t *msg)
    {
        wchar_t wPathBuffer[MAX_PATH] = {0};
        GetPathInLibraryFolder(wPathBuffer, MAX_PATH, L"google_request.log");
        return WriteTextLogWithDate(wPathBuffer, msg);
    }
 

#ifdef __cplusplus
}
#endif

#endif // GOOGLE_H