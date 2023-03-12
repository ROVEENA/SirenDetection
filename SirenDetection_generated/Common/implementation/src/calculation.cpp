#include "calculation.h"
#include "AudioFFT.h"

//////////////////////////////////////////////////////////////////////////
///
/// \brief      this function transforms int16 pointer to int16 vector by reference
/// \param[in]  in_p_int            ... pointer holds audio data
/// \param[in]  in_samples_count    ... total sample count in audio
/// \param[out] out_int_vector      ... int16_t vector, it has same datas with in_p_int
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void intPtrToInt16tVector(const int16_t *in_p_int, int in_samples_count,
                          std::vector<int16_t> &out_int_vector)
{
    if(nullptr == in_p_int)
        return;
    for (int i = 0; i < in_samples_count; ++i)
    {
        out_int_vector.push_back(*in_p_int);
        in_p_int++;
    }
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      this function transforms int16 vector to float vector by reference
/// \param[in]  in_int_vector       ... int16_t typed input vector
/// \param[out] out_float_vector    ... float typed output vector
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void int16VectorToFloatVector(std::vector<int16_t> in_int_vector,
                              std::vector<float> &out_float_vector)
{
    //audio sample rate
    //transform data to float(pcmToReal)
    const uint16_t PCMS16MaxAmplitude =  32768; // because minimum is -32768
    out_float_vector.reserve(in_int_vector.size());
    for(int i=0; i<in_int_vector.size(); i++)
        out_float_vector.push_back(static_cast<float>(in_int_vector[i])/PCMS16MaxAmplitude);
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      this function calculates the magnitudes of real and imaginary part.
/// it repeats for every data in each sample.
/// \param[in]  in_fft_size                 ... fft point size
/// \param[in]  in_result_of_first_fft      ... this vector holds fft result of every sample. In first pair holds real part , second pair holds imaginary part
/// \param[out] out_magnitude_list_of_all_results   ... this vector holds magnitudes of real and imaginary parts. It repats for every data in each sample.
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void calculateMagnitudesOfEachVectorSample(const size_t in_fft_size,
                                           std::vector<std::pair<std::vector<float> ,std::vector<float>>> in_result_of_first_fft,
                                           std::vector<std::vector<float> > &out_magnitude_list_of_all_results)
{
    // magnitude = sqrt ( real_part^2 + imaginary_part^2)
    std::vector<float> magnitudes ;
    float sum = 0;
    for( int i = 0; i < in_result_of_first_fft.size(); i++ )
    {
        for( int j = 0; j < audiofft::AudioFFT::ComplexSize(in_fft_size); j++ )
        {
             sum = sqrt(pow(in_result_of_first_fft[i].first[j], 2) + pow(in_result_of_first_fft[i].second[j],2));
             magnitudes.push_back(sum);
        }
        out_magnitude_list_of_all_results.push_back(magnitudes);
        magnitudes.clear();
    }
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      this function calculates the max frequency for each sample.
/// \param[in]  in_audio_file               ... audio file pointer
/// \param[in]  in_fft_size                 ... fft point size
/// \param[in]  in_magnitude_list_of_all_samples      ... input vector which holds magnidutes of every data in each sample
/// \param[out] out_frequency_list_fft      ... it holds output of function. The value inside of each sample contains maximum frequency of related sample.
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void calculateFreqListOfEachVectorSample(AudioFile *in_audio_file,
                                         const size_t in_fft_size,
                                         std::vector<std::vector <float>> in_magnitude_list_of_all_samples,
                                         std::vector<float> &out_frequency_list_fft)
{
    // frequency of fft bin = maxElementIndex * sample_rate / fft_size;
    /*
    https://stackoverflow.com/questions/17390677/how-can-i-get-dft-fft-output-frequencies-in-hertz#:~:text=calculate%20the%20magnitude%20of%20each,no%20of%20points%20in%20FFT.
    */
    out_frequency_list_fft.reserve(in_magnitude_list_of_all_samples.size());
    int max_element_index, freq;
    for( int i = 0; i < in_magnitude_list_of_all_samples.size(); i++ )
    {
        max_element_index = max_element(in_magnitude_list_of_all_samples[i].begin(),
                                               in_magnitude_list_of_all_samples[i].end()) - in_magnitude_list_of_all_samples[i].begin();
        freq = max_element_index * in_audio_file->getSampleRate() / in_fft_size;
        out_frequency_list_fft.push_back(freq * in_audio_file->channelCount());
    }
}


