// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIapAcknowledgePurchaseFunction.h"

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapAcknowledgePurchase(FString StringPurchaseData, FString DevPayload);
FOneStoreIapPurchaseData AndroidAcknowledgePurchaseParser_JsonParser(FString OriginalPurchaseJson);
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIapAcknowledgePurchaseFunction::UOneStoreIapAcknowledgePurchaseFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIapAcknowledgePurchaseFunction::Activate()
{
	StaticOneStoreIapAcknowledgePurchase.BindUObject(this, &UOneStoreIapAcknowledgePurchaseFunction::OnCompleteAcknowledge);
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIapAcknowledgePurchase(PurchaseData, DevPayload);
#endif
}

void UOneStoreIapAcknowledgePurchaseFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIapAcknowledgePurchaseFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		FOneStoreIapPurchaseData Dummy;
		UOneStoreIapAcknowledgePurchaseFunction::StaticOneStoreIapAcknowledgePurchase.Execute(errorCode, Dummy);
		UOneStoreIapAcknowledgePurchaseFunction::StaticOneStoreIapAcknowledgePurchase.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIapAcknowledgePurchaseFunction* UOneStoreIapAcknowledgePurchaseFunction::OneStoreIapAcknowledgePurchase(UObject* WorldContextObject, const FString& PurchaseData, const FString& DevPayload)
{
	UOneStoreIapAcknowledgePurchaseFunction* Proxy = NewObject<UOneStoreIapAcknowledgePurchaseFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->PurchaseData = PurchaseData;
	Proxy->DevPayload = DevPayload;
	return Proxy;
}


void UOneStoreIapAcknowledgePurchaseFunction::OnCompleteAcknowledge(int resultCode, const FOneStoreIapPurchaseData& OriginalPurchaseData)
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
void AndroidThunkJava_OneStoreIapAcknowledgePurchase(FString PurchaseData, FString DevPayload)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JavaOriginalPurchaseData = Env->NewStringUTF(TCHAR_TO_UTF8(*PurchaseData));
		jstring JavaDevPayload = Env->NewStringUTF(TCHAR_TO_UTF8(*DevPayload));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAAAcknowledgeAsync", "(Ljava/lang/String;Ljava/lang/String;J)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaOriginalPurchaseData, JavaDevPayload, ONESTORE_REQUEST_ACKNOWLEDGE);

		Env->DeleteLocalRef(JavaOriginalPurchaseData);
		Env->DeleteLocalRef(JavaDevPayload);
	}
} 

extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnAcknowledgePurchaseResponse(JNIEnv* jenv, jobject thiz, jstring JavaPurchaseData, jlong futureHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnAcknowledgePurchaseResponse"));

	FOneStoreIapPurchaseData OriginalPurchase;

	const char* charPurchaseData = jenv->GetStringUTFChars(JavaPurchaseData, 0);
	OriginalPurchase = AndroidAcknowledgePurchaseParser_JsonParser(FString(UTF8_TO_TCHAR(charPurchaseData)));

	jenv->ReleaseStringUTFChars(JavaPurchaseData, charPurchaseData);
	jenv->DeleteLocalRef(JavaPurchaseData);

	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call AcknowledgePurchase : %s"), *OriginalPurchase.OriginalPurchaseData);
	
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapAcknowledgePurchaseFunction::StaticOneStoreIapAcknowledgePurchase.Execute(RESULT_OK, OriginalPurchase);
		UOneStoreIapAcknowledgePurchaseFunction::StaticOneStoreIapAcknowledgePurchase.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
}

FOneStoreIapPurchaseData AndroidAcknowledgePurchaseParser_JsonParser(FString OriginalPurchaseJson) {
	FOneStoreIapPurchaseData NewPurchaseData;

	NewPurchaseData.OriginalPurchaseData = OriginalPurchaseJson;

	TSharedPtr<FJsonObject> jsonObject;
	TSharedRef< TJsonReader<TCHAR> > reader = TJsonReaderFactory<TCHAR>::Create(OriginalPurchaseJson);

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

UOneStoreIapAcknowledgePurchaseFunction::FStaticOneStoreIapAcknowledge UOneStoreIapAcknowledgePurchaseFunction::StaticOneStoreIapAcknowledgePurchase;

