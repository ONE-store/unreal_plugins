﻿/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#pragma once

#include "ONEstoreALCBase.h"
#include "ONEstoreALCQueryLicenseAsync.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/


UCLASS(MinimalAPI)
class UONEstoreALCQueryLicenseAsync : public UONEstoreALCAsyncBase
{
	GENERATED_UCLASS_BODY()
			
	UPROPERTY(BlueprintAssignable)
	FOnResult	OnGranted;
	UPROPERTY(BlueprintAssignable)
	FOnResult	OnDenied;
	UPROPERTY(BlueprintAssignable)
	FOnResult	OnError;
	UPROPERTY(BlueprintAssignable)
	FOnResult	OnNeedLogin;	// 10
	UPROPERTY(BlueprintAssignable)
	FOnResult	OnNeedUpdate;	// 11
	

	virtual void Activate() override;
	
private:
	void OnCompleted(const int32&, const FString&, const FString&, const FString&);	

protected:
	UFUNCTION(BlueprintCallable, Category = "ONEstore|ALC",
		meta = (BlueprintInternalUseOnly = "true", WorldContext = "pWorld"))
	static UONEstoreALCQueryLicenseAsync* QueryLicenseAsync( const UObject* pWorld, const FString& publicKey );	
};