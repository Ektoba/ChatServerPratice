#include "ChatGameState.h"
#include "ChatController.h"
AChatGameState::AChatGameState()
{
}
void AChatGameState::BroadcastMessage_Implementation(const FString& SenderName, const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("Call BroadcastMessage"));
	if (UWorld* World = GetWorld())
	{
		if (AChatController* Controller = Cast<AChatController>(World->GetFirstPlayerController()))
		{
			Controller->ReceiveMessage(SenderName, Message);
		}
	}
}
void AChatGameState::BeginPlay()
{
	Super::BeginPlay();
}
