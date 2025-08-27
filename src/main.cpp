#include "game.h"
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include <iostream>
#include <stdexcept>

#pragma execution_character_set("utf-8")

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

ma_decoder decoder;
ma_device device;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    /* Reading PCM frames will loop based on what we specified when called ma_data_source_set_looping(). */
    ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    (void)pInput;
}

void maInit() {
    ma_result result;
    ma_device_config deviceConfig;

    result = ma_decoder_init_file("./resource/Gaming-fix.mp3", NULL, &decoder);
    if (result != MA_SUCCESS) {
        throw std::runtime_error("Resource File Not Found");
    }

    /*
    A decoder is a data source which means we just use ma_data_source_set_looping() to set the
    looping state. We will read data using ma_data_source_read_pcm_frames() in the data callback.
    */
    ma_data_source_set_looping(&decoder, MA_TRUE);

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate = decoder.outputSampleRate;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = &decoder;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        ma_decoder_uninit(&decoder);
        throw std::runtime_error("Failed to open playback device.");
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        throw std::runtime_error("Failed to start playback device.");
    }
}

void maDeinit() {

    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
}

int main() {
    // maInit();

    srand((unsigned int)time(nullptr));
    game SOD;
    SOD.entry();

    // maDeinit();
    return 0;
}