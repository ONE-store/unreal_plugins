// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIapProductDetailsFunction.h"

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapGetProductDetails(FString ProductType, TArray<FString> ProductList);
FOneStoreIapProductData AndroidProductDetail_JsonParser(FString productDetail);
#endif

// Add default functionality here for any IOneStoreIapFunction functions that are not pure virtual.
UOneStoreIapProductDetailsFunction::UOneStoreIapProductDetailsFunction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOneStoreIapProductDetailsFunction::Activate()
{
	StaticOneStoreIapGetProductDetails.BindUObject(this, &UOneStoreIapProductDetailsFunction::OnCompleteGetProductDetails);

	// JNI를 통해 Common Error가 호출된 경우 해당 에러 이벤트를 BluePrint에서 전달 받을 수 있도록 HandleError 함수를 전달할 필요가 있다.
	// 원스토어와 JNI통신을 담당하는 Function 클리스의 경우 반드시 HandleError 처리를 하도록 한다.
	StaticErrorHandle = this->HandleError;

#if PLATFORM_ANDROID
	AndroidThunkJava_OneStoreIapGetProductDetails(ProductType, ProductList);
#else
	UOneStoreIapProductDetailsFunction::StaticOneStoreIapGetProductDetails.Unbind();
#endif
}

// ProductDeatail호출 시 성공이 아닌 결괴를 리턴 받았을 때 OneStoreIapCommonError.cpp를 통해 호출되도록 구현을 해야한다.
// 해당 함수를 Activation때 OneStoreIapCommonError의 static 함수 포인터에 저장 시킨다.
void UOneStoreIapProductDetailsFunction::HandleError(int errorCode)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call UOneStoreIapProductDetailsFunction HandleError %d"), errorCode);

#if PLATFORM_ANDROID
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		TArray<FOneStoreIapProductData> Dummy;
		UOneStoreIapProductDetailsFunction::StaticOneStoreIapGetProductDetails.Execute(errorCode, Dummy);
		UOneStoreIapProductDetailsFunction::StaticOneStoreIapGetProductDetails.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
#endif
}

UOneStoreIapProductDetailsFunction* UOneStoreIapProductDetailsFunction::OneStoreIapGetProductDetails(UObject* WorldContextObject, const FString& ProductType, const TArray<FString>& ProductList)
{
	UOneStoreIapProductDetailsFunction* Proxy = NewObject<UOneStoreIapProductDetailsFunction>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ProductType = ProductType;
	Proxy->ProductList = ProductList;
	return Proxy;
}


void UOneStoreIapProductDetailsFunction::OnCompleteGetProductDetails(int resultCode, const TArray<FOneStoreIapProductData>& ProductDetailList)
{
	switch (resultCode)
	{
	case RESULT_OK :
		OnSuccess.Broadcast(resultCode, ProductDetailList);
		break;
	case RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(resultCode, ProductDetailList);
		break;
	case RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(resultCode, ProductDetailList);
		break;
	default:
		OnFailure.Broadcast(resultCode, ProductDetailList);
		break;
	}
}

#if PLATFORM_ANDROID
void AndroidThunkJava_OneStoreIapGetProductDetails(FString ProductType, TArray<FString> ProductList)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JavaProductType = Env->NewStringUTF(TCHAR_TO_UTF8(*ProductType));
		jobjectArray JavaProductList = (jobjectArray)Env->NewObjectArray(ProductList.Num(), Env->FindClass("java/lang/String"), Env->NewStringUTF(""));

		int i = 0;

		for (FString Str : ProductList)
		{
			UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call productList %s"), *Str);
			Env->SetObjectArrayElement(JavaProductList, i++, Env->NewStringUTF(TCHAR_TO_UTF8(*Str)));
		}


		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAAQueryProductDetails", "([Ljava/lang/String;Ljava/lang/String;J)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaProductList, JavaProductType, ONESTORE_REQUEST_PRODUCT_DETAIL);

		Env->DeleteLocalRef(JavaProductList);
		Env->DeleteLocalRef(JavaProductType);
	}
}

FOneStoreIapProductData AndroidProductDetail_JsonParser(FString productDetail) {
	FOneStoreIapProductData NewProductInfo;

	NewProductInfo.OriginalProductJson = productDetail;

	TSharedPtr<FJsonObject> jsonObject;
	TSharedRef< TJsonReader<> > reader = TJsonReaderFactory<>::Create(productDetail);

	if (FJsonSerializer::Deserialize(reader, jsonObject) && jsonObject.IsValid())
	{
	//	jsonObj->GetObjectFiled(KeyString);	// One object of current Object
//		jsonObj->GetIntegerFiled(KeyString);	// Return current object value
	//	jsonObj->GetBoolFiled(KeyString);
	//	jsonObj->GetNumberFiled(KeyString);
		NewProductInfo.PriceCurrencyCode = jsonObject->GetStringField("priceCurrencyCode");
		NewProductInfo.ProductId = jsonObject->GetStringField("productId");
		NewProductInfo.Title = jsonObject->GetStringField("title");
		NewProductInfo.Type = jsonObject->GetStringField("type");
		NewProductInfo.Price = jsonObject->GetStringField("price");
		NewProductInfo.PriceAmountMicros = jsonObject->GetStringField("priceAmountMicros");
	}
	return NewProductInfo;
}

extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnProductDetailsResponse(JNIEnv* jenv, jobject thiz, jobjectArray productDetails, jlong futureHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_onestore_OnestoreIapHelper_nativeOnProductDetailsResponse"));
	jsize productSize = jenv->GetArrayLength(productDetails);

	TArray<FOneStoreIapProductData> ProvidedProductInformation;

	for (jsize Idx = 0; Idx < productSize; Idx++)
	{
		FOneStoreIapProductData NewProduct;
		jstring JavaProductDetail = (jstring)jenv->GetObjectArrayElement(productDetails, Idx);
		const char* charProductDetail = jenv->GetStringUTFChars(JavaProductDetail, 0);
		FString ProductDetail = FString(UTF8_TO_TCHAR(charProductDetail));

		NewProduct = AndroidProductDetail_JsonParser(ProductDetail);

		UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call productDetails : %s"), *ProductDetail);

		jenv->ReleaseStringUTFChars(JavaProductDetail, charProductDetail);
		jenv->DeleteLocalRef(JavaProductDetail);

		ProvidedProductInformation.Add(NewProduct);

	}

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
	{
		UOneStoreIapProductDetailsFunction::StaticOneStoreIapGetProductDetails.Execute(RESULT_OK, ProvidedProductInformation);
		UOneStoreIapProductDetailsFunction::StaticOneStoreIapGetProductDetails.Unbind();
	}),
		TStatId(),
		nullptr,
		ENamedThreads::GameThread
		);
}

#endif

UOneStoreIapProductDetailsFunction::FStaticOneStoreIapProductDetails UOneStoreIapProductDetailsFunction::StaticOneStoreIapGetProductDetails;

