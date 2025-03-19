#include "ChatWindow.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Styling/SlateTypes.h"
#include "Engine/GameViewportClient.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../GameDefault/ChatController.h"
#include "GameUIBase.h"
void UChatWindow::NativeConstruct()
{
    Super::NativeConstruct();

	if (IsValid(ChattingInput))
	{
        ChattingInput->OnTextCommitted.AddDynamic(this, &UChatWindow::OnTextCommitted);
	}    
}

void UChatWindow::AddMessage(const FString& Sender, const FString& Message)
{
    UGameUIBase* MessageWidget = CreateWidget<UGameUIBase>(GetWorld(), ChatMessageClass);
    MessageWidget->SendMessage = FText::FromString(FString::Printf(TEXT("%s : %s"), *Sender, *Message));
    ChatMessageBox->AddChild(MessageWidget);
}

void UChatWindow::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
    switch (CommitMethod)
    {
    case ETextCommit::Default:
        UE_LOG(LogTemp, Log, TEXT("Commit Type: Default"));
        break;
    case ETextCommit::OnEnter:
        if (!Text.IsEmpty())
        {
            ChattingInput->SetText(FText::FromString(TEXT("")));
            if (IsValid(ChatMessageClass))
            {
                UGameUIBase* MessageWidget = CreateWidget<UGameUIBase>(GetWorld(), ChatMessageClass);
                MessageWidget->SendMessage = Text;
                //  서버로 메시지 전송
                if (AChatController* Cont = Cast<AChatController>(GetOwningPlayer()))
                {
                    Cont->SendServerMessage(Cont, Text.ToString());
                }
            }
        }
        else
        {
            UWidgetBlueprintLibrary::SetFocusToGameViewport();
        }
        break;
    case ETextCommit::OnUserMovedFocus:
        UE_LOG(LogTemp, Log, TEXT("Commit Type: OnUserMovedFocus"));
        break;
    case ETextCommit::OnCleared:
        UE_LOG(LogTemp, Log, TEXT("Commit Type: OnCleared"));
        break;
    }
}
