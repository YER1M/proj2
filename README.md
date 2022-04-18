# 장애물 긴급 회피 시스템
### 1. 요구사항
1. 초음파센서를 통한 전방 차량 상대거리 감지
* 초음파센서 5,10,25,50[cm]의 구간으로 상대거리  구분

2. DC 모터를 이용한 좌우 바퀴 속도 제어
* 전방 차량과의 좌,우측 상대거리비교를 통한 DC 모터 속도 제어
* PWM Duty 조절-구간별 20%감소

3. 상위 제어기와 하위 제어기 보드연결
* GPIO Setting을 통해서 여러 보드 연결
* 보드 개수: 최소 2, 최대 3

4. 가변저항을 이용한 시동 ON/OFF
* 가변 저항 입력값< 1500 -> OFF
* 가변 저항 입력값>= 1500 -> ON

5. 부저를 이용한 앞 차량 간격 거리 구간 별 경고음 조절
* 앞 차량과의 간격 거리 간격에 따라서 경고음 간격 조절(Delay 이용)

6. LED를 이용한 앞차량 간격 거리 구간 별 경고등 점등 간격 조절
* 앞 차량과의 간격 거리 간격에 따라서 경고음 간격 조절(Delay 이용)

7. 스위치  입력을 통한 차량 모드 제어
* SW1 ON -> LED Only
* SW2 ON -> LED & Buzzer
* SW -> GPIO로 제어

8. RGB를 색을 통해 차량 모드 표시
* 빨강 ->시동 OFF
* 노랑 ->시동 ON
* 파랑 ->LED & 초음파
* 초록 ->LED & 초음파 & Buzzer ON

### 2. 범준(PL)


### 3. 재현


### 4. 예림


### 5. 진호

