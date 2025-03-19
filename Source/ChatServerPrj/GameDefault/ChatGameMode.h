#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChatGameMode.generated.h"

UCLASS()
class CHATSERVERPRJ_API AChatGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AChatGameMode();
protected:
	virtual void BeginPlay() override;
};
