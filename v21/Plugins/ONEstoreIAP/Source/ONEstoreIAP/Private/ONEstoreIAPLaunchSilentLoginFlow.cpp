/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPLaunchSilentLoginFlow.h"
#include "ONEstoreIAP.h"

UONEstoreIAPLaunchSilentLoginFlow::UONEstoreIAPLaunchSilentLoginFlow(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}



void UONEstoreIAPLaunchSilentLoginFlow::LaunchSilentLoginFlow()
{
#if PLATFORM_ANDROID
	say("d. check in");
	NativeIapHelper->launchSilentLoginFlow();
#endif
}


