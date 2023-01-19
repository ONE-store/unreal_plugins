/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPLaunchManageSubscription.h"
#include "ONEstoreIAP.h"

UONEstoreIAPLaunchManageSubscription::UONEstoreIAPLaunchManageSubscription(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


void UONEstoreIAPLaunchManageSubscription::LaunchManageSubscription(const FONEstorePurchaseData data)
{	
#if PLATFORM_ANDROID	
	NativeIapHelper->launchManageSubscription( UNREAL_TO_ONESTORE_PURCHASEDATA( data ).get() );
#endif
}

