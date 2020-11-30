// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIapManageRecurringFunction.h"


#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapManageRecurring(FString StringPurchaseData);
FOneStoreIapPurchaseData AndroidManageRecurringPurchaseParser_JsonParser(FString OriginalPurchaseJson);
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIapManageRecurringFunction::UOneStoreIapManageRecurringFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIapManageRecurringFunction::Activate()
{
	StaticOneStoreIapManageRecurring.BindUObject(this, &UOneStoreIapManageRecurringFunction::OnCompleteManageRecurring);
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIapManageRecurring(PurchaseData);
#endif
}

void UOneStoreIapManageRecurringFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIapManageRecurringFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		FOneStoreIapPurchaseData Dummy;
		UOneStoreIapManageRecurringFunction::StaticOneStoreIapManageRecurring.Execute(errorCode, "", Dummy);
		UOneStoreIapManageRecurringFunction::StaticOneStoreIapManageRecurring.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIapManageRecurringFunction* UOneStoreIapManageRecurringFunction::OneStoreIapManageRecurring(UObject* WorldContextObject, const FString& PurchaseData)
{
	UOneStoreIapManageRecurringFunction* Proxy = NewObject<UOneStoreIapManageRecurringFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->PurchaseData = PurchaseData;
	return Proxy;
}


void UOneStoreIapManageRecurringFunction::OnCompleteManageRecurring(int resultCode, const FString& Action, const FOneStoreIapPurchaseData& OriginalPurchaseData)
{
	switch (resultCode)
	{
	case RESULT_OK:
		OnSuccess.Broadcast(resultCode, Action, OriginalPurchaseData);
		break;
	case RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(resultCode, Action, OriginalPurchaseData);
		break;
	case RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(resultCode, Action, OriginalPurchaseData);
		break;
	default:
		OnFailure.Broadcast(resultCode, Action, OriginalPurchaseData);
		break;
	}
}

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapManageRecurring(FString PurchaseData)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JavaOriginalPurchaseData = Env->NewStringUTF(TCHAR_TO_UTF8(*PurchaseData));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAAManageRecurringProductAsync", "(Ljava/lang/String;J)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaOriginalPurchaseData, ONESTORE_REQUEST_MANAGED_RECURRING);

		Env->DeleteLocalRef(JavaOriginalPurchaseData);
	}
} 


extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnRecurringProductResponse(JNIEnv* jenv, jobject thiz, jstring JavaPurchaseData, jstring JavaAction, jlong futureHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnRecurringProductResponse"));

	FOneStoreIapPurchaseData OriginalPurchase;

	const char* charPurchaseData = jenv->GetStringUTFChars(JavaPurchaseData, 0);
	OriginalPurchase = AndroidManageRecurringPurchaseParser_JsonParser(FString(UTF8_TO_TCHAR(charPurchaseData)));

	jenv->ReleaseStringUTFChars(JavaPurchaseData, charPurchaseData);
	jenv->DeleteLocalRef(JavaPurchaseData);

	const char* charAction= jenv->GetStringUTFChars(JavaAction, 0);
	FString Action = FString(UTF8_TO_TCHAR(charAction));

	jenv->ReleaseStringUTFChars(JavaAction, charAction);
	jenv->DeleteLocalRef(JavaAction);

	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call ManageRecurring : %s , Action : %s"), *OriginalPurchase.OriginalPurchaseData, *Action);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapManageRecurringFunction::StaticOneStoreIapManageRecurring.Execute(RESULT_OK, Action, OriginalPurchase);
		UOneStoreIapManageRecurringFunction::StaticOneStoreIapManageRecurring.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);

}

FOneStoreIapPurchaseData AndroidManageRecurringPurchaseParser_JsonParser(FString OriginalPurchaseJson) {
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

UOneStoreIapManageRecurringFunction::FStaticOneStoreIapManageRecurring UOneStoreIapManageRecurringFunction::StaticOneStoreIapManageRecurring;

