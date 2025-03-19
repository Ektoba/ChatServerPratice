#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatWindow.generated.h"

UCLASS()
class CHATSERVERPRJ_API UChatWindow : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* ChattingInput;
	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	class UScrollBox* ChatMessageBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> ChatMessageClass;
protected:
	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
protected:
	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintCallable)
	void AddMessage(const FString& Sender, const FString& Message);
};
