/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPLaunchPurchaseFlow.h"
#include "ONEstoreIAP.h"

UONEstoreIAPLaunchPurchaseFlow::UONEstoreIAPLaunchPurchaseFlow(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


UONEstoreIAPLaunchPurchaseFlow* UONEstoreIAPLaunchPurchaseFlow::LaunchPurchaseFlow(
	const UObject* pWorld,
	const FString& product_id, const EONEstoreProductType type, const FString& developer_payload,
	const FString& product_name, const FString& game_user_id, const int quantity, const bool promotion_applicable)
{
	UONEstoreIAPLaunchPurchaseFlow* pthis = NewObject<UONEstoreIAPLaunchPurchaseFlow>();
	pthis->m_pWorld = pWorld;
	pthis->m_product_id = product_id;
	pthis->m_type = type;
	pthis->m_developer_payload = developer_payload;
	pthis->m_product_name = product_name;
	pthis->m_game_user_id = game_user_id;
	pthis->m_quantity = quantity;
	pthis->m_promotion_applicable = promotion_applicable;

	return pthis;
}


void UONEstoreIAPLaunchPurchaseFlow::Activate()
{
#if PLATFORM_ANDROID	
	getListener()->m_OnPurchaseDataListListener.BindUObject(
		this, &UONEstoreIAPLaunchPurchaseFlow::OnCompleted);

	NativeIapHelper->launchPurchaseFlow( 
		TCHAR_TO_UTF8(*m_product_id ), (ProductType)m_type, TCHAR_TO_UTF8(*m_developer_payload), 
		TCHAR_TO_UTF8(*m_product_name), TCHAR_TO_UTF8(*m_game_user_id), m_quantity, m_promotion_applicable );
#endif 
}


void UONEstoreIAPLaunchPurchaseFlow::OnCompleted(const int32& code, const FString& message,
												 const TArray<FONEstorePurchaseData>& list)
{
#if PLATFORM_ANDROID	
	switch ((ResponseCode)code) {
	case ResponseCode::RESULT_OK:
		OnSuccess.Broadcast(code, message, list);	break;
	case ResponseCode::RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(code, message, list); break;
	case ResponseCode::RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(code, message, list); break;
	default:
		OnFailure.Broadcast(code, message, list); break;
	}
#endif
}
