/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPQueryPurchasesAsync.h"
#include "ONEstoreIAP.h"

UONEstoreIAPQueryPurchasesAsync::UONEstoreIAPQueryPurchasesAsync(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


UONEstoreIAPQueryPurchasesAsync* UONEstoreIAPQueryPurchasesAsync::QueryPurchaseAsync(
	const UObject* pWorld, const EONEstoreProductType type )
{
	UONEstoreIAPQueryPurchasesAsync* pthis = NewObject<UONEstoreIAPQueryPurchasesAsync>();
	pthis->m_pWorld = pWorld;
	pthis->m_productType = type;

	return pthis;
}


void UONEstoreIAPQueryPurchasesAsync::Activate()
{
#if PLATFORM_ANDROID
	getListener()->m_OnPurchaseDataListListener.BindUObject(
		this, &UONEstoreIAPQueryPurchasesAsync::OnCompleted);

	NativeIapHelper->queryPurchasesAsync((ProductType)m_productType);
#endif
}



void UONEstoreIAPQueryPurchasesAsync::OnCompleted(const int32& code, const FString& message,
												  const TArray<FONEstorePurchaseData>& list)
{
#if PLATFORM_ANDROID
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT	
#endif

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
