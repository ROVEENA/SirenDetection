# Siren Detection with FFT Algorithm

This program reads WAVE audio files. It extracts header of WAVE file and stores audio PCM data. PCM data uses for fft.
## Dependicies

QT framework: necessary for wavfile.cpp

 AudioFTT library : [AudioFFT github repo](https://github.com/HiFi-LoFi/AudioFFT/)

## What is FFT ?

[You can watch this link to understand what is fft.](https://www.youtube.com/watch?v=spUNpyF58BY)

## Related information
- Video explanaition (in German language) of the different typoes of sirens in an ambulance (urban - (speaker), interurban (speaker), horn (air pressure)
- https://de.wikipedia.org/wiki/Folgetonhorn
- Audio sample files https://web.archive.org/web/20170308205507/http://www.einsatzvideos.net/sounds/
- DIN Stadtsignal: 410 Hz (tief), 547 Hz (hoch), DIN Landsignal: 362 Hz (tief), 483 Hz (hoch) according to [Hella Specs](https://hella.trustpb.de/soe/sites/default/files/downloads/Technische_Merkblaetter_Dachbalken_Informationen_RTK_VE.pdf)
- https://www.maxbmartin.de/en/ => See products and related data sheets.
- Austria: http://www.providing-concepts.com/folgeton.htm (including post bus example)
- Corridor for emergency vehicle access (Rettungsgasse) on highways https://www.youtube.com/watch?v=WfiLITNZudE
- https://github.com/sheelabhadra/Emergency-Vehicle-Detection
- You can extract smaple sounds from youtube videos like e.g. https://www.youtube.com/watch?v=ixfCoA8zBrk with [Youtube Downloader](https://github.com/ytdl-org/youtube-dl)
- A Review of Algorithms for Audio Fingerprinting (http://mtg.upf.edu/files/publications/MMSP-2002-pcano.pdf)
- https://ieeexplore.ieee.org/document/9032797


## Code Run

CmakeLists.txt used to compile the code. QT Creator selected as IDE since debugging is easy in QT Creator.

[If you want to use Vs Code click the link for QT framework usage in VS Code](https://www.kdab.com/using-visual-studio-code-for-qt-apps-pt-1/)

## Usage

```c
	WavFile*   p_file = new WavFile();

	QString file_path = "C:/Users/BLueleci/Desktop/cpp_works/qt_wav_v02/sirena_ambulanza.wav";
	//Read File and keep Header information on p_file
	p_file->open(file_path)

	//Read Audio PCM data in data_file
	QByteArray data_file = p_file->readAll();

    //transform bytes to int16 because it is written that sirena_ambulanza.wav data is 16 bit
	//if your .wav data has different type you should chance casting.
    const int16_t* p_int = reinterpret_cast<const int16_t*>(data_file.constData());

	//find number of samples
    int num_samples = data_file.size() / (p_file->fileFormat().channelCount()* p_file->fileFormat().sampleSize() / 8);
	
	//transformation operation 1
	vector<int16_t> int_vector;
    intPtrToInt16tVector(p_int, num_samples, int_vector);
	//transformation operation 2 (float type necesarry for AudioFFT library)
    vector<float> float_vector;
    int16VectorToFloatVector(int_vector, float_vector);
	
	// apply first fft
	// chose appropriate number of fft point  (size)
    const size_t fft_size = 1024;
    /*for ex: if sample rate = 20050 then,
    22050/1024 the amplitudes and phases are obtained about each 21,533203125 Hz bandwidth.
    2050 = 1 second -> 1024 = 0,04 second (every fft applys audio data array of 0,04 second)*/

    vector<pair<vector<float>, vector<float>>> result_of_first_fft; //it holds the output of real and imaginary data
    vector<float>::const_iterator point_at = float_vector.begin();
	//divide whole audio to small samples
    for(int i=0; i<float_vector.size()/fft_size; i++)
    {
        vector<float> temp_re(audiofft::AudioFFT::ComplexSize(fft_size));
        vector<float> temp_im(audiofft::AudioFFT::ComplexSize(fft_size));

        audiofft::AudioFFT fft;
        vector<float> sub_vector(point_at, point_at + fft_size);

        fft.init(fft_size);
        fft.fft(sub_vector.data(), temp_re.data(), temp_im.data());

        result_of_first_fft.push_back(make_pair(temp_re,temp_im));
        point_at += fft_size;

        temp_re.clear();
        temp_im.clear();
    }
	//calculate magnitude of each sample
    vector<vector <float>>magnitude_list_of_all_results;
    calculateMagnitudesOfEachVectorSample(fft_size, result_of_first_fft, magnitude_list_of_all_results);
	//calculate max frequency of each sample
    vector<float> frequency_list_fft1;
    calculateFreqListOfEachVectorSample(p_file, fft_size, magnitude_list_of_all_results, frequency_list_fft1);

```

