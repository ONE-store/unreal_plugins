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
#if PLATFORM_ANDROID
	NativeIapHelper->showToast(TCHAR_TO_UTF8(*str));
#else
	UE_LOG( LogTemp, Warning, TEXT("[onestore] %s"), TCHAR_TO_UTF8( *str ) );
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
	UE_LOG(LogTemp, Warning, TEXT("[onestore] %s"), "ONEstore Iap Sevice Disconnected" );
#endif
}


void ONEstoreIAPListener::onPurchasesUpdated(IapResult* presult,
											 std::list<PurchaseData> *plist) 
{
	processPurchaseDataListResult(presult, plist);
}


void ONEstoreIAPListener::onQueryPurchasesAsync(IapResult* presult,
											    std::list<PurchaseData>* plist)
{
	processPurchaseDataListResult(presult, plist);
}


void ONEstoreIAPListener::onQueryProductDetailsAsync(IapResult* presult,
												     std::list<ProductDetail>* plist) 
{
	TArray<FONEstoreProductDetail> resultList;
	for (auto iter : *plist) 
		resultList.Add(FONEstoreProductDetail(&iter));
	
	m_OnProductDetailListListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()),
		resultList);
}


void ONEstoreIAPListener::onAcknowledgeAsync(IapResult* presult, PurchaseData* pdata) 
{
	processPurchaseDataResult(presult, pdata);
}


void ONEstoreIAPListener::onConsumeAsync(IapResult* presult, PurchaseData* pdata) 
{
	processPurchaseDataResult(presult, pdata);
}


void ONEstoreIAPListener::onLaunchLoginFlowAsync(IapResult* presult)
{
	processIapResult(presult);
}


void ONEstoreIAPListener::onLaunchUpdateOrInstallFlow(IapResult* presult)
{
	processIapResult(presult);
}


void ONEstoreIAPListener::onManageRecurringProductAsync(IapResult* presult,
														PurchaseData* pdata,
														enum RecurringState state) 
{
	m_OnRecurringStateListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()), 
		FONEstorePurchaseData(pdata), EONEstoreRecurringState(state));
}


void ONEstoreIAPListener::onStoreInfoAsync(IapResult* presult, const char* pinfo)
{
	m_OnStoreInfoListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()),
		UTF8_TO_TCHAR(pinfo));
}


void ONEstoreIAPListener::processIapResult(IapResult* presult) {
	m_OnIapResultListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()));
}


void ONEstoreIAPListener::processPurchaseDataResult(IapResult* presult,
													PurchaseData* pdata) {
	m_OnPurchaseDataListener.ExecuteIfBound(
		(int32)presult->getResponseCode(), UTF8_TO_TCHAR(presult->getMessage()),
		FONEstorePurchaseData(pdata));
}

void ONEstoreIAPListener::processPurchaseDataListResult(IapResult* presult,
														std::list<PurchaseData> *plist) {
	TArray<FONEstorePurchaseData> resultList;
	for (auto iter : *plist)
		resultList.Add(FONEstorePurchaseData(&iter));

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
	if (m_setCallbackListener == false) {
		m_setCallbackListener = true;
		ONESTORE_IAP::NativeIapHelper->changeCallbacksListener(getListener());
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
