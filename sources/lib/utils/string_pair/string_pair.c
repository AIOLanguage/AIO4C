#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/utils/string_pair/string_pair.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"

string_pair *new_string_pair(string first, string second)
{
    string_pair *pair = new_object(sizeof(pair));
    pair->first = first;
    pair->second = second;
    return pair;
}