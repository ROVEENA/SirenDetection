#include "AudioFFT.h"
#include <complex>
#include<fstream>
#include<iostream>
#include "calculation.h"
#include"AudioFile.h"


//////////////////////////////////////////////////////////////////////////
///
/// \brief      this program divides audio data to many samples and calculates max frequency of each sample.
/// \author     Bahadir Lueleci
/// \date       18.05.2022
/// \details    Depedicies: QT framework, AudioFTT library
///             AudioFFT github repo: https://github.com/HiFi-LoFi/AudioFFT
///
/////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

    const std::string filePath = "../data/sirena_ambulanza.wav";

    AudioFile a;
    bool loadedOK = a.load(filePath);

    assert(loadedOK);

    std::cout << "Bit Depth: " << a.getBitDepth() << std::endl;
    std::cout << "Sample Rate: " << a.getSampleRate() << std::endl;
    std::cout << "Num Channels: " << a.channelCount() << std::endl;
    std::cout << "Length in Seconds: " << a.getLengthInSeconds() << std::endl;
    std::cout << "Number of samples per channel: " << a.getSampleRate() << std::endl;
    std::cout<<a.samples[0].size() << std::endl;
    std::cout << std::endl;

    int num_samples = a.samples.size() / (a.channelCount() * a.getSampleRate() / 8);


    // apply first fft
    const size_t fft_size = 1024;
    /*for ex: if sample rate = 20050 then,
    22050/1024 the amplitudes and phases are obtained about each 21,533203125 Hz bandwidth.
    2050 = 1 second -> 1024 = 0,04 second (every fft applys audio data array of 0,04 second)*/

    std::vector<std::pair<std::vector<float>, std::vector<float>>> result_of_first_fft; //it holds the output of real and imaginary data
    std::vector<float>::const_iterator point_at = a.samples[0].begin();//float_vector.begin();

    std::cout<<fft_size<<std::endl;
    for(int i=0; i< a.samples[0].size()/fft_size; i++)
    {
        std::vector<float> temp_re(audiofft::AudioFFT::ComplexSize(fft_size));
        std::vector<float> temp_im(audiofft::AudioFFT::ComplexSize(fft_size));

        audiofft::AudioFFT fft;
        std::vector<float> sub_vector(point_at, point_at + fft_size);

        fft.init(fft_size);
        fft.fft(sub_vector.data(), temp_re.data(), temp_im.data());

        result_of_first_fft.push_back(make_pair(temp_re,temp_im));
        point_at += fft_size;

        temp_re.clear();
        temp_im.clear();
        //std::cout<<i<<std::endl;
    }
    std::vector<std::vector <float>>magnitude_list_of_all_results;
    calculateMagnitudesOfEachVectorSample(fft_size, result_of_first_fft, magnitude_list_of_all_results);
    std::vector<float> frequency_list_fft1;
    calculateFreqListOfEachVectorSample(&a, fft_size, magnitude_list_of_all_results, frequency_list_fft1);

    return 0;
}


