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
	say("d. check in");
	
	PurchaseDataCore core( TCHAR_TO_UTF8(*(data.OriginalJson)),
						   TCHAR_TO_UTF8(*(data.Signature)),
						   TCHAR_TO_UTF8(*(data.BillingKey)) );
	NativeIapHelper->launchManageSubscription( &core );
#endif
}

