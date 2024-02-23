/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPGetConnectionState.h"
#include "ONEstoreIAP.h"

UONEstoreIAPGetConnectionState::UONEstoreIAPGetConnectionState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


EONEstoreConnectionState UONEstoreIAPGetConnectionState::GetConnectionState()
{	
#if PLATFORM_ANDROID
	say("d. check in");
	return (EONEstoreConnectionState)NativeIapHelper->getConnectionState();
#endif
	return EONEstoreConnectionState::DISCONNECTED;
}