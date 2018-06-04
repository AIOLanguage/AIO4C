void isEqualsStrings(char* first, char* second, int *flag){
    for (int i = 0; i < sizeof(first); ++i) {
        if (first[i] != second[i]){
            *flag = 0;
            return;
        }
    }
    *flag = 1;
}