/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPLaunchLoginFlowAsync.h"
#include "ONEstoreIAP.h"

UONEstoreIAPLaunchLoginFlowAsync::UONEstoreIAPLaunchLoginFlowAsync(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


UONEstoreIAPLaunchLoginFlowAsync* UONEstoreIAPLaunchLoginFlowAsync::LaunchLoginFlowAsync(const UObject* pWorld)
{
	UONEstoreIAPLaunchLoginFlowAsync* pthis = NewObject<UONEstoreIAPLaunchLoginFlowAsync>();
	pthis->m_pWorld = pWorld;

	return pthis;
}


void UONEstoreIAPLaunchLoginFlowAsync::Activate()
{
#if PLATFORM_ANDROID
	getListener()->m_OnIapResultListener.BindUObject(
		this, &UONEstoreIAPLaunchLoginFlowAsync::OnCompleted );	

	NativeIapHelper->launchLoginFlowAsync();
#endif 
}


void UONEstoreIAPLaunchLoginFlowAsync::OnCompleted(const int32& code, const FString& message)
{
#if PLATFORM_ANDROID	
	switch ((ResponseCode)code) {
	case ResponseCode::RESULT_OK:
		OnSuccess.Broadcast(code, message);	break;
	case ResponseCode::RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(code, message); break;
	case ResponseCode::RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(code, message); break;
	default:
		OnFailure.Broadcast(code, message); break;
	}
#endif
}
