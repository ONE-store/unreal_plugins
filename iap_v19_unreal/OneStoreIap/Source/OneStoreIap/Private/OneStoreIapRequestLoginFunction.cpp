// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIapRequestLoginFunction.h"

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapRequestLogin();
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIapRequestLoginFunction::UOneStoreIapRequestLoginFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIapRequestLoginFunction::Activate()
{
	StaticOneStoreIapRequestLogin.BindUObject(this, &UOneStoreIapRequestLoginFunction::OnCompleteRequestLogin);
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIapRequestLogin();
#endif
}

void UOneStoreIapRequestLoginFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIapRequestLoginFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapRequestLoginFunction::StaticOneStoreIapRequestLogin.Execute(errorCode);
		UOneStoreIapRequestLoginFunction::StaticOneStoreIapRequestLogin.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIapRequestLoginFunction* UOneStoreIapRequestLoginFunction::OneStoreIapRequestLogin(UObject* WorldContextObject)
{
	UOneStoreIapRequestLoginFunction* Proxy = NewObject<UOneStoreIapRequestLoginFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}


void UOneStoreIapRequestLoginFunction::OnCompleteRequestLogin(int resultCode)
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
void AndroidThunkJava_OneStoreIapRequestLogin()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{

		UE_LOG(LogTemp, Warning, TEXT("AndroidThunkJava_OneStoreIapRequestLogin"));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAALaunchLoginFlowAsync", "(J)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, ONESTORE_REQUEST_LOGIN);
	} 
}

#endif

UOneStoreIapRequestLoginFunction::FStaticOneStoreIapRequestLogin UOneStoreIapRequestLoginFunction::StaticOneStoreIapRequestLogin;
