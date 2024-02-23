/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPSwitchPID.h"

UONEstoreIAPSwitchPID::UONEstoreIAPSwitchPID(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


FString UONEstoreIAPSwitchPID::SwitchPID( FString pid )
{
	return (pid.Len() == 11) ? pid.Append( "0" ) : pid.Left(11);
}