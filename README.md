# RainyDay
시프실 프로젝트입니다.

# waterpump.c 소개

Main Device에 작동 여부를 요청하고, 응답 값을 바탕으로 워터펌프를 작동시키는 코드

# waterpump.c 컴파일방법

``` sh

    gcc -o waterpump waterpump.c -lwiringPi -ljson-c

```

# waterpump.c 실행방법

``` sh

    ./waterpump

```

# waterlevel.c 소개

수위센서를 작동시켜 센서값을 디지털 값으로 변환한 후, Main Device에 전송하는 코드

# waterlevel.c 컴파일방법

``` sh

gcc -o waterlevel watelevel.c -ljson-c

```

# waterlevel.c 실행방법

``` sh

./waterlevel

```
