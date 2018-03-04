#include "StdAfx.h"
#include ".\DR7\DR7Parser.h"
#include ".\Test\Test.h"
#include ".\Common\IndigoTimer.h"

void Usage()
{
    printf("Usage DR7 parser\n"
        "params: \n"
        "-f \"c:\\example.dr7\"\n"
    );
}

int main(int argc, char* argv[])
{
    TestDR7Parser notifier;
    DR7Parser     parser;

    if (argc != 3)
    {
        Usage();
        return -1;
    }
    if (strcmp(argv[1], "-f") != 0)
    {
        Usage();
        return -1;
    }

    if (0)
    {
        //parser.BigFile(argv[2], 3500);

        return 0;
    } 

    IndigoTimer timer;

    timer.Start(0);
    StreamFile stream;

    bool r = stream.Initialize(argv[2]);
    if (r)
        r = parser.Initialize(&notifier);
    if (r)
        r = parser.Parse(stream);

    uint64_t ms = timer.Stop();
    if (r)
        printf("success parsing file: \"%s\", elapsed time: %I64ums\n", argv[2], ms);
    else
        printf("parsing file \"%s\" failed\n", argv[2]);

    return 0;
}