// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ChatGameState.generated.h"

DECLARE_DELEGATE(Test)
UCLASS()
class CHATSERVERPRJ_API AChatGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AChatGameState();
public:
	//	NetMultiCast는 서버에서 클라이언트에게 브로드캐스트를 하기 위한 지정자
	UFUNCTION(NetMulticast, Reliable)
	void BroadcastMessage(const FString& SenderName, const FString& Message);
	Test testDelegate;
protected:
	virtual void BeginPlay() override;
};
