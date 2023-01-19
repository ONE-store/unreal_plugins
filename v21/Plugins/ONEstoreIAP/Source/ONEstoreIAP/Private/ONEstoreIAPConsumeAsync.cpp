/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPConsumeAsync.h"
#include "ONEstoreIAP.h"

UONEstoreIAPConsumeAsync::UONEstoreIAPConsumeAsync(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


UONEstoreIAPConsumeAsync* UONEstoreIAPConsumeAsync::ConsumeAsync(
	const UObject* pWorld, const FONEstorePurchaseData& data)
{
	UONEstoreIAPConsumeAsync* pthis = NewObject<UONEstoreIAPConsumeAsync>();
	pthis->m_pWorld = pWorld;
	pthis->m_data = data;

	return pthis;
}


void UONEstoreIAPConsumeAsync::Activate()
{
#if PLATFORM_ANDROID
	getListener()->m_OnPurchaseDataListener.BindUObject(
		this, &UONEstoreIAPConsumeAsync::OnCompleted);

	NativeIapHelper->consumeAsync( UNREAL_TO_ONESTORE_PURCHASEDATA(m_data).get() );
#endif 
}


void UONEstoreIAPConsumeAsync::OnCompleted( const int32& code, const FString& message,
											const FONEstorePurchaseData& data )
{
#if PLATFORM_ANDROID	
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
