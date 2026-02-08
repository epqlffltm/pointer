# 컴파일러
CC = gcc

# 수정: -Wall (대문자), -O2 (숫자 0이 아닌 알파벳 O)
CFLAGS = -Wall -O2 -g

# 수정: wildcard 뒤에 한 칸 띄우기
SRCS = $(wildcard *.c)

# 확장자를 떼어내서 실행 파일 이름 목록 생성
TARGETS = $(SRCS:.c=)

# 'make'만 쳤을 때 모든 실행 파일을 만들도록 설정
all: $(TARGETS)

# 일반화된 규칙
# $@ : 타겟 이름
# $< : 첫 번째 의존성 파일
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# 파일 삭제
clean:
	rm -f $(TARGETS)