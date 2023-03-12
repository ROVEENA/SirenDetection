//A test file to high pass the audio input to remove lower frequencies. 
//Has error while building, not complete
#include <iostream>
#include <sndfile.h>
#include "DSPFilters/Dsp.h"

using namespace DSPFilters;

int main()
{
    // Open input and output .wav files
    SF_INFO input_info, output_info;
    input_info.format = 0;
    output_info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    SNDFILE* input_file = sf_open("input.wav", SFM_READ, &input_info);
    SNDFILE* output_file = sf_open("output.wav", SFM_WRITE, &output_info);

    // Create high-pass filter
    Butterworth::HighPass<float> highpass(4);
    highpass.setup(input_info.samplerate, 1000);

    // Process samples
    float buffer[4096];
    while (int num_samples = sf_read_float(input_file, buffer, 4096))
    {
        highpass.process(num_samples, buffer);
        sf_write_float(output_file, buffer, num_samples);
    }

    // Close files
    sf_close(input_file);
    sf_close(output_file);

    return 0;
}

