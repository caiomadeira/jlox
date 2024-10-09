#include "utils.h"

static int hadError = U_FALSE;

static void run(char * source, int source_n)
{
    //Scanner * s = newscanner(source, source_n);
    //Token * vtk = scantokens(s, source_n, BASE_TOKENS_QTD);
    //print_token(vtk);
}

static void runprompt(int * hadError)
{
    char * buffer = allocstr(1000);
    int input = scanf("%s", buffer);
    for(;;)
    {
        printf("> ");
        if (buffer == NULL) break;
        run(buffer, 1000);
        int false = U_FALSE;
        hadError = &false;
    }
}

static void runfile(const char * path, int * hadError) {
    FILE * f = fopen(path, "rb");
    // 0L -> deslocamento offset = 0. Queremos ir ate oi final do arquivo
    // Move o ponteiro ate o final do arquivo depois volta
    // isso ajuda a determinar o tamanho do arquivo
    fseek(f, 0L, SEEK_END);
    long fsize = ftell(f);
    rewind(f);

    char * buffer = allocstr(fsize);
    if (buffer == NULL) { fclose(f); }
    fread(buffer, sizeof(char), fsize, f);
    buffer[fsize] = NULL_TERMINATOR;

    fclose(f);
    run(buffer, fsize);
    free(buffer);
    if (*(hadError) == U_TRUE) { exit(65); } // Ver se ta ok posteriormente
}

static void report(int line, const char* where, const char* msg, int * hadError)
{
    printf("[line %d] Error %s: %s\n", line, where, msg);
    int true = U_TRUE;
    hadError = &true;
}

static void error(int line, const char * msg, int * hadError)
{ report(line, "", msg, hadError); }

int main(int argc, char * argv[])
{
    int false = U_FALSE;
    int * hadError;
    hadError = &false;

    if (argc > 1)
    { printf("Usage: cmarte [script]\n"); exit(EX_USAGE); } 

    else if (argc == 1) { runfile(argv[0], hadError); }

    else { runprompt(hadError); }
    return 0;
}