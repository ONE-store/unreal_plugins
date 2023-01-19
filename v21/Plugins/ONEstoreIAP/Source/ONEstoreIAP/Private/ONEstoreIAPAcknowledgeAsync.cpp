/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPAcknowledgeAsync.h"
#include "ONEstoreIAP.h"


UONEstoreIAPAcknowledgeAsync::UONEstoreIAPAcknowledgeAsync(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


UONEstoreIAPAcknowledgeAsync* UONEstoreIAPAcknowledgeAsync::AcknowledgeAsync(
	const UObject* pWorld, const FONEstorePurchaseData& data)
{
	UONEstoreIAPAcknowledgeAsync* pthis = NewObject<UONEstoreIAPAcknowledgeAsync>();
	pthis->m_pWorld = pWorld;
	pthis->m_data = data;
	
#if PLATFORM_ANDROID
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	pthis->m_data.dump();
#endif
#endif

	return pthis;
}


void UONEstoreIAPAcknowledgeAsync::Activate()
{
#if PLATFORM_ANDROID	
	getListener()->m_OnPurchaseDataListener.BindUObject(
		this, &UONEstoreIAPAcknowledgeAsync::OnCompleted);
	NativeIapHelper->acknowledgeAsync(UNREAL_TO_ONESTORE_PURCHASEDATA(m_data).get());
#endif 
}


void UONEstoreIAPAcknowledgeAsync::OnCompleted( const int32& code, const FString& message,
												const FONEstorePurchaseData& data)
{
#if PLATFORM_ANDROID	
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT	
	data.dump();	
#endif

	switch ((ResponseCode)code) {
	case ResponseCode::RESULT_OK:
		OnSuccess.Broadcast(code, message, data); break;
	case ResponseCode::RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(code, message, data); break;
	case ResponseCode::RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(code, message, data); break;
	default:
		OnFailure.Broadcast(code, message, data); break;
	}
#endif
}

