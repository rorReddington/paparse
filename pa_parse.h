//////////////////////////////////////////////////////////////////////////////////
// Parse program arguments
//
// Copyright (c) 2018-2019 Ruslan Sungurov, Filipp Uryas
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//////////////////////////////////////////////////////////////////////////////////

#ifndef PA_PARSE_H_INCLUDED
#define PA_PARSE_H_INCLUDED

#include "pa_config.h"

#include <stdio.h>
#include <stdbool.h>

#include <string.h>

/* Функция разбора массива argv:
 * возвращается код ошибки, представленный объектом перечисления Error
 * принимается массив ключей и параметры функции main
 */
Error cmdParse(CmdItem* itemList, int argc, char* argv[]);

/* Получение указателя на объект, описывающий ключ  (NULL если ключа нет в массиве)*/
CmdItem* getKeyPointer(CmdItem* itemList, char key, char sign);

/* Получение значения ключа */
char* getKeyValue(CmdItem* itemList, char key);

/* Функция проверки наличия ключа */
bool isKey(CmdItem* itemList, char key);

/* Функция проверки наличия значения */
bool isValue(CmdItem* itemList, char key);

/* Функция определения последнего элемента */
bool isEmpty(CmdItem* itemList);

/* Функция проверки на флаг */
bool isSign(CmdItem* itemList, char sign);

/* Вывод на экран текста text и содержимого массива */
void cmdUsage(CmdItem* itemList, char* text);

/* Вывод справки на экран */
void printHelp(CmdItem* itemList, char* text);

/* Вывод ошибки по ее коду */
void printError(Error errorCode);

#endif // PA_PARSE_H_INCLUDED