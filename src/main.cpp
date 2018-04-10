#include "StdAfx.h"
#include "EmPulse3E/Common/Parser3E.h"
#include "Test/Notifier3E.h"
#include "CommonLibEmPulse/IndigoTimer.h"

void Usage()
{
    printf("Usage EmPulse3E parser\n"
        "params: \n"
        "-f \"c:\\example.dr7\"\n"
    );
}

int main(int argc, char* argv[])
{
    char  file_name[MAX_PATH] = { 0 };
    int       pos = 1;
    uint32_t  num_interval = INT_MAX, num_frame = INT_MAX;

    while (pos < argc)
    {
        if (strcmp(argv[pos], "-f") == 0) // file name dr7 or dv7
        {
            if ((pos + 1) >= argc)
            {
                Usage();
                return -1;
            }
            pos++;
            strcpy_s(file_name, argv[pos]);
        }
        else if (strcmp(argv[pos], "-n") == 0) // num frame for analyze
        {
            if ((pos + 1) >= argc)
            {
                Usage();
                return -1;
            }
            pos++;
            num_frame = atoi(argv[pos]);
        }
        else if (strcmp(argv[pos], "-i") == 0) // num interval for analyze
        {
            if ((pos + 1) >= argc)
            {
                Usage();
                return -1;
            }
            pos++;
            num_interval = atoi(argv[pos]);
        }
        pos++;
    }
    if (!file_name[0])
    {
        Usage();
        return -1;
    }


    Parser3E     parser;
    Notifier3E   notifier;
    IndigoTimer  timer;
    StreamFile   stream;

    timer.Start(0);

    bool dr7 = false;
    if (strstr(file_name, ".DR7"))
        dr7 = true;

    bool r = stream.Initialize(file_name);
    if (r)
        r = notifier.Initialize(file_name, num_interval, num_frame);
    if (r)
        r = parser.Initialize(&notifier);
    if (r)
        r = parser.Parse(stream, dr7);

    uint64_t ms = timer.Stop();
    if (r)
        printf("success parsing file: \"%s\", elapsed time: %I64ums\n", argv[2], ms);
    else
        printf("parsing file \"%s\" failed\n", argv[2]);

    return 0;
}
