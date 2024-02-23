/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPLaunchUpdateOrInstallFlow.h"
#include "ONEstoreIAP.h"

UONEstoreIAPLaunchUpdateOrInstallFlow::UONEstoreIAPLaunchUpdateOrInstallFlow(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


UONEstoreIAPLaunchUpdateOrInstallFlow* UONEstoreIAPLaunchUpdateOrInstallFlow::LaunchUpdateOrInstallFlow(const UObject* pWorld)
{
	UONEstoreIAPLaunchUpdateOrInstallFlow* pthis = 
		NewObject<UONEstoreIAPLaunchUpdateOrInstallFlow>();
	pthis->m_pWorld = pWorld;
#if PLATFORM_ANDROID
	say("d. check in");
#endif
	return pthis;
}


void UONEstoreIAPLaunchUpdateOrInstallFlow::Activate()
{
#if PLATFORM_ANDROID
	say("d. check in");
	getListener()->m_OnIapResultListener.BindUObject(
		this, &UONEstoreIAPLaunchUpdateOrInstallFlow::OnCompleted);
	
	NativeIapHelper->launchUpdateOrInstallFlow();
#endif 
}


void UONEstoreIAPLaunchUpdateOrInstallFlow::OnCompleted(const int32& code, const FString& message)
{
#if PLATFORM_ANDROID
	say("d. check in");
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	say("d. result( %d, %s )", code, TCHAR_TO_UTF8(*message));
#endif

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