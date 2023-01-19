/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPQueryProductDetailsAsync.h"
#include "ONEstoreIAP.h"

UONEstoreIAPQueryProductDetailsAsync::UONEstoreIAPQueryProductDetailsAsync(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{	
}


UONEstoreIAPQueryProductDetailsAsync* UONEstoreIAPQueryProductDetailsAsync::QueryProductDetailsAsync(
	const UObject* pWorld, const EONEstoreProductType type, const TArray<FString>& list )
{
	UONEstoreIAPQueryProductDetailsAsync* pthis = NewObject<UONEstoreIAPQueryProductDetailsAsync>();
	pthis->m_pWorld = pWorld;
	pthis->m_productType = type;
	pthis->m_productList = list;

	return pthis;
}


void UONEstoreIAPQueryProductDetailsAsync::Activate()
{	
#if PLATFORM_ANDROID	
	getListener()->m_OnProductDetailListListener.BindUObject(
		this, &UONEstoreIAPQueryProductDetailsAsync::OnCompleted );
			
	std::list<std::string> productList;
	for( FString prodName: m_productList ){
		productList.push_back(TCHAR_TO_UTF8(*prodName));
	}
		
	NativeIapHelper->queryProductDetailsAsync((ProductType)m_productType, &productList);
#endif
}


void UONEstoreIAPQueryProductDetailsAsync::OnCompleted( const int32& code, const FString& message,
														const TArray<FONEstoreProductDetail>& list) 
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
