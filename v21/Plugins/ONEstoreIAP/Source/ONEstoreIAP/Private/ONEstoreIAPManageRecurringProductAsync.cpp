/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPManageRecurringProductAsync.h"
#include "ONEstoreIAP.h"

UONEstoreIAPManageRecurringProductAsync::UONEstoreIAPManageRecurringProductAsync(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


UONEstoreIAPManageRecurringProductAsync* UONEstoreIAPManageRecurringProductAsync::ManageRecurringProductAsync(
	const UObject* pWorld, const FONEstorePurchaseData& data, const EONEstoreRecurringState state )
{
	UONEstoreIAPManageRecurringProductAsync* pthis = NewObject<UONEstoreIAPManageRecurringProductAsync>();
	pthis->m_pWorld = pWorld;
	pthis->m_data = data;
	pthis->m_state = state;

	return pthis;
}


void UONEstoreIAPManageRecurringProductAsync::Activate()
{
#if PLATFORM_ANDROID
	getListener()->m_OnRecurringStateListener.BindUObject(
		this, &UONEstoreIAPManageRecurringProductAsync::OnCompleted );

	NativeIapHelper->manageRecurringProductAsync(
		UNREAL_TO_ONESTORE_PURCHASEDATA(m_data).get(), (RecurringState)m_state);
#endif 
}


void UONEstoreIAPManageRecurringProductAsync::OnCompleted(const int32& code, const FString& message,
														  const FONEstorePurchaseData& data, 
														  const EONEstoreRecurringState& state)
{
#if PLATFORM_ANDROID	
	switch ((ResponseCode)code) {
	case ResponseCode::RESULT_OK:
		OnSuccess.Broadcast(code, message, data, state);	break;
	case ResponseCode::RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(code, message, data, state); break;
	case ResponseCode::RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(code, message, data, state); break;
	default:
		OnFailure.Broadcast(code, message, data, state); break;
	}
#endif
}
