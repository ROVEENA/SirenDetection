///////////////////////////////////////////////////////////
//  PreprocessingCalculator.cpp
//  Implementation of the Class PreprocessingCalculator
//  Created on:      18-Jan-2023 12:42:06
//  Original author: RLobo
///////////////////////////////////////////////////////////
// TO DO ! -- high_pass_filter() is available in DSPFilters need to build it. THere were issues while building the Portaudio library
#include "PreprocessingCalculator.h"
// https://www.portaudio.com/
#include <portaudio.h>

using adlux::vse::PreprocessingCalculator;

const int SAMPLE_RATE = 44100;
const int FRAMES_PER_BUFFER = 256;
const int NUM_CHANNELS = 1;

#define ALPHA 0.95f // adjust as needed
float previousSample = 0.0f;

/**
 * Default constructor
 */
PreprocessingCalculator::PreprocessingCalculator(){

}


/**
 * Default destructor
 */
PreprocessingCalculator::~PreprocessingCalculator(){

}


/**
 * Initializes the internal values
 */
void PreprocessingCalculator::start(){



}


/**
 * Performs preprocessing of the input
 * 
 * @param micInput
 */
adlux::vse::PreProcessedSig PreprocessingCalculator::preprocess(adlux::vse::MicInput micInput){

deviceID = micInput.deviceID;
 
preprocessed_sig = high_pass_filter(micInput,cutoff_frequency,sample_rate);

  // Calculate the filter coefficients
  double omega_c = 2 * M_PI * cutoff_frequency / sample_rate;
  double alpha = sin(omega_c) / (2 * 0.5);
  double a_0 = 1 / (1 + alpha);
  double a_1 = -2 * cos(omega_c) / (1 + alpha);
  double a_2 = (1 - alpha) / (1 + alpha);
  double b_1 = a_1;
  double b_2 = a_2;

// Initialize the filtered signal with the same size as the input signal
  preprocessed_sig(micInput.size());

  // Apply the filter to the input signal
  for (size_t i = 2; i < signal.size(); ++i) {
    filtered_signal[i] = a_0 * signal[i] + a_1 * signal[i - 1] + a_2 * signal[i - 2]
                         - b_1 * filtered_signal[i - 1] - b_2 * filtered_signal[i - 2];
  }

  return filtered_signal; 

}


/**
 * Cleanup internal values
 */
void PreprocessingCalculator::stop(){

}