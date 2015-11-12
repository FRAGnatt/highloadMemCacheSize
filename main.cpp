//
//  main.cpp
//  highload
//
//  Created by Константин Забродин on 08.11.15.
//  Copyright © 2015 Константин Забродин. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <fstream>
#include <cstring>
#include <math.h>

struct List_t  //Структура с инфополями и адресным полем
{
    int x;
    List_t *next; //Адресное поле
};

List_t * deletelem(List_t *lst) {
    List_t *temp;
    temp = lst;
    while(temp->next != lst) // просматриваем список начиная с корня
    { // пока не найдем узел, предшествующий lst
        temp = temp->next;
    }
    temp->next = lst->next; // переставляем указатель
    lst->next = nullptr;
    return lst;
}

int COUNT_ELEMENT = 100;

List_t * shuffle(List_t *first_item) {
    
    List_t *newList;
    List_t *firstItemNewList;
    
    List_t *oldList = first_item->next;
    List_t *buf;
    
    newList = first_item;
    firstItemNewList = newList;
    
    deletelem(first_item);
    
    for(int i = 1; i < COUNT_ELEMENT; i++){
        for (int i = 0; i < (rand() % COUNT_ELEMENT); i++) {
            oldList = oldList->next;
        }
        buf = oldList->next;
        newList->next = deletelem(oldList);
        oldList = buf;
        newList = newList->next;
    }
    
    newList->next = firstItemNewList;
    return newList;
}


int main()
{
    std::ofstream file;
    
    for (int i = 0; i < 100; i++) {
//        if (i < 87) {
//            COUNT_ELEMENT = COUNT_ELEMENT + COUNT_ELEMENT/10;
//            continue;
//        }
        COUNT_ELEMENT = COUNT_ELEMENT + COUNT_ELEMENT/10;
        List_t *el = new List_t();
        List_t *first = el;
        
        for (int i = 0; i < COUNT_ELEMENT-1; i++) {
            el->x = i;
            el->next = new List_t();
            el = el->next;
        }
        
        el->x = 9;
        el->next = first;
        
        const int sizeOfElementOfList = sizeof(el);
        
        for (int i = 0; i < COUNT_ELEMENT; i++) {
            //        std::cout << el->x;
            el = el->next;
        }
        
        el = shuffle(first);
        
        double start_time;
        double end_time;
        double avg_time;
        
        start_time = clock();
        
        unsigned int countCycle = COUNT_ELEMENT*10;
        
        for (int i = 0; i < countCycle; i++) {
            el = el->next;el = el->next;el = el->next;el = el->next;el = el->next; // 5 раз
            
        }
        
        end_time = clock();
        
        avg_time = (end_time - start_time) / (5 * (countCycle));
        std::cout << avg_time;
        
        std::string str = std::to_string((sizeOfElementOfList * COUNT_ELEMENT)) +  " " + std::to_string(avg_time);
        file.open("highload.csv", std::ios::app);
        file << str;
        file << std::endl;
        file.close();
    }
    
    return 0;

}
