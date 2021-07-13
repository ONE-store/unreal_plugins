// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIaaOfferwallFunction.h"

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIaaOpenOfferwall();
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIaaOfferwallFunction::UOneStoreIaaOfferwallFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIaaOfferwallFunction::Activate()
{
	StaticOneStoreIaaOfferwall.BindUObject(this, &UOneStoreIaaOfferwallFunction::OnCompleteOfferwall);
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIaaOpenOfferwall();
#endif
}

void UOneStoreIaaOfferwallFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIaaOfferwallFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIaaOfferwallFunction::StaticOneStoreIaaOfferwall.Execute(errorCode);
		UOneStoreIaaOfferwallFunction::StaticOneStoreIaaOfferwall.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIaaOfferwallFunction* UOneStoreIaaOfferwallFunction::OneStoreIaaOfferwall(UObject* WorldContextObject)
{
	UOneStoreIaaOfferwallFunction* Proxy = NewObject<UOneStoreIaaOfferwallFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}


void UOneStoreIaaOfferwallFunction::OnCompleteOfferwall(int resultCode)
{
	UE_LOG(LogTemp, Warning, TEXT("UOneStoreIaaOfferwallFunction : %d"), resultCode);
	switch (resultCode)
	{
	case RESULT_OK:
		OnSuccess.Broadcast(resultCode);
		break;
	default:
		OnFailure.Broadcast(resultCode);
		break;
	}
}

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIaaOpenOfferwall()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{

		UE_LOG(LogTemp, Warning, TEXT("AndroidTrunkJava_OpenOfferWall"));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_OpenOfferWall", "(J)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, ONESTORE_REQUEST_OFFERWALL);
	} 
}

#endif

UOneStoreIaaOfferwallFunction::FStaticOneStoreIaaOfferwall UOneStoreIaaOfferwallFunction::StaticOneStoreIaaOfferwall;
