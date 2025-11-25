#define _CRT_SECURE_NO_WARNINGS
#include "pet_manager.h"
#include <Windows.h>
#include <time.h>
#include <stdio.h>
//룰 :
// 일주일 진행
// 동물 추가 될 수록 알바비 증가
// 각 행동들은 2번 진행 시 하루 지남

int main(void) {
    animal* pet[MAX_ANIMAL] = { 0 }; // animal을 가리키는 포인터 배열
    int pet_count = 0;
    int day = 1;
    int actions_today = 0;
    int salary = 0;
    bool game_end = false;

    while (day <= TURN)
    {
        system("cls");
        printf("*******[ Pet Manager Program ]*******\n");
        printf("Day %d / %d  |  오늘 행동 %d / %d\n", day, TURN, actions_today, ACTIONS_PER_DAY);
        printf("등록된 동물: %d마리\n\n", pet_count);
        printf("[1] 등록하기\n");
        printf("[2] 놀기\n");
        printf("[3] 씻기기\n");
        printf("[4] 먹이 주기\n");
        printf("[5] 정보 보기\n");
        printf("[0] 종료\n\n");
        printf("입력 : ");

        int input;
        scanf("%d", &input);

        if (input == 0)
        {
            printf("종료를 선택했습니다.\n");
            salary = 0;
            break;
        }

        int action_consumed = 0;

        switch (input)
        {
        case 1:
            if (pet_count >= MAX_ANIMAL)
            {
                printf("더 이상 동물을 등록할 수 없습니다.\n");
                Sleep(1200);
                break;
            }
            pet[pet_count] = (animal*)malloc(sizeof(animal));

            create_animal(pet[pet_count]);
            pet_count++;

            save_animals(pet, pet_count);
            printf("등록 완료!\n");
            Sleep(1200);
            break;

        case 2:
        {
            int idx = select_animal(pet, pet_count);
            if (idx >= 0)
            {
                play_with_animal(pet[idx]);
                action_consumed = 1;
            }
            Sleep(1200);
            break;
        }
        case 3:
        {
            int idx = select_animal(pet, pet_count);
            if (idx >= 0)
            {
                wash_animal(pet[idx]);
                action_consumed = 1;
            }
            Sleep(1200);
            break;
        }
        case 4:
        {
            int idx = select_animal(pet, pet_count);
            if (idx >= 0)
            {
                feed_animal(pet[idx]);
                action_consumed = 1;
            }
            Sleep(1200);
            break;
        }
        case 5:
            display_info(pet, pet_count, day, actions_today);
            break;

        default:
            printf("잘못된 입력입니다.\n");
            Sleep(1000);
            break;
        }

        if (game_end)
            break;

        if (action_consumed)
        {
            actions_today++;
            save_animals(pet, pet_count);
            //당일 행동 가능 횟수 넘으면 하루 넘기고 행동 횟수 초기화
            if (actions_today >= ACTIONS_PER_DAY)
            {
                day++;
                actions_today = 0;
            }
        }

        if (check_game_over(pet, pet_count))
        {
            salary = 0;
            game_end = true;
            break;
        }
    }

    if (!game_end && day > TURN)
    {
        salary = pet_count * 10000;
        printf("\n일주일 간의 보호를 마쳤습니다!\n");
        printf("남아있는 동물 %d마리 기준 급여: %d원\n", pet_count, salary);
    }
    else if (!game_end && day <= TURN)
    {
        printf("\n게임이 중단되었습니다.\n");
    }
    else
    {
        printf("\n관리 실패로 급여는 0원입니다.\n");
    }
    save_animals(pet, pet_count);
    free_all(pet, pet_count);
    system("pause");
    return 0;
}