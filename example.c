#include <stdio.h>
#include <stdlib.h>

#include "pa_parse.h"

int main(int argc, char* argv[])
{
    CmdItem itemList[] = {
        { '-', 'h', 0x00000000, NULL, "Print help-text", false },
        { '-', 'a', 0x00000000, NULL, "Append value to file (need value)", true },
        { '+', 'o', 0x00000000, NULL, "Open file (need value)", true },
        { '-', 'p', 0x00000000, NULL, "Print key-massive after parsing", false },
        { 0, 0, 0, NULL, NULL, false }

    };

    int err = cmdParse(itemList, argc, argv);

    if (err != Ok) {

        printError(err);
        return 0;
    }

    if (isKey(itemList, 'h')) {
        printHelp(itemList, argv[0]);
    }

    if (isKey(itemList, 'p')) {
        cmdUsage(itemList, "Key-massive after parsing:\n");
    }

    if (isValue(itemList, 'o')) {
        printf("Opening file: %s\n", getKeyValue(itemList, 'o'));
    }

    if (isValue(itemList, 'a')) {
        printf("Hi %s!\n", getKeyValue(itemList, 'a'));
    }

    return 0;
}