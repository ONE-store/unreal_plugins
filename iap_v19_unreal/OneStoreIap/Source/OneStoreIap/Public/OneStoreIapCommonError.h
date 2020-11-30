// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OneStoreIapInterface.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

/**
 * 
 */
class ONESTOREIAP_API OneStoreIapCommonError
{

public:
	OneStoreIapCommonError();
	~OneStoreIapCommonError();

	static void(*StaticErrorHandle)(int);

};
