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

#ifndef PA_CONFIG_H_INCLUDED
#define PA_CONFIG_H_INCLUDED

#include <stdbool.h>

/* Константы для работы с маской */
#define KEY_IN_CMD 0x00000001
#define VAL_IN_CMD 0x00000010

/* Перечисление с номерами ошибок */
typedef enum {
    Ok = 100,
    UnknownKey = 200,
    KeyNeedValue = 300,
    UnknownValue = 400,
    NoKey = 500
} Error;

/* Структура для хранения ключа */
typedef struct {
    char sign;
    char key;
    int mask;
    char* value;
    char* usage;
    bool needValue;
} CmdItem;

#endif // PA_CONFIG_H_INCLUDED
