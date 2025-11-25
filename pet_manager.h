
#ifndef PET_MANAGER_H
#define PET_MANAGER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_ANIMAL 100
#define TURN 7
#define ACTIONS_PER_DAY 2
#define SAVE_PATH "pet_records.txt"

typedef struct
{
    int age;
    char name[31];
    char species[31];
    char commit[51];
    int food;
    int clean;
    int health;
} animal;

void create_animal(animal* a);

// Action function
void play_with_animal(animal* target);
void wash_animal(animal* target);
void feed_animal(animal* target);

// Print information
void display_info(animal** ani, int count, int day, int actions_today);

// Action function 호출 시 호출
int select_animal(animal** ani, int count);

// event 처리 후 계속 호출
bool check_game_over(animal** ani, int count);

// 파일에 저장 / 메모리 해제
void save_animals(animal** ani, int count);
void free_all(animal** ani, int count);

#endif 