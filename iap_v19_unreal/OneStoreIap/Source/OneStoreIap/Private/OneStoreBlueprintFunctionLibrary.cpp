// Fill out your copyright notice in the Description page of Project Settings.


#include "OneStoreBlueprintFunctionLibrary.h"

void UOneStoreBlueprintFunctionLibrary::OneStoreDisconnect()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAAEndConnection", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
#endif
}

bool UOneStoreBlueprintFunctionLibrary::OneStorePurchaseVerify(FString publicKey, FString originalPurchaseData, FString signatureData) {
	bool ret = false;
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JavapublicKey = Env->NewStringUTF(TCHAR_TO_UTF8(*publicKey));
		jstring JavaOriginalPurchaseData = Env->NewStringUTF(TCHAR_TO_UTF8(*originalPurchaseData));
		jstring JavaSignatureData = Env->NewStringUTF(TCHAR_TO_UTF8(*signatureData));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAAVerify", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", false);
		ret = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method, JavapublicKey, JavaOriginalPurchaseData, JavaSignatureData);
		
		Env->DeleteLocalRef(JavapublicKey);
		Env->DeleteLocalRef(JavaOriginalPurchaseData);
		Env->DeleteLocalRef(JavaSignatureData);
	}
#endif
	return ret;
}

void UOneStoreBlueprintFunctionLibrary::OneStoreShowMessage(FString title, FString message) {
	UE_LOG(LogTemp, Warning, TEXT("[UE4] = Call OneStoreShowMessage Title : %s, Message : %s"), *title, *message);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JavaTitle = Env->NewStringUTF(TCHAR_TO_UTF8(*title));
		jstring JavaMessage = Env->NewStringUTF(TCHAR_TO_UTF8(*message));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidTrunkJava_GAAAlertDialog", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaTitle, JavaMessage);

		Env->DeleteLocalRef(JavaTitle);
		Env->DeleteLocalRef(JavaMessage);
	}
#endif
}



