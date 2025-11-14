# 딜리봇 MCU Firmware

> **2025-2학기 인천대학교 임베디드시스템공학과 캡스톤디자인 – 자율주행 로봇 딜리봇**  
> 이 레포지토리는 **딜리봇의 MCU(마이크로컨트롤러) 펌웨어 코드**를 담고 있습니다.

---

## 프로젝트 개요

딜리봇은 캠퍼스 내 자율주행을 목표로 하는 로봇 프로젝트입니다.  
이 레포지토리는 그중 **모터 제어, 센서 인터페이스, SBC와의 통신**을 담당하는 MCU 측 소스 코드를 관리합니다.

- 자율주행 로봇: Dillybot (딜리봇)
- 역할: 모터 제어, 저수준 하드웨어 제어, 통신 처리 등
- 보드: Nucleo-F446RE (STM32)

---

## 레포지토리 구성


```text
.
├── Core/
│   ├── Inc/
│   │   └── motor_driver.h
│   └── Src/
│       ├── main.c
│       └── motor_driver.c
└── README.md

```

## 주요 기능

### 1. UART를 활용한 Single Board Computer(SBC)와의 통신
- MCU ↔ SBC 간 **양방향 UART 통신**
- SBC (예: Raspberry Pi, Jetson 등)에서 생성한 **제어 명령 수신**
- 속도, 방향, 제어 모드 등의 정보를 **구조체 형태로 수신 및 처리**

---

### 2. HAL을 이용한 MCU 제어
- **STM32 HAL 라이브러리** 기반 하드웨어 제어
- 주요 HAL 함수 사용:
  - `HAL_UART_Transmit`, `HAL_UART_Receive_IT`를 이용한 **비동기 UART 통신**
  - `HAL_TIM_PWM_Start` 등을 활용한 **PWM 기반 모터 출력 제어**
- **GPIO 핀 제어**
  - 상태 LED 제어
  - 모터 드라이버 Enable 핀 제어 등
- **STM32CubeMX**로 생성한 초기화 코드를 기반으로 동작

---

### 3. MCU를 이용한 모터 드라이버 제어
- 모터 드라이버 (**Cytron MDD10A**)에 연결된 **PWM + 방향 제어 핀 제어**
- 주요 기능:
  - 좌/우 모터 속도 제어 (**전진 / 후진 / 정지**)
  - 회전 동작 (**좌회전 / 우회전**)
  - 제어 명령에 따른 **속도 비율 / 가중치 적용**
- 코드 구조:
  - `motor_driver.c`
  - `motor_driver.h`  
  → 드라이버 레벨 코드를 별도 모듈로 분리

---

## 시스템 구조 개요

```

+-----------------------+        UART        +----------------------+    PWM / DIR      +----------------------+
|  Single Board Computer| <----------------> |         MCU          | ----------------> |   Motor Driver       |
|  & Sensors            |                    |                      |                   +----------------------+
+-----------------------+                    +----------+-----------+               

                            
```

---

## 개발 환경
- MCU: STM32 Nucleo-F446RE
- IDE: STM32CubeIDE
- 통신: UART(115200 Baud, 8N1)
- MCU - SBC 연결: USART1

---

## 관련 레포지토리
- SBC / 자율주행 로직: https://github.com/embedded-ddookddaks/SBC
