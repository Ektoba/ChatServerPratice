#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChatGameMode.generated.h"

USTRUCT(BlueprintType)
struct FBaseballResult
{
	GENERATED_BODY()
	int32 StrikeCount;
	int32 BallCount;
	bool Out;
};
UCLASS()
class CHATSERVERPRJ_API AChatGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	TArray<int32> NumArray;
	TArray<int32> SystemAnswer;
protected:
	virtual void BeginPlay() override;
protected:
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	FBaseballResult ServerBaseballResult(const TArray<int32>& Answer);
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	bool AnswerCheck(const FText& Answer);
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	TArray<int32> SplitAnswer(const FText& Answer);
public:
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	FBaseballResult SendAnswer(const FText& Answer);
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	FText MakeMessage(const FBaseballResult& Result);
};
