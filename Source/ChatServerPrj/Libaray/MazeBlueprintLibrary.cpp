#include "MazeBlueprintLibrary.h"

void UMazeBlueprintLibrary::GenerateMaze(int32 Width, int32 Height, TArray<FCell>& OutCells)
{
    InitializeMaze(Width, Height, OutCells);

    // (0, 0)에서 시작 (랜덤 시작점을 원한다면 수정 가능)
    GenerateMazeRecursive(0, 0, Width, Height, OutCells);

    // 시작점과 목표 지점 설정 (예시)
    OutCells[0].PlayerStartNum = 0; // (0, 0)을 시작점으로
    OutCells[Width * Height - 1].IsGoal = true; // 마지막 셀을 목표로
}

void UMazeBlueprintLibrary::InitializeMaze(int32 Width, int32 Height, TArray<FCell>& Cells)
{
    Cells.Empty();
    Cells.SetNum(Width * Height); // Width x Height 크기로 셀 배열 설정
    // FCell 생성자에서 기본값이 이미 설정됨
}

void UMazeBlueprintLibrary::GenerateMazeRecursive(int32 X, int32 Y, int32 Width, int32 Height, TArray<FCell>& Cells)
{
    int32 CurrentIndex = GetIndex(X, Y, Width);
    if (!IsValidCell(X, Y, Width, Height) || Cells[CurrentIndex].IsVisited)
    {
        return;
    }

    Cells[CurrentIndex].IsVisited = true;

    // 방향 배열 (상, 하, 좌, 우)
    TArray<FIntPoint> Directions = {
        FIntPoint(0, -1), // 상
        FIntPoint(0, 1),  // 하
        FIntPoint(-1, 0), // 좌
        FIntPoint(1, 0)   // 우
    };

    // 방향을 랜덤으로 섞기
    Directions.Sort([](const FIntPoint& A, const FIntPoint& B) {
        return FMath::RandBool(); // 무작위 정렬
        });

    // 각 방향 탐색
    for (const FIntPoint& Dir : Directions)
    {
        int32 NewX = X + Dir.X;
        int32 NewY = Y + Dir.Y;
        int32 NewIndex = GetIndex(NewX, NewY, Width);

        if (IsValidCell(NewX, NewY, Width, Height) && !Cells[NewIndex].IsVisited)
        {
            // 현재 셀과 다음 셀 사이 벽 제거
            if (Dir.X == 1) // 오른쪽
            {
                Cells[CurrentIndex].RightWall = false;
                Cells[NewIndex].LeftWall = false;
            }
            else if (Dir.X == -1) // 왼쪽
            {
                Cells[CurrentIndex].LeftWall = false;
                Cells[NewIndex].RightWall = false;
            }
            else if (Dir.Y == 1) // 아래쪽
            {
                Cells[CurrentIndex].BottomWall = false;
                Cells[NewIndex].TopWall = false;
            }
            else if (Dir.Y == -1) // 위쪽
            {
                Cells[CurrentIndex].TopWall = false;
                Cells[NewIndex].BottomWall = false;
            }

            // 다음 셀로 재귀 호출
            GenerateMazeRecursive(NewX, NewY, Width, Height, Cells);
        }
    }
}

int32 UMazeBlueprintLibrary::GetIndex(int32 X, int32 Y, int32 Width)
{
    return Y * Width + X; // 2D 좌표를 1D 인덱스로 변환
}

bool UMazeBlueprintLibrary::IsValidCell(int32 X, int32 Y, int32 Width, int32 Height)
{
    return X >= 0 && X < Width && Y >= 0 && Y < Height;
}