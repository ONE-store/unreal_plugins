
#include "OneStoreIapGetPurchaseFunction.h"

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapGetPurchase(FString ProductType);
FOneStoreIapPurchaseData AndroidPurchaseParser_JsonParser(FString OriginalPurchaseJson);
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIapGetPurchaseFunction::UOneStoreIapGetPurchaseFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIapGetPurchaseFunction::Activate()
{
	StaticOneStoreIapGetPurchaseInfo.BindUObject(this, &UOneStoreIapGetPurchaseFunction::OnCompleteGetPurchase);
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIapGetPurchase(ProductType);
#endif
}

void UOneStoreIapGetPurchaseFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIapGetPurchaseFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		TArray<FOneStoreIapPurchaseData> Dummy;
		UOneStoreIapGetPurchaseFunction::StaticOneStoreIapGetPurchaseInfo.Execute(errorCode, Dummy);
		UOneStoreIapGetPurchaseFunction::StaticOneStoreIapGetPurchaseInfo.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIapGetPurchaseFunction* UOneStoreIapGetPurchaseFunction::OneStoreIapPurchaseInfo(UObject* WorldContextObject, const FString& ProductType)
{
	UOneStoreIapGetPurchaseFunction* Proxy = NewObject<UOneStoreIapGetPurchaseFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ProductType = ProductType;
	return Proxy;
}


void UOneStoreIapGetPurchaseFunction::OnCompleteGetPurchase(int resultCode, const TArray<FOneStoreIapPurchaseData>& OneStorePurchaseData)
{
	switch (resultCode)
	{
	case RESULT_OK:
		OnSuccess.Broadcast(resultCode, OneStorePurchaseData);
		break;
	case RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(resultCode, OneStorePurchaseData);
		break;
	case RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(resultCode, OneStorePurchaseData);
		break;
	default:
		OnFailure.Broadcast(resultCode, OneStorePurchaseData);
		break;
	}
}

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapGetPurchase(FString ProductType)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JavaProductType = Env->NewStringUTF(TCHAR_TO_UTF8(*ProductType));

		UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call AndroidThunkJava_OneStoreIapGetPurchase %s"), *ProductType);

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAAQueryPurchasesAsync", "(Ljava/lang/String;J)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaProductType, ONESTORE_REQUEST_PURCHASE);

		Env->DeleteLocalRef(JavaProductType);
	} 
}

FOneStoreIapPurchaseData AndroidPurchaseParser_JsonParser(FString OriginalPurchaseJson) {
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

extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnQueryPurchasesResponse(JNIEnv* jenv, jobject thiz, jobjectArray purchaseList, jobjectArray signatureList, jlong futureHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnQueryPurchasesResponse"));
	jsize purchaseSize = jenv->GetArrayLength(purchaseList);
	jsize signatureSize = jenv->GetArrayLength(signatureList);

	TArray<FOneStoreIapPurchaseData> ProvidedPurchaseInfomation;

	for (jsize Idx = 0; Idx < purchaseSize; Idx++)
	{
		FOneStoreIapPurchaseData NewPurchaseData;

		jstring JavaPurchaseData = (jstring)jenv->GetObjectArrayElement(purchaseList, Idx);
		const char* charPurchase = jenv->GetStringUTFChars(JavaPurchaseData, 0);
		NewPurchaseData = AndroidPurchaseParser_JsonParser(FString(UTF8_TO_TCHAR(charPurchase)));

		jenv->ReleaseStringUTFChars(JavaPurchaseData, charPurchase);
		jenv->DeleteLocalRef(JavaPurchaseData);

		jstring JavaSignature = (jstring)jenv->GetObjectArrayElement(signatureList, Idx);
		const char* charSignature = jenv->GetStringUTFChars(JavaSignature, 0);
		NewPurchaseData.SignatureData = FString(UTF8_TO_TCHAR(charSignature));

		jenv->ReleaseStringUTFChars(JavaSignature, charSignature);
		jenv->DeleteLocalRef(JavaSignature);

		UE_LOG(LogTemp, Warning, TEXT("[UE4] = purchase data : %s"), *NewPurchaseData.OriginalPurchaseData);
		UE_LOG(LogTemp, Warning, TEXT("[UE4] = signature data : %s"), *NewPurchaseData.SignatureData);

		ProvidedPurchaseInfomation.Add(NewPurchaseData);
	}

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapGetPurchaseFunction::StaticOneStoreIapGetPurchaseInfo.Execute(RESULT_OK, ProvidedPurchaseInfomation);
		UOneStoreIapGetPurchaseFunction::StaticOneStoreIapGetPurchaseInfo.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
}

#endif

UOneStoreIapGetPurchaseFunction::FStaticOneStoreIapPurchase UOneStoreIapGetPurchaseFunction::StaticOneStoreIapGetPurchaseInfo;

