﻿/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#pragma once

#include "ONEstoreIapBase.h"
#include "ONEstoreIAPManageRecurringProductAsync.generated.h"

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
class UONEstoreIAPManageRecurringProductAsync : public UONEstoreIAPAsyncBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnRecurringState	OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FOnRecurringState	OnFailure;
	UPROPERTY(BlueprintAssignable)
	FOnRecurringState	OnNeedUpdate;
	UPROPERTY(BlueprintAssignable)
	FOnRecurringState	OnNeedLogin;

	virtual void Activate() override;
	
protected:
	UFUNCTION(BlueprintCallable, Category = "ONEstore|IAP",
		meta = (BlueprintInternalUseOnly = "true", WorldContext = "pWorld"))
	static UONEstoreIAPManageRecurringProductAsync* ManageRecurringProductAsync(
		const UObject* pWorld,
		const FONEstorePurchaseData& data, const EONEstoreRecurringState recurringState );


private:
	FONEstorePurchaseData	m_data;
	EONEstoreRecurringState	m_state;
	void OnCompleted( const int32& code, const FString& message, 
					  const FONEstorePurchaseData& data, const EONEstoreRecurringState& recurringState);

};
