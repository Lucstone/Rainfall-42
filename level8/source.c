char *auth = NULL;
char *service = NULL;

int main (void) {
    char input[125];
    void *pointer_input;
    size_t size = 125;
    
    do {
        pointer_input = fgets(input,size,stdin);
        if (input == "auth") {
            auth = malloc(4);
            *auth = 0;
            strcpy(auth, input);
        }
        if (input == "reset") {
            free(auth);
        }
        if (input == "service") {
            service = strdup(input);
        }
        if (input == "login") {
            if (auth[32] != 0) {
                system("/bin/sh");
            } else
                fwrite("Password:\n",1,10,stdout);
        }
    } while( true );

    return 0;
}