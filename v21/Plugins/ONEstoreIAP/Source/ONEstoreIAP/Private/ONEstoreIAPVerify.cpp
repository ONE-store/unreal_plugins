/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPVerify.h"
#include "ONEstoreIAP.h"

UONEstoreIAPVerify::UONEstoreIAPVerify(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


bool UONEstoreIAPVerify::Verify(const FString publicKey, const FONEstorePurchaseData data )
{
#if PLATFORM_ANDROID	
	return NativeIapHelper->verifyPurchaseData(
		TCHAR_TO_UTF8(*publicKey), UNREAL_TO_ONESTORE_PURCHASEDATA(data).get());
#else
	return false;
#endif
}