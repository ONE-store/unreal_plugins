// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIapRequestPurchaseFunction.h"

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapRequestPayment(FString ProductType, FString ProductId, FString ProductName, FString DevPayload);
FOneStoreIapPurchaseData AndroidRequestPurchaseParser_JsonParser(FString OriginalPurchaseJson);
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIapRequestPurchaseFunction::UOneStoreIapRequestPurchaseFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIapRequestPurchaseFunction::Activate()
{
	StaticOneStoreIapRequestPurchase.BindUObject(this, &UOneStoreIapRequestPurchaseFunction::OnCompleteRequestPurchase);
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIapRequestPayment(ProductType, ProductId, ProductName, DevPayload);
#endif
}

void UOneStoreIapRequestPurchaseFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIapRequestPurchaseFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		FOneStoreIapPurchaseData Dummy;
		UOneStoreIapRequestPurchaseFunction::StaticOneStoreIapRequestPurchase.Execute(errorCode, Dummy);
		UOneStoreIapRequestPurchaseFunction::StaticOneStoreIapRequestPurchase.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIapRequestPurchaseFunction* UOneStoreIapRequestPurchaseFunction::OneStoreIapRequestPurchase(UObject* WorldContextObject, 
	const FString& ProductType, 
	const FString& ProductId,
	const FString& ProductName, 
	const FString& DevPayload)
{
	UOneStoreIapRequestPurchaseFunction* Proxy = NewObject<UOneStoreIapRequestPurchaseFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ProductType = ProductType;
	Proxy->ProductId = ProductId;
	Proxy->ProductName = ProductName;
	Proxy->DevPayload = DevPayload;
	return Proxy;
}


void UOneStoreIapRequestPurchaseFunction::OnCompleteRequestPurchase(int resultCode, const FOneStoreIapPurchaseData& purchaseData)
{
	switch (resultCode)
	{
	case RESULT_OK:
		OnSuccess.Broadcast(resultCode, purchaseData);
		break;
	case RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(resultCode, purchaseData);
		break;
	case RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(resultCode, purchaseData);
		break;
	default:
		OnFailure.Broadcast(resultCode, purchaseData);
		break;
	}
}

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapRequestPayment(FString ProductType, FString ProductId, FString ProductName, FString DevPayload)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JavaProductType = Env->NewStringUTF(TCHAR_TO_UTF8(*ProductType));
		jstring JavaProductId = Env->NewStringUTF(TCHAR_TO_UTF8(*ProductId));
		jstring JavaProductName = Env->NewStringUTF(TCHAR_TO_UTF8(*ProductName));
		jstring JavaDevPayload = Env->NewStringUTF(TCHAR_TO_UTF8(*DevPayload));
		jstring JavaGameUser = Env->NewStringUTF(TCHAR_TO_UTF8(*""));
		jboolean JavaPromotionApplicable = (jboolean)false;

		UE_LOG(LogTemp, Warning, TEXT("[request Purchase] productId : %s,  ProductType : %s,  ProductName : %s,  DevPayload : %s)"), *ProductId, *ProductType, *ProductName, *DevPayload);

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAALaunchPurchaseFlow", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaProductId, JavaProductType, JavaProductName, JavaDevPayload, JavaGameUser, JavaPromotionApplicable);

		Env->DeleteLocalRef(JavaProductType);
		Env->DeleteLocalRef(JavaProductId);
		Env->DeleteLocalRef(JavaProductName);
		Env->DeleteLocalRef(JavaDevPayload);
		Env->DeleteLocalRef(JavaGameUser);
	} 
}

extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnPurchaseUpdated(JNIEnv* jenv, jobject thiz, jobjectArray purchases, jobjectArray signatures, jlong futureHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnPurchaseUpdated"));
	jsize purchasSize = jenv->GetArrayLength(purchases);

	FOneStoreIapPurchaseData NewPurchaseData;

	jstring JavaOriginalPurchaseData = (jstring)jenv->GetObjectArrayElement(purchases, 0);
	const char* charPurchaseData = jenv->GetStringUTFChars(JavaOriginalPurchaseData, 0);
	NewPurchaseData = AndroidRequestPurchaseParser_JsonParser(FString(UTF8_TO_TCHAR(charPurchaseData)));

	jstring JavaSignature = (jstring)jenv->GetObjectArrayElement(signatures, 0);
	const char* charsSignature = jenv->GetStringUTFChars(JavaSignature, 0);
	NewPurchaseData.SignatureData = FString(UTF8_TO_TCHAR(charsSignature));

	UE_LOG(LogTemp, Warning, TEXT("[UE4] = PurchaseData : %s"), *NewPurchaseData.OriginalPurchaseData);
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Signature : %s"), *NewPurchaseData.SignatureData);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapRequestPurchaseFunction::StaticOneStoreIapRequestPurchase.Execute(RESULT_OK, NewPurchaseData);
		UOneStoreIapRequestPurchaseFunction::StaticOneStoreIapRequestPurchase.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
}

FOneStoreIapPurchaseData AndroidRequestPurchaseParser_JsonParser(FString OriginalPurchaseJson) {
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

UOneStoreIapRequestPurchaseFunction::FStaticOneStoreIapRequestPurchase UOneStoreIapRequestPurchaseFunction::StaticOneStoreIapRequestPurchase;
