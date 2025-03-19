#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChatController.generated.h"

UCLASS()
class CHATSERVERPRJ_API AChatController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UChatWindow> ChatWindowClass;
	//TSoftClassPtr<class UChatWindow> ChatWindowClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<class UChatWindow> ChatWindowInstance;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FString ControllerID;
public:
	UFUNCTION(Client, Reliable)
	void ReceiveMessage(const FString& SenderName,const FString& Message);
	UFUNCTION(Server, Reliable)
	void SendServerMessage(APlayerController* Sender, const FString& Message);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FString GetUserID() const;
protected:
	virtual void BeginPlay() override;
	bool IsServer();
};
