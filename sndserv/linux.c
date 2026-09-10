#include <raylib.h>
#include <stdio.h>

AudioStream stream;

void I_InitMusic(void) {}

void I_InitSound(int samplerate, int samplesize)
{
    printf("Initializing Doom Sound -> Rate: %d Hz, Bits: %d\n", samplerate, samplesize);
    SetAudioStreamBufferSizeDefault(512);
    
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        printf("[Error] Raylib Audio Device Isn't Ready\n");
    }
    stream = LoadAudioStream(samplerate, samplesize, 2);
    PlayAudioStream(stream);
}

void I_SubmitOutputBuffer(void* samples, int samplecount)
{

    while (!IsAudioStreamProcessed(stream)) {}
    UpdateAudioStream(stream, samples, samplecount);
}

void I_ShutdownSound(void)
{
    UnloadAudioStream(stream);
    CloseAudioDevice();
}

void I_ShutdownMusic(void) {}


