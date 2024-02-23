/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPIsReady.h"
#include "ONEstoreIAP.h"

UONEstoreIAPIsReady::UONEstoreIAPIsReady(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


bool UONEstoreIAPIsReady::IsReady()
{
#if PLATFORM_ANDROID
	say("d. check in");
	return NativeIapHelper->isReady();
#endif
	return false;
}