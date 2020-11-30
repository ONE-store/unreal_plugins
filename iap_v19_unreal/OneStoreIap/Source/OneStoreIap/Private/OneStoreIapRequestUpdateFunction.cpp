// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIapRequestUpdateFunction.h"

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapRequestUpdate();
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIapRequestUpdateFunction::UOneStoreIapRequestUpdateFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIapRequestUpdateFunction::Activate()
{
	StaticOneStoreIapRequestUpdate.BindUObject(this, &UOneStoreIapRequestUpdateFunction::OnCompleteRequestUpdate);
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIapRequestUpdate();
#endif
}

void UOneStoreIapRequestUpdateFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIapRequestUpdateFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapRequestUpdateFunction::StaticOneStoreIapRequestUpdate.Execute(errorCode);
		UOneStoreIapRequestUpdateFunction::StaticOneStoreIapRequestUpdate.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIapRequestUpdateFunction* UOneStoreIapRequestUpdateFunction::OneStoreIapRequestUpdate(UObject* WorldContextObject)
{
	UOneStoreIapRequestUpdateFunction* Proxy = NewObject<UOneStoreIapRequestUpdateFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}


void UOneStoreIapRequestUpdateFunction::OnCompleteRequestUpdate(int resultCode)
{
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
void AndroidThunkJava_OneStoreIapRequestUpdate()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{

		UE_LOG(LogTemp, Warning, TEXT("AndroidThunkJava_OneStoreIapRequestUpdate"));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAALaunchUpdateOrInstall", "(J)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, ONESTORE_REQUEST_UPDATE);
	} 
}

#endif

UOneStoreIapRequestUpdateFunction::FStaticOneStoreIapRequestUpdate UOneStoreIapRequestUpdateFunction::StaticOneStoreIapRequestUpdate;
