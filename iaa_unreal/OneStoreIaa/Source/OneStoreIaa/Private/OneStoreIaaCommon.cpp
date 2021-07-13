// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreIaaCommon.h"

OneStoreIaaCommon::OneStoreIaaCommon() {
}

OneStoreIaaCommon::~OneStoreIaaCommon()
{
}


#if PLATFORM_ANDROID
extern "C" void Java_com_gaa_sdk_iaa_AdsNativeCallback_nativeOnIaaResultResponse(JNIEnv* jenv, jobject thiz, jint responseCode, jstring message, jlong futureHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call Java_com_gaa_sdk_iaa_AdsNativeCallback_nativeOnIaaResultResponse"));
	OneStoreIaaCommon::StaticErrorHandle((int)responseCode);
}
#endif

void(*OneStoreIaaCommon::StaticErrorHandle)(int errorCode);


