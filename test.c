#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    void* base;       // 전체 땅의 시작 주소
    void* next_free;  // 다음에 빌려줄 땅의 시작 주소
    size_t capacity;  // 전체 크기
    size_t used;      // 지금까지 빌려준 크기
} MemoryPool;

// 1. 메모리 풀 초기화: 미리 큰 땅을 사둡니다.
MemoryPool* create_pool(size_t size) 
{
    MemoryPool* pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    pool->base = malloc(size); // 여기서 딱 한 번만 malloc 실행!
    pool->next_free = pool->base;
    pool->capacity = size;
    pool->used = 0;
    return pool;
}

// 2. 할당(My_Alloc): 포인터 연산으로 땅을 잘라줍니다.
void* my_alloc(MemoryPool* pool, size_t size) 
{
    // 남은 공간이 있는지 확인
    if (pool->used + size > pool->capacity) 
    {
        printf("Error: 메모리 풀이 꽉 찼습니다!\n");
        return NULL;
    }

    void* allocated_ptr = pool->next_free; // 현재 빈 곳의 주소를 기억해둠
    
    // 포인터 기행: 다음 빈 주소는 현재 주소 + 요청한 사이즈
    // (char*)로 형변환하는 이유는 주소값을 1바이트 단위로 정확히 더하기 위해서입니다.
    pool->next_free = (char*)pool->next_free + size; 
    pool->used += size;

    return allocated_ptr; // 잘라낸 땅의 시작 주소를 반환
}

int main(void) 
{
    // 100바이트짜리 풀 생성
    MemoryPool* my_pool = create_pool(100);
    printf("풀 시작 주소: %p\n", my_pool->base);

    // 정수형(int) 공간 빌리기
    int* p1 = (int*)my_alloc(my_pool, sizeof(int));
    *p1 = 123;
    printf("p1 주소: %p, 값: %d\n", p1, *p1);

    // 문자열(char[10]) 공간 빌리기
    char* p2 = (char*)my_alloc(my_pool, 10);
    printf("p2 주소: %p (p1으로부터 %ld바이트 뒤)\n", p2, (char*)p2 - (char*)p1);

    free(my_pool->base); // 마지막에 전체 땅 반납
    free(my_pool);
    return 0;
}