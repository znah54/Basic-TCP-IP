## 1일차

- TCP(Transmission Control Protocol, TCP)
    - 전송방식(일방향 UDP, 양방향 TCP)
    - 전송 제어 프로토콜, 전송계층에 속한다. 네트워크의 정보 전달 통제 프로토콜
    - OSI7 Layer 4계층, TCP가 실을 수 있는 데이터 -> 세그먼트(Segment)

    ※  소 -> 소켓(socket)
        말 -> 바인더(binder)
        리 -> 리슨(Listen)
        아 -> 아댑터(adapter)

    - 3-way handshake

  ![TCP001](https://github.com/znah54/Basic-TCP-IP/assets/50408406/88cb4cb9-64bd-46b6-aa3b-2437f778759c)

    - 송수신자 확인 뒤 데이터를 주고 받음

- IP란?? => Internet Protocol 인터넷에 연결되어 있는 모든 장치들을 식별할 수 있도록 각 장비에 부여되는 고유주소!
    - IPv4, IPv6, Subnet Mask, Gateway, DNS

- 프로토콜(Protocol) => 대화에 필요한 통신규약
    - PF_INET = IPv4 인터넷 프로토콜 체계! <사실상 이것만 알면 됨>

- 소켓(Socket)
    - TYPE 
        - 연결지향형 소켓(SOCK_STREAM)
        - 비 연결지향형 소켓(SOCK_DGRAM)
 
## 2일차

- OSI-7 Layer(계층)
    - LINK 계층 - LAN, WAN, MAN 프로토콜 정의 영역
    - IP 계층 - 비 연결지향적 신뢰할 수 없는 프로토콜, 데이터를 전송할 때마다 거쳐야 할 경오를 선택, 그 경로는 일정치 않음
    - TCP/UDP 계층 - 전송계층으로 위의 TCP와 UDP의 차이로 설명가능

<img src=https://github.com/znah54/Basic-TCP-IP/blob/main/images/TCP002.png>


## 3일차

- TCP 기반 Half-close
    - TCP에서는 연결과정보다 중요한 것은 종료과정 
    - Half-close
    1) 일반종료
    2) 완전종료

- 소켓, 스트림
    - 스트림 : 송수신이 가능한 상태를 일종의 스트림, 물의 흐름
    - 소켓 : 양한쪽 방햐응로만 데이터 이동 가능
    - 즉 양방햐을 위해서는 두개의 스트림이 필요함

- 연결지향형 소켓(SOCK_STREAM)의 데이터 전송 특성 
    - 중간에 데이터 소멸되지 않는다. 
    - 전송 순서대로 데이터가 수신된다. 
    - 데이터의 경계가 존재하지 않는다. 
    - 소켓 대 소켓의 연결은 반드시 1대 1의 구조.
- 비 연결지향형 소켓(SOCK_DGRAM)의 데이터 전송특성 
    - 전송순서 상관없이 빠른 속도의 전송을 지향 
    - 데이터 손실 및 파손의 우려있다. 
    - 데이터의 경계가 존재한다. 
    - 한번에 전송할 수 있는 데이터의 크기가 제한된다.


- DNS(Domain Name System)

<img src=https://github.com/znah54/Basic-TCP-IP/blob/main/images/TCP003.png>


- 소켓의 다양한 옵션

<img src=https://github.com/znah54/Basic-TCP-IP/blob/main/images/TCP004.png>

- 프로세스 : 컴퓨터에서 실행중인 프로그램

## 4일차

- 멀티태스킹 다중접속 서버
    - 에코서버
    1) 에코 서버(부모 프로세스)는 accept 함수호출을 통해서 연결요청을 수락한다.
    2) 이때 얻게 되는 소켓의 파일 디스크립터를 자식 프로세스를 생성해서 넘겨준다.
    3) 자식 프로세스는 전달받은 파일 디스크립터를 바탕으로 서비스를 제공한다.

## 5일차

- 다중서버
    - 멀티플렉싱 select
    - 멀티스레드 fork

- 쓰레드
    - 멀티프로세스 : 프로세스 생성이라는 부담스러운 작업과정을 거친다, 두 프로세스 사이에서의 데이터교환을 위해서는 별도의 IPC 기법을 적용해야 한다.

- 쓰레드 프로세스 차이점
    - 프로르세 > 힙, 스택
    - 즉, 프로스세 : 운영체제 관점에서 별도의 실행흐름을 구성하는단위
    쓰레드 : 프로세스 관점에서 별도의 실행흐름을 구성하는 단위

- 쓰레드의 문제점과 임계영역



## 시험
- 웹페이지 구성(라즈베리 파이, 사진 케릭터 그런 사진 하나 다운로드 띄워보기) - 단순접속 멀티프로세스 사용한다던지, 멀티 플렉싱, 멀티 쓰레드 서버 동작시키기 인터넷 통해서 주소창 라즈베리 통해 들어가니 웹서버 구현

char webpage[] = "HTTP/1.1 200 OK\r\n"
			"Server:Linux Web Server\r\n"
			"Content-Type: text/htm; charset=UTF-8\r\n\r\n"
            "<!DOCTYPE html>\r\n"
            "<html><head><title> My Web Page </title>\r\n"
            "<style>body {background-color: #FFFF00}</style><head>\r\n"
            "<body><center><h1>Hello world!!</h1><br>\r\n"
            "<img src=\"cat.jpg\"></center></body></html>\r\n"

