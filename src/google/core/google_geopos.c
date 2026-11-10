#include "google_geopos.h"

BOOL WGoogleGeoPos(
    HINTERNET hConnect,
    const char *szStreet,
    const char *szStreetNumber,
    const char *szCity,
    const char *szCountry,
    const char *szApiKey,
    char **ppOutResponseBuffer,
    DWORD *pStatusCode)
{
    if (!hConnect || !ppOutResponseBuffer || !pStatusCode)
        return FALSE;

    if (!szStreet || szStreet[0] == '\0')
        return FALSE;
    if (!szStreetNumber || szStreetNumber[0] == '\0')
        return FALSE;
    if (!szCity || szCity[0] == '\0')
        return FALSE;
    if (!szCountry || szCountry[0] == '\0')
        return FALSE;
    if (!szApiKey || szApiKey[0] == '\0')
        return FALSE;

    //*pStatusCode = 0;
    //*ppOutResponseBuffer = NULL;
    BOOL bResult = FALSE;

    char *cCalle = StrTrimAllAlloc(szStreet);
    char *cNum = StrTrimAllAlloc(szStreetNumber);
    char *cCiudad = StrTrimAllAlloc(szCity);
    char *cPais = StrTrimAllAlloc(szCountry);
    char *cKey = StrTrimAllAlloc(szApiKey);
    //
    if (cCalle)
        StrTranChar(cCalle, ' ', '+');
    if (cNum)
        StrTranChar(cNum, ' ', '+');
    if (cCiudad)
        StrTranChar(cCiudad, ' ', '+');
    if (cPais)
        StrTranChar(cPais, ' ', '+');
    //
    int requiredSize = _scprintf("/maps/api/geocode/json?address=%s+%s,%s,%s&key=%s",
                                 cCalle ? cCalle : "", cNum ? cNum : "",
                                 cCiudad ? cCiudad : "", cPais ? cPais : "",
                                 cKey ? cKey : "");

    if (requiredSize > 0)
    {
        char *szUrl = (char *)malloc(requiredSize + 1);
        if (szUrl)
        {

            sprintf_s(szUrl, requiredSize + 1, "/maps/api/geocode/json?address=%s+%s,%s,%s&key=%s",
                      cCalle ? cCalle : "", cNum ? cNum : "",
                      cCiudad ? cCiudad : "", cPais ? cPais : "",
                      cKey ? cKey : "");

            bResult = WRestGet(hConnect, szUrl, NULL, ppOutResponseBuffer, pStatusCode);
            free(szUrl);
        }
    }

    free(cCalle);
    free(cNum);
    free(cCiudad);
    free(cPais);
    free(cKey);

    return bResult;
}
