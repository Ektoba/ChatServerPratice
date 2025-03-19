// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MazeBlueprintLibrary.generated.h"

USTRUCT(BlueprintType)
struct FCell
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsVisited;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool TopWall;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool BottomWall;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool LeftWall;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool RightWall;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayerStartNum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsGoal;

    FCell()
    {
        IsVisited = false;
        TopWall = true;
        BottomWall = true;
        LeftWall = true;
        RightWall = true;
        PlayerStartNum = -1;
        IsGoal = false;
    }
};

UCLASS()
class CHATSERVERPRJ_API UMazeBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Maze")
    static void GenerateMaze(int32 Width, int32 Height, UPARAM(ref) TArray<FCell>& OutCells);
private:
    static void InitializeMaze(int32 Width, int32 Height, TArray<FCell>& Cells);
    static void GenerateMazeRecursive(int32 X, int32 Y, int32 Width, int32 Height, TArray<FCell>& Cells);
    static int32 GetIndex(int32 X, int32 Y, int32 Width);
    static bool IsValidCell(int32 X, int32 Y, int32 Width, int32 Height);
};
