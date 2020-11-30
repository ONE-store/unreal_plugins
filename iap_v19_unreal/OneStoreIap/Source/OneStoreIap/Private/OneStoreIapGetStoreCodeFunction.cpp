// Fill out your copyright notice in the Description page of Project Settings.

#include "OneStoreIapGetStoreCodeFunction.h"

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapGetStoreCode();
FOneStoreIapProductData AndroidProductDetail_JsonParser(FString productDetail);
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIapGetStoreCodeFunction::UOneStoreIapGetStoreCodeFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIapGetStoreCodeFunction::Activate()
{
	StaticOneStoreIapGetStoreCode.BindUObject(this, &UOneStoreIapGetStoreCodeFunction::OnCompleteGetStoreCode);

	// JNI�� ���� Common Error�� ȣ��� ��� �ش� ���� �̺�Ʈ�� BluePrint���� ���� ���� �� �ֵ��� HandleError �Լ��� ������ �ʿ䰡 �ִ�.
	// �������� JNI����� ����ϴ� Function Ŭ������ ��� �ݵ�� HandleError ó���� �ϵ��� �Ѵ�.
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIapGetStoreCode();
#else
	UOneStoreIapGetStoreCodeFunction::StaticOneStoreIapGetStoreCode.Unbind();
#endif
}

// ProductDeatailȣ�� �� ������ �ƴ� �ᱫ�� ���� �޾��� �� OneStoreIapCommonError.cpp�� ���� ȣ��ǵ��� ������ �ؾ��Ѵ�.
// �ش� �Լ��� Activation�� OneStoreIapCommonError�� static �Լ� �����Ϳ� ���� ��Ų��.
void UOneStoreIapGetStoreCodeFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIapGetStoreCodeFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapGetStoreCodeFunction::StaticOneStoreIapGetStoreCode.Execute(errorCode, "");
		UOneStoreIapGetStoreCodeFunction::StaticOneStoreIapGetStoreCode.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIapGetStoreCodeFunction* UOneStoreIapGetStoreCodeFunction::OneStoreIapGetStoreCode(UObject* WorldContextObject)
{
	UOneStoreIapGetStoreCodeFunction* Proxy = NewObject<UOneStoreIapGetStoreCodeFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}


void UOneStoreIapGetStoreCodeFunction::OnCompleteGetStoreCode(int resultCode, const FString& StoreCode)
{
	switch (resultCode)
	{
	case RESULT_OK :
		OnSuccess.Broadcast(resultCode, StoreCode);
		break;
	case RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(resultCode, StoreCode);
		break;
	case RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(resultCode, StoreCode);
		break;
	default:
		OnFailure.Broadcast(resultCode, StoreCode);
		break;
	}
}

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapGetStoreCode()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAAGetStoreInfoAsync", "(J)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, ONESTORE_REQUEST_STORECODE);
	}
}


extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnStoreInfoResponse(JNIEnv* jenv, jobject thiz, jstring JavaStoreCode, jlong futureHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnStoreInfoResponse"));
	const char* charStoreCode = jenv->GetStringUTFChars(JavaStoreCode, 0);
	FString StoreCode = FString(UTF8_TO_TCHAR(charStoreCode));

	jenv->ReleaseStringUTFChars(JavaStoreCode, charStoreCode);
	jenv->DeleteLocalRef(JavaStoreCode);

	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call StoreCode : %s"), *StoreCode);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapGetStoreCodeFunction::StaticOneStoreIapGetStoreCode.Execute(RESULT_OK, StoreCode);
		UOneStoreIapGetStoreCodeFunction::StaticOneStoreIapGetStoreCode.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
}

#endif

UOneStoreIapGetStoreCodeFunction::FStaticOneStoreIapStoreCode UOneStoreIapGetStoreCodeFunction::StaticOneStoreIapGetStoreCode;

