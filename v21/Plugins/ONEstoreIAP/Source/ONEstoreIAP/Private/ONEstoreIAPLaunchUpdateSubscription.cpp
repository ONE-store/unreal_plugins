/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPLaunchUpdateSubscription.h"
#include "ONEstoreIAP.h"

UONEstoreIAPLaunchUpdateSubscription::UONEstoreIAPLaunchUpdateSubscription(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


UONEstoreIAPLaunchUpdateSubscription* UONEstoreIAPLaunchUpdateSubscription::LaunchUpdateSubscription(
	const UObject* pWorld,
	const FString& product_id, const FString& developer_payload, 
	const FString& product_name, const FString& old_purchase_token, const EONEstoreProrationMode proration_mode )
{
	UONEstoreIAPLaunchUpdateSubscription* pthis = NewObject<UONEstoreIAPLaunchUpdateSubscription>();

#if PLATFORM_ANDROID	
	pthis->m_pWorld				= pWorld;	
	pthis->m_product_id			= product_id;
	pthis->m_developer_payload	= developer_payload;
	pthis->m_product_name		= product_name;
	pthis->m_old_purchase_token = old_purchase_token;
	pthis->m_proration_mode		= proration_mode;
#endif

	return pthis;
}


void UONEstoreIAPLaunchUpdateSubscription::Activate()
{
#if PLATFORM_ANDROID	
	getListener()->m_OnPurchaseDataListListener.BindUObject(
		this, &UONEstoreIAPLaunchUpdateSubscription::OnCompleted);

	NativeIapHelper->launchUpdateSubscription( 
		TCHAR_TO_UTF8(*m_product_id), TCHAR_TO_UTF8(*m_developer_payload),
		TCHAR_TO_UTF8(*m_product_name), TCHAR_TO_UTF8(*m_old_purchase_token), (ProrationMode)m_proration_mode );
#endif 
}


void UONEstoreIAPLaunchUpdateSubscription::OnCompleted( const int32& code, const FString& message,
														const TArray<FONEstorePurchaseData>& list)
{
#if PLATFORM_ANDROID	
	switch ((ResponseCode)code) {
	case ResponseCode::RESULT_OK:
		OnSuccess.Broadcast(code, message, list); break;
	case ResponseCode::RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(code, message, list); break;
	case ResponseCode::RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(code, message, list); break;
	default:
		OnFailure.Broadcast(code, message, list); break;
	}
#endif
}
