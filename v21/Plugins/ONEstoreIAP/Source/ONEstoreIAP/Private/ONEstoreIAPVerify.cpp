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


bool UONEstoreIAPVerify::Verify( const FString publicKey, const FONEstorePurchaseData data )
{
#if PLATFORM_ANDROID
	say("d. check in");	
	 
	PurchaseDataCore core( TCHAR_TO_UTF8( *(data.OriginalJson)),
						   TCHAR_TO_UTF8( *(data.Signature)),
						   TCHAR_TO_UTF8( *(data.BillingKey)) );
	return NativeIapHelper->verifyPurchaseData( &core, TCHAR_TO_UTF8(*publicKey) );
#endif

	return false;
}