/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPBase.h"
#include "ONEstoreIAP.h"



#if PLATFORM_ANDROID
bool UONEstoreIAPAsyncBase::m_setCallbackListener;
ONEstoreIAPListener	UONEstoreIAPAsyncBase::m_callbackListener;
#endif


//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------


void UONEstoreIAPShowToast::showToast( FString str )
{	
#if 1
#if PLATFORM_ANDROID
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	say( "i. showToast( %s )", TCHAR_TO_UTF8( *str ) );
#endif
	NativeIapHelper->showToast( TCHAR_TO_UTF8( *str ) );
#else
	UE_LOG( LogTemp, Warning, TEXT("[onestore] %s" ),	TCHAR_TO_UTF8( *str ) );
#endif
#endif
}


//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------


#if PLATFORM_ANDROID

void ONEstoreIAPListener::onSetupFinished(IapResult* presult) 
{
	processIapResult(presult);
}


void ONEstoreIAPListener::onServiceDisconnected()
{
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	say("i. ONEstore Iap Sevice Disconnected. ");
#endif
}


void ONEstoreIAPListener::onPurchasesResponse(IapResult* presult,
											  std::list<PurchaseData>* plist) 
{
	processPurchaseDataListResult(presult, plist);
}


void ONEstoreIAPListener::onPurchasesUpdated(IapResult* presult,
											 std::list<PurchaseData> *plist) 
{
	processPurchaseDataListResult(presult, plist);
}


void ONEstoreIAPListener::onProductDetailsResponse(IapResult* presult,
												   std::list<ProductDetail>* plist) 
{
	TArray<FONEstoreProductDetail> resultList;	
	for ( ProductDetail& p : *plist) {	
		resultList.Add( FONEstoreProductDetail( &p ) );
	}

	m_OnProductDetailListListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()),
		resultList);
}


void ONEstoreIAPListener::onAcknowledgeResponse(IapResult* presult,
												PurchaseData* pdata) 
{
	processPurchaseDataResult(presult, pdata);
}


void ONEstoreIAPListener::onConsumeResponse(IapResult* presult,
											PurchaseData* pdata) 
{
	processPurchaseDataResult(presult, pdata);
}


void ONEstoreIAPListener::onLaunchLoginFlowResponse(IapResult* presult)
{
	processIapResult(presult);
}


void ONEstoreIAPListener::onLaunchUpdateOrInstallFlowResponse(IapResult* presult)
{	
	processIapResult(presult);
}


void ONEstoreIAPListener::onRecurringResponse(IapResult* presult,
											  PurchaseData* pdata,
											  enum RecurringState state) 
{
	m_OnRecurringStateListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()), 
		FONEstorePurchaseData(pdata), EONEstoreRecurringState(state));
}


void ONEstoreIAPListener::onStoreInfoResponse(IapResult* presult, const char* pinfo)
{
	m_OnStoreInfoListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()),
		UTF8_TO_TCHAR(pinfo));
}


void ONEstoreIAPListener::processIapResult(IapResult* presult) 
{
	m_OnIapResultListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()));
}


void ONEstoreIAPListener::processPurchaseDataResult(IapResult* presult,
													PurchaseData* pdata) 
{
	m_OnPurchaseDataListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()),
		FONEstorePurchaseData(pdata));
}

void ONEstoreIAPListener::processPurchaseDataListResult(IapResult* presult,
														std::list<PurchaseData> *plist) 
{
	TArray<FONEstorePurchaseData> resultList;
	for( PurchaseData& p : *plist ){
		resultList.Add( FONEstorePurchaseData( &p ) );
	}

	m_OnPurchaseDataListListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()),
		resultList);
}

#endif


//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------



UONEstoreIAPSyncBase::UONEstoreIAPSyncBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}



UONEstoreIAPAsyncBase::UONEstoreIAPAsyncBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
#if PLATFORM_ANDROID
	// 최초 1회만 수행하도록 flag 둬서 수정필요
	if (m_setCallbackListener == false) {
		m_setCallbackListener = true;
		ONESTORE_IAP::NativeIapHelper->changeCallbacksListener(getListener());

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT	
		ONESTORE_IAP::NativeIapHelper->setLogLevel(ONESTORE_IAP::LogLevel::VERBOSE);
#else
		ONESTORE_IAP::NativeIapHelper->setLogLevel(ONESTORE_IAP::LogLevel::INFO);
#endif			
	}	
#endif
}


#if PLATFORM_ANDROID
ONEstoreIAPListener* UONEstoreIAPAsyncBase::getListener() {
	return &m_callbackListener;
}
#endif

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
