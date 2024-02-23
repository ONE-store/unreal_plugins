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
	UONEstoreIAPQueryProductDetailsAsync* pthis = 
		NewObject<UONEstoreIAPQueryProductDetailsAsync>();
	pthis->m_pWorld = pWorld;
	pthis->m_productType = type;
	pthis->m_productList = list;

#if PLATFORM_ANDROID
	say("d. check in");
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	say( "d. productType( %d ).", pthis->m_productType );
	for( auto& iter : pthis->m_productList ){
		say( "d. item( %s )", TCHAR_TO_UTF8( *(iter) ) );
	}
#endif 
#endif 
	return pthis;
}


void UONEstoreIAPQueryProductDetailsAsync::Activate()
{	
#if PLATFORM_ANDROID
	say("d. check in");
	getListener()->m_OnProductDetailListListener.BindUObject(
		this, &UONEstoreIAPQueryProductDetailsAsync::OnCompleted );
			
	std::list<std::string> productList;	
	for( auto& iter : m_productList ){
		productList.push_back( TCHAR_TO_UTF8(*(iter) ) );
	}
	
	NativeIapHelper->queryProductDetailsAsync( (ProductType)m_productType, productList );
#endif
}


void UONEstoreIAPQueryProductDetailsAsync::OnCompleted( const int32& code, 
														const FString& message,
														const TArray<FONEstoreProductDetail>& list ) 
{
#if PLATFORM_ANDROID
	say("d. check in");

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	say("d. result( %d, %s ). list item count( %d ).", code, TCHAR_TO_UTF8(*message), list.Num());
	for( auto& iter : list ){
		iter.dump();
	}
#endif

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
