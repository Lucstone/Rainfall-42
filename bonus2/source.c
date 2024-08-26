int language;
char *stack_adress;

int main(int param_1, int param_2) {

    char *lang_env = getenv("LANG");
    if (memcmp(lang_env, "fi", 2)) {
        language = 1;
    } else if (memcmp(lang_env, "nl", 2)) {
        language = 2;
    } else {
        language = 0;
    }
    greetuser();
    return 0;
}

void greetuser(void) {
    char *string;
    
    if (language == 0) {
        string = "Hello";
    } else if (language == 1) {
        string = "Hyvää päivää";
    } else {
        string = "Goedemiddag!";
    }
    strcat(string, stack_adress);
    puts(string);
    return;
}