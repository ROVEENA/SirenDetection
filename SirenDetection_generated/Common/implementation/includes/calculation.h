#ifndef CALCULATION_H
#define CALCULATION_H

#include "AudioFile.h"
#include<cmath>

//-----------------------------------------------------------------------------
// Miscellaneous calculation functions
//-----------------------------------------------------------------------------

void        intPtrToInt16tVector                    (const int16_t *in_p_int,
                                                    int in_samples_count,
                                                    std::vector<int16_t> &out_int_vector);

void        int16VectorToFloatVector                (std::vector<int16_t> in_int_vector,
                                                    std::vector<float> &out_float_vector);

void        calculateMagnitudesOfEachVectorSample   (const size_t in_fft_size,
                                                    std::vector<std::pair<std::vector<float>,
                                                    std::vector<float>>> in_result_of_first_fft,
                                                    std::vector<std::vector <float>> &out_magnitude_list_of_all_results);

void        calculateFreqListOfEachVectorSample     (AudioFile *in_audio_file,
                                                    const size_t in_fft_size,
                                                    std::vector<std::vector <float>> in_magnitude_list_of_all_samples,
                                                    std::vector<float> &out_frequency_list_fft);
#endif // CALCULATION_H