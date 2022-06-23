#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

struct Table {
    int size;
    int* p;
};

struct Input {
    int sum;
    int highest;
};

struct IntList {
    int idx;
    int number;
    IntList* next;
};


void scenario();
Table* create_prime_table(int max);
int fill_sieve(char* sieve, int max);
void fill_prime_table(int* prime_table, char* sieve, int max);
void divide_into_primes(int a, Table* prime, int pos, IntList** first, int max);
Input* get_input();
int list_print(IntList* first, Table* prime);
IntList** list_add(IntList** first, int number, int idx);
IntList** list_pop(IntList** first, int pos);
bool check_exeption(Input* input);
void print_result(Table* prime, IntList* first, int i, int k, int pos);

int main()
{
    int a;
    scanf("%d", &a);
    while (a) {
        scenario();
        a--;
    }
    return 0;
}

void scenario() {
    Input* input = get_input();
    if (input == NULL)return;
    Table* prime = create_prime_table(input->highest);
    IntList* first = NULL;
    if (!check_exeption(input)) {
        divide_into_primes(input->sum - input->highest, prime, 1, &first, prime->size);
    }
}

bool check_exeption(Input* input) {
    if (input->highest == 2) {
        int k = input->sum - input->highest;
        if (k % 2 == 0) {
            std::cout << input->highest;
            for (int i = 0; i < k / 2; k++) {
                std::cout << "+" << 2;
            }
            std::cout << "\n";
        }
        return true;
    }
    else return false;
}

Table* create_prime_table(int max) {
    char* sieve = NULL;
    sieve = (char*)malloc(sizeof(char) * (max + 1));
    if (sieve == NULL)return NULL;
    int prime_n = fill_sieve(sieve, max);

    Table* prime = NULL;
    prime = (Table*)malloc(sizeof(Table));
    prime->p = (int*)malloc(sizeof(int) * prime_n);
    if (prime == NULL or prime->p == NULL)return NULL;

    fill_prime_table(prime->p, sieve, max);
    prime->size = prime_n;
    return prime;
}

int fill_sieve(char* sieve, int max) {
    sieve[0] = 1;  sieve[1] = 1;
    for (int i = 2; i < max + 1; i++) {
        sieve[i] = 0;
    }
    int prime_n = 0;
    for (int i = 2; i < max + 1; i++) {
        if (sieve[i] == 0) {
            prime_n++;
            if (i < sqrt(max)) {
                for (int j = i + i; j < max; j += i) {
                    sieve[j] = 1;
                }
            }
        }
    }
    return prime_n;
}

void fill_prime_table(int* prime_table, char* sieve, int max) {
    int j = 0;
    for (int i = 0; i <= max; i++) {
        if (sieve[i] == 0) {
            prime_table[j++] = i;
        }
    }
}

Input* get_input() {
    Input* input = NULL;
    input = (Input*)malloc(sizeof(Input));
    if (input == NULL)return NULL;
    scanf("%d%d", &input->sum, &input->highest);
    return input;
}

void divide_into_primes(int a, Table* prime, int pos, IntList** first, int max) {
    int i = 1;
    int k;
    while (a - prime->p[pos] * i >= 0) {
        k = a - prime->p[pos] * i;
        if (k % 2 == 0) {
            print_result(prime, *first, i, k, pos);
        }
        if (pos > 1) {
            first = list_add(first, i, pos);
            divide_into_primes(k, prime, 1, first, pos);
        }
        i++;
    }
    first = list_pop(first, pos);
    if (pos + 1 < max) {divide_into_primes(a, prime, pos + 1, first, max);}
}

IntList** list_add(IntList** first, int number, int idx) {
    if (*first == NULL) {
        *first = (IntList*)malloc(sizeof(IntList));
        (*first)->idx = idx;
        (*first)->number = number;
        (*first)->next = NULL;
        return first;
    }
    if ((*first)->idx == idx) {
        (*first)->number = number;
        return first;
    }
    IntList* current = *first;
    while (current->next != NULL){
        current = current->next;
        if (current->idx == idx) {
            current->number = number;
            return first;
        }
    }
    IntList* new_element = (IntList*)malloc(sizeof(IntList));
    new_element->idx = idx;
    new_element->number = number;
    new_element->next = NULL;
    current->next = new_element;
    return first;
}

IntList** list_pop(IntList** first, int pos) {
    if (*first == NULL)return first;
    IntList* current = *first;
    IntList* prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    if (current->idx <= pos) {
        free(current);
        if (prev == NULL) *first = NULL;
        else prev->next = NULL;
    }
    return first;
}

int list_print(IntList* first, Table* prime) {
    IntList* current = first;
    int check = 0;
    while (current != NULL) {
        for (int i = 0; i < current->number; i++) {
            std::cout << "+" << prime->p[current->idx];
            check += prime->p[current->idx];
        }
        current = current->next;
    }
    return check;
}

void print_result(Table* prime, IntList* first, int i, int k, int pos) {
    int check = prime->p[prime->size - 1];
    std::cout << prime->p[prime->size - 1];
    check += list_print(first, prime);
    for (int j = 0; j < i; j++) {
        std::cout << "+" << prime->p[pos];
        check += prime->p[pos];
    }
    for (int j = 0; j < k / 2; j++) {
        std::cout << "+" << prime->p[0];
        check += prime->p[0];
    }
    std::cout << "[ " << check << " ]";
    std::cout << "\n";
}