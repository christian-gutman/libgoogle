#ifndef GOOGLE_REQUEST_H
#define GOOGLE_REQUEST_H


#include "google.h"

#ifdef __cplusplus
extern "C"
{
#endif

    BOOL WGoogleGeoPos(
        HINTERNET hConnect,
        const char *wStreet,
        const char *wStreetNumber,
        const char *wCity,
        const char *wCountry,
        const char *wApiKey,
        char **ppOutResponseBuffer,
        DWORD *pStatusCode);

#ifdef __cplusplus
}
#endif

#endif // GOOGLE_REQUEST_H