#include "utils.h"
#include "scanner.h"
#include "token.h"

static void runfile(const char * path) {
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
    run(buffer);
    free(buffer);
}

static void run(char * source, int source_n)
{
    Scanner * s = newscanner(source, source_n);
    Token ** vtk = scantokens(s, source_n, MAX)
}

int main(int argc, char * argv[])
{
    if (argc > 1)
    { printf("Usage: cmarte [script]"); exit(EX_USAGE); } 

    else if (argc == 1) { runfile(argv[0]); }

    else { runprompt(); }
    return 0;
}