#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIBase.generated.h"

UCLASS()
class CHATSERVERPRJ_API UGameUIBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = "Message"))
	FText SendMessage;
};
