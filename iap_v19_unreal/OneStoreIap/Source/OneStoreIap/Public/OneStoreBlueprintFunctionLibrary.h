// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OneStoreBlueprintFunctionLibrary.generated.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

/**
 * 
 */
UCLASS()
class ONESTOREIAP_API UOneStoreBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "OneStore")
	static void OneStoreDisconnect();


	UFUNCTION(BlueprintCallable, Category = "OneStore")
	static bool OneStorePurchaseVerify(FString PublicKey, FString OriginalPurchaseData, FString SignatureData);

	UFUNCTION(BlueprintCallable, Category = "OneStore")
	static void OneStoreShowMessage(FString title, FString message);
	
};
