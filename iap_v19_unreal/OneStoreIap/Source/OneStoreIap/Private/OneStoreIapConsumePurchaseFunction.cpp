// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIapConsumePurchaseFunction.h"


#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapConsumePurchase(FString StringPurchaseData, FString DevPayload);
FOneStoreIapPurchaseData AndroidConsumePurchaseParser_JsonParser(FString OriginalPurchaseJson);
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIapConsumePurchaseFunction::UOneStoreIapConsumePurchaseFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIapConsumePurchaseFunction::Activate()
{
	StaticOneStoreIapConsumePurchase.BindUObject(this, &UOneStoreIapConsumePurchaseFunction::OnCompleteConsume);
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIapConsumePurchase(PurchaseData, DevPayload);
#endif
}

void UOneStoreIapConsumePurchaseFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIapConsumePurchaseFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		FOneStoreIapPurchaseData Dummy;
		UOneStoreIapConsumePurchaseFunction::StaticOneStoreIapConsumePurchase.Execute(errorCode, Dummy);
		UOneStoreIapConsumePurchaseFunction::StaticOneStoreIapConsumePurchase.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIapConsumePurchaseFunction* UOneStoreIapConsumePurchaseFunction::OneStoreIapConsumePurchase(UObject* WorldContextObject, const FString& PurchaseData, const FString& DevPayload)
{
	UOneStoreIapConsumePurchaseFunction* Proxy = NewObject<UOneStoreIapConsumePurchaseFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->PurchaseData = PurchaseData;
	Proxy->DevPayload = DevPayload;
	return Proxy;
}


void UOneStoreIapConsumePurchaseFunction::OnCompleteConsume(int resultCode, const FOneStoreIapPurchaseData& OriginalPurchaseData)
{
	switch (resultCode)
	{
	case RESULT_OK:
		OnSuccess.Broadcast(resultCode, OriginalPurchaseData);
		break;
	case RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(resultCode, OriginalPurchaseData);
		break;
	case RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(resultCode, OriginalPurchaseData);
		break;
	default:
		OnFailure.Broadcast(resultCode, OriginalPurchaseData);
		break;
	}
}

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapConsumePurchase(FString PurchaseData, FString DevPayload)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JavaOriginalPurchaseData = Env->NewStringUTF(TCHAR_TO_UTF8(*PurchaseData));
		jstring JavaDevPayload = Env->NewStringUTF(TCHAR_TO_UTF8(*DevPayload));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAAConsumeAsync", "(Ljava/lang/String;Ljava/lang/String;J)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaOriginalPurchaseData, JavaDevPayload, ONESTORE_REQUEST_CONSUME);

		Env->DeleteLocalRef(JavaOriginalPurchaseData);
		Env->DeleteLocalRef(JavaDevPayload);
	}
} 


extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnConsumePurchaseResponse(JNIEnv* jenv, jobject thiz, jstring JavaPurchaseData, jlong futureHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnConsumePurchaseResponse"));

	FOneStoreIapPurchaseData OriginalPurchase;

	const char* charPurchaseData = jenv->GetStringUTFChars(JavaPurchaseData, 0);
	OriginalPurchase = AndroidConsumePurchaseParser_JsonParser(FString(UTF8_TO_TCHAR(charPurchaseData)));

	jenv->ReleaseStringUTFChars(JavaPurchaseData, charPurchaseData);
	jenv->DeleteLocalRef(JavaPurchaseData);

	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call AcknowledgePurchase : %s"), *OriginalPurchase.OriginalPurchaseData);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapConsumePurchaseFunction::StaticOneStoreIapConsumePurchase.Execute(RESULT_OK, OriginalPurchase);
		UOneStoreIapConsumePurchaseFunction::StaticOneStoreIapConsumePurchase.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);

}

FOneStoreIapPurchaseData AndroidConsumePurchaseParser_JsonParser(FString OriginalPurchaseJson) {
	FOneStoreIapPurchaseData NewPurchaseData;

	NewPurchaseData.OriginalPurchaseData = OriginalPurchaseJson;

	TSharedPtr<FJsonObject> jsonObject;
	TSharedRef< TJsonReader<> > reader = TJsonReaderFactory<>::Create(OriginalPurchaseJson);

	if (FJsonSerializer::Deserialize(reader, jsonObject) && jsonObject.IsValid())
	{
		NewPurchaseData.OrderId = jsonObject->GetStringField("orderId");
		NewPurchaseData.PackageName = jsonObject->GetStringField("packageName");
		NewPurchaseData.ProductId = jsonObject->GetStringField("productId");
		NewPurchaseData.PurchaseTime = jsonObject->GetStringField("purchaseTime");
		NewPurchaseData.AcknowlegeState = jsonObject->GetStringField("acknowlegeState");
		NewPurchaseData.DeveloperPayload = jsonObject->GetStringField("developerPayload");
		NewPurchaseData.PurchaseId = jsonObject->GetStringField("purchaseId");
		NewPurchaseData.PurchaseToken = jsonObject->GetStringField("purchaseToken");
		NewPurchaseData.BillingKey = jsonObject->GetStringField("billingKey");

		UE_LOG(LogTemp, Warning, TEXT("[request Purchase] OrderId : %s,  DeveloperPayload : %s,  PurchaseId : %s,  PurchaseToken : %s)"),
			*NewPurchaseData.OrderId, *NewPurchaseData.DeveloperPayload, *NewPurchaseData.PurchaseId, *NewPurchaseData.PurchaseToken);

	}
	return NewPurchaseData;
}


#endif

UOneStoreIapConsumePurchaseFunction::FStaticOneStoreIapConsume UOneStoreIapConsumePurchaseFunction::StaticOneStoreIapConsumePurchase;

