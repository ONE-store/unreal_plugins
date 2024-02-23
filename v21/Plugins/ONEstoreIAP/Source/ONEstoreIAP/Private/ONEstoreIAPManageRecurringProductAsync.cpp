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
	UONEstoreIAPManageRecurringProductAsync* pthis = 
		NewObject<UONEstoreIAPManageRecurringProductAsync>();
	pthis->m_pWorld = pWorld;
	pthis->m_data = data;
	pthis->m_state = state;

#if PLATFORM_ANDROID
	say("d. check in");
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	pthis->m_data.dump();
	say("d. recurreing state( %d )", (int)pthis->m_state);
#endif 
#endif 

	return pthis;
}


void UONEstoreIAPManageRecurringProductAsync::Activate()
{
#if PLATFORM_ANDROID
	say("d. check in");
	getListener()->m_OnRecurringStateListener.BindUObject(
		this, &UONEstoreIAPManageRecurringProductAsync::OnCompleted );

	PurchaseDataCore core( TCHAR_TO_UTF8(*(m_data.OriginalJson)),
						   TCHAR_TO_UTF8( *(m_data.Signature)),
						   TCHAR_TO_UTF8( *(m_data.BillingKey)) );
	NativeIapHelper->manageRecurringProductAsync( &core, (RecurringState)m_state );
#endif 

}


void UONEstoreIAPManageRecurringProductAsync::OnCompleted( const int32& code, 
														   const FString& message,
														   const FONEstorePurchaseData& data, 
														   const EONEstoreRecurringState& state )
{	
#if PLATFORM_ANDROID	
	say("d. check in");
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	say("d. result( %d, %s ). RecurringState( %d )", code, TCHAR_TO_UTF8(*message), state);
	data.dump();
#endif
	
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

