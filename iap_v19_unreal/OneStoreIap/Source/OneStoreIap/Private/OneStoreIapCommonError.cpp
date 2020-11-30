// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIapCommonError.h"

OneStoreIapCommonError::OneStoreIapCommonError() {
}

OneStoreIapCommonError::~OneStoreIapCommonError()
{
}


#if PLATFORM_ANDROID
extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnIapResultResponse(JNIEnv* jenv, jobject thiz, jint responseCode, jstring message, jlong futureHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnIapResultResponse"));
	OneStoreIapCommonError::StaticErrorHandle((int)responseCode);
}

extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnNeedUpdate(JNIEnv* jenv, jobject thiz)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnNeedUpdate"));
	OneStoreIapCommonError::StaticErrorHandle(RESULT_NEED_UPDATE);
}

extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnNeedLogin(JNIEnv* jenv, jobject thiz)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnNeedLogin"));
	OneStoreIapCommonError::StaticErrorHandle(RESULT_NEED_LOGIN);
}

extern "C" void Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnServiceDisconnected(JNIEnv* jenv, jobject thiz)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_unreal_plugin_iap_PurchaseClientNativeCallback_nativeOnServiceDisconnected"));
	OneStoreIapCommonError::StaticErrorHandle(RESULT_SERVICE_UNAVAILABLE);
}
#endif

void(*OneStoreIapCommonError::StaticErrorHandle)(int errorCode);


