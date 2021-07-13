// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OneStoreIaaInterface.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

/**
 * 
 */
class ONESTOREIAA_API OneStoreIaaCommon
{

public:
	OneStoreIaaCommon();
	~OneStoreIaaCommon();

	static void(*StaticErrorHandle)(int);

};
