/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPLaunchManageSubscriptionHome.h"
#include "ONEstoreIAP.h"

UONEstoreIAPLaunchManageSubscriptionHome::UONEstoreIAPLaunchManageSubscriptionHome(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


void UONEstoreIAPLaunchManageSubscriptionHome::LaunchManageSubscriptionHome()
{	
#if PLATFORM_ANDROID	
	NativeIapHelper->launchManageSubscription();
#endif
}

