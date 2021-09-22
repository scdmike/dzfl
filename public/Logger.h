
#pragma once

#ifdef ANDROID
void InstallLogcatMessageHandler(const char *TAG);
#else
#define InstallLogcatMessageHandler(TAG)
#endif


