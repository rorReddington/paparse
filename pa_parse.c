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

#include "pa_parse.h"

/* Функция парсинга строки, возвращает ошибку из структуры Error */
Error cmdParse(CmdItem* itemList, int argc, char* argv[])
{

    if (argc < 2)
        return NoKey;

    for (size_t i = 1; i < argc; i++) {

        if (strlen(argv[i]) < 2)
            return UnknownKey;

        char sign = argv[i][0];

        if (isSign(itemList, sign)) {

            for (size_t j = 1; argv[i][j] != '\0'; j++) {

                char key = argv[i][j];
                CmdItem* item = getKeyPointer(itemList, key, sign);

                if (item == NULL)
                    return UnknownKey;

                if (item->needValue == true && strlen(argv[i]) > 2)
                    return UnknownKey;

                item->mask |= KEY_IN_CMD;

                if (item->needValue == true && argv[i + 1] == NULL)
                    return KeyNeedValue;

                if (item->needValue == true) {

                    item->mask = VAL_IN_CMD;
                    item->value = argv[i + 1];
                    ++i;
                    break;
                }
            }
        }
    }
    return Ok;
}

/* Получение указателя на объект, описывающий ключ  (NULL если ключа нет в массиве)*/
CmdItem* getKeyPointer(CmdItem* itemList, char key, char sign)
{

    for (size_t i = 0; isEmpty(&itemList[i]) != true; i++) {

        if ((itemList[i].sign == sign) && (itemList[i].key == key)) {
            return itemList + i;
        }
    }
    return NULL;
}

/* Получение значения ключа */
char* getKeyValue(CmdItem* itemList, char key)
{

    size_t i = 0;

    while (!isEmpty(&itemList[i])) {

        if ((itemList[i].key == key) && (itemList[i].needValue == true))
            return itemList[i].value;
        i++;
    }
    return NULL;
}

/* Функция проверки наличия ключа */
bool isKey(CmdItem* itemList, char key)
{

    size_t i = 0;

    while (!isEmpty(&itemList[i])) {

        if ((itemList[i].key == key) && (itemList[i].mask &= KEY_IN_CMD))
            return true;
        i++;
    }
    return false;
}

/* Функция проверки наличия значения */
bool isValue(CmdItem* itemList, char key)
{

    size_t i = 0;

    while (!isEmpty(&itemList[i])) {

        if ((itemList[i].key == key) && (itemList[i].mask &= VAL_IN_CMD))
            return true;
        i++;
    }
    return false;
}

/* Функция определения последнего элемента */
bool isEmpty(CmdItem* itemList)
{

    if ((itemList->sign == 0) && 
		(itemList->key == 0) && 
		(itemList->mask == 0) && 
		(itemList->value == NULL) && 
		(itemList->usage == NULL) && 
		(itemList->needValue == false)) {
        return true;
    }

    return false;
}

/* Функция проверки на флаг */
bool isSign(CmdItem* itemList, char sign)
{

    for (size_t i = 0; !isEmpty(&itemList[i]); i++) {
        if (itemList[i].sign == sign)
            return true;
    }

    return false;
}

/* Вывод на экран текста text и содержимого массива */
void cmdUsage(CmdItem* itemList, char* text)
{

    printf("%s\n", text);
    printf("KEY \tMASK \tNEED-VALUE \t%15s \tUSAGE\n", " VALUE");

    for (size_t i = 0; isEmpty(&itemList[i]) != true; i++) {
        printf("%2c%c \t%4i \t%10s \t%15s \t%s\n",
            itemList[i].sign, itemList[i].key,
            itemList[i].mask,
            itemList[i].needValue ? "true" : "false",
            itemList[i].value,
            itemList[i].usage);
    }
}

/* Вывод справки на экран */
void printHelp(CmdItem* itemList, char* text)
{
	
    printf("Usage: %s [key] [value] Example: [-h -a file.txt]\n\n", text);
    printf("Keys:\n");

    for (size_t i = 0; isEmpty(&itemList[i]) != true; i++)
        printf("%c%c\t %s\n", itemList[i].sign, itemList[i].key, itemList[i].usage);
}

/* Вывод ошибки по ее коду */
void printError(Error errorCode)
{
	
    switch (errorCode) {
    case UnknownKey:
        printf("Error: Unknown key\n");
        break;

    case KeyNeedValue:
        printf("Error: Key need value\n");
        break;

    case UnknownValue:
        printf("Error: Unknown value\n");
        break;

    case NoKey:
        printf("Error: Please specify key. Use -h for help.\n");
        break;

    default:
        break;
    }
}