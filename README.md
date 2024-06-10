# RainyDay
시프실 프로젝트입니다.

# waterpump.c 소개

서버에 작동 여부를 요청하고, 응답 값을 바탕으로 워터펌프를 작동시키는 코드

# waterpump.c 컴파일방법

    gcc -o waterpump waterpump.c -lwiringPi -ljson-c

# waterpump.c 실행방법

    ./waterpump


# waterlevel.c 소개

수위센서를 작동시켜서 센서값을 디지털로 변환한뒤, 서버에 전송하는 코드

# waterlevel.c 컴파일방법

    gcc -o waterlevel watelevel.c -ljson-c

# waterlevel.c 실행방법

    ./waterlevel
