#define _CRT_SECURE_NO_WARNINGS
#include "pet_manager.h" 
#include <stdlib.h> 
#include <Windows.h> 

// 값이 초과하거나 음수 되면 설정
static void clamp_stat(int* value)
{
    if (*value > 100)
        *value = 100;
    if (*value < 0)
        *value = 0;
}

//구조체 변수 초기화
void create_animal(animal* a) {
    system("cls");
    a->health = 100;
    a->clean = 100;
    a->food = 100;

    printf("동물의 이름 : ");
    scanf("%30s", a->name);
    printf("동물의 나이 : ");
    scanf("%d", &a->age);
    printf("동물의 종 : ");
    scanf("%30s", a->species);
    printf("참고사항 : ");
    scanf("%50s", a->commit);
}

// 구조체들 출력
void display_info(animal** ani, int count, int day, int actions_today)
{
    system("cls");
    printf("=== Day %d / %d === (오늘 사용한 행동: %d/%d)\n", day, TURN, actions_today, ACTIONS_PER_DAY);
    printf("등록 된 동물 수 : %d \n\n", count);

    for (int i = 0; i < count; i++)
    {
        printf("[%d] %s (%s) | 나이:%d\n", i + 1, ani[i]->name, ani[i]->species, ani[i]->age);
        printf("  체력:%3d  배고픔:%3d  청결도:%3d\n", ani[i]->health, ani[i]->food, ani[i]->clean);
        printf("  참고사항: %s\n\n", ani[i]->commit);
    }
    system("pause");
}

// ****************행동 함수**********************
void play_with_animal(animal* target)
{
    target->health += 15;
    target->clean -= 20;
    target->food -= 15;
    clamp_stat(&target->health);
    clamp_stat(&target->clean);
    clamp_stat(&target->food);
    printf("%s와(과) 놀아주었습니다.\n", target->name);
}

void wash_animal(animal* target)
{
    target->clean += 20;
    target->health -= 5;
    target->food -= 10;
    clamp_stat(&target->health);
    clamp_stat(&target->clean);
    clamp_stat(&target->food);
    printf("%s를 깨끗하게 씻겼습니다.\n", target->name);
}

void feed_animal(animal* target)
{
    target->food += 25;
    target->health += 5;
    target->clean -= 5;
    clamp_stat(&target->health);
    clamp_stat(&target->clean);
    clamp_stat(&target->food);
    printf("%s에게 맛있는 식사를 제공했습니다.\n", target->name);
}


int select_animal(animal** ani, int count)
{
    if (count == 0)
    {
        printf("관리 중인 동물이 없습니다.\n");
        Sleep(1200);
        return -1;
    }

    for (int i = 0; i < count; i++)
    {
        printf("[%d] %s (%s)\n", i + 1, ani[i]->name, ani[i]->species);
    }

    int choice;
    printf("대상 동물 번호 선택 : ");
    scanf("%d", &choice);

    if (choice < 1 || choice > count)
    {
        printf("잘못된 번호입니다.\n");
        Sleep(1200);
        return -1;
    }
    return choice - 1; // 인덱스에 맞게
}

// Game over condition check
bool check_game_over(animal** ani, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (ani[i]->food == 0 || ani[i]->clean == 0 || ani[i]->health == 0)
        {
            printf("%s의 상태가 한계에 도달했습니다. 보호 실패...\n", ani[i]->name);
            Sleep(1500);
            return true; 
        }
    }
    return false; 
}

// file I/O
void save_animals(animal** ani, int count)
{
    FILE* fp = fopen(SAVE_PATH, "w");
    if (fp == NULL) {
        printf("경고: 파일 저장에 실패했습니다.\n");
        return;
    }

    fprintf(fp, "===== 보호 동물 현황 (%d마리) =====\n\n", count);
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "[%d] 이름:%s 종:%s 나이:%d\n", i + 1, ani[i]->name, ani[i]->species, ani[i]->age);
        fprintf(fp, "  체력:%d 배고픔:%d 청결:%d 참고:%s\n\n", ani[i]->health, ani[i]->food, ani[i]->clean, ani[i]->commit);
    }
    fclose(fp);
}

// 메모리 해제
void free_all(animal** ani, int count)
{
    for (int i = 0; i < count; i++)
        free(ani[i]);
}