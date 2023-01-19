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
	return (EONEstoreConnectionState)NativeIapHelper->getConnectionState();
#else
	return EONEstoreConnectionState::DISCONNECTED;
#endif
}