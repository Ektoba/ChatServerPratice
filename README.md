# ChatServerPratice
# 목적
* 객체 지향과 디자인 패턴을 적용
* RPC기능을 통해 Chat Multi게임 구현

# 기술스택
[![Stack](https://skillicons.dev/icons?i=cpp,visualstudio,unreal,git,github)](https://skillicons.dev)

# 프로젝트 소개
* ProjectName : ChatServerPratice
* Duration : 2025.03.10 ~ 2025.03.30
* YouTube : [https://studio.youtube.com/video/PYuHX_neIvk/edit](https://youtu.be/PYuHX_neIvk?si=sDcH4vzyM69B6znJ)
* Velog : https://velog.io/@buu1147/2025-03-28TIL-%EC%B1%84%ED%8C%85-%EC%95%BC%EA%B5%AC%EA%B2%8C%EC%9E%84-lnwf8vtr

# 개발환경
* C++
* Urneal
* GitKracen

# SourceTree
```cpp
| -- GameMode // 판정, 난수생성, 다음 턴 유저 관리
  | -- PlayerController // UI생성 및 전체 데이터 전송
  | -- GameState  //  Broadcast 기능, 현재 턴인 플레이어, 게임 시간 관리
  | -- PlayerState  //  남은 답 입력 회수, 승패 등 관리
  | -- UI
    |  --  ChatWindow  //  모든 위젯이 들어있다.
        |  --  Editable  //  채팅을 입력한다.
        |  --  ScroolBox  //  입력하거나 받은 채팅을 화면에 띄운다.
        |  --  UniformGrid  //  게임 상황을 기록한다.
```
