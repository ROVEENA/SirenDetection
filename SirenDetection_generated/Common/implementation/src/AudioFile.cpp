#include"AudioFile.h"


AudioFile::AudioFile()
{
    bitDepth = 16;
    sampleRate = -1;
    samples.resize(1);
    samples[0].resize(0);
    audioFileFormat = AudioFileFormat::NotLoaded;
    type = AudioFile::SampleType::Float;
    codec = "";
}


AudioFile::AudioFile(std::string filePath)
    : AudioFile()
{
    load(filePath);
}

AudioFile::AudioFile(const AudioFile& other)
{
    this->samples = other.samples;
    this->audioFileFormat = other.audioFileFormat;
    this->bitDepth = other.bitDepth;
    this->iXMLChunk = other.iXMLChunk;
    this->sampleRate = other.sampleRate;
    this->type = other.type;
    this->codec = other.codec;
}

AudioFile::~AudioFile()
{
}


uint32_t AudioFile::getSampleRate() const
{
    return sampleRate;
}


int AudioFile::channelCount() 
{
        channels = (int)samples.size();
        return channels;
}


bool AudioFile::isMono() const
{
    return channels == 1;
}


bool AudioFile::isStereo() const
{
    return channels == 2;
}


int AudioFile::getBitDepth() const
{
    return bitDepth;
}

int AudioFile::sampleSize() const
{
    if (samples.size() > 0)
        return (int)samples[0].size();
    else
        return 0;
}


double AudioFile::getLengthInSeconds() const
{
    return (double)sampleSize() / (double)sampleRate;
}

bool AudioFile::setAudioBuffer(AudioBuffer& newBuffer)
{
    int numChannels = (int)newBuffer.size();

    if (numChannels <= 0)
    {
        assert(false && "The buffer your are trying to use has no channels");
        return false;
    }

    size_t numSamples = newBuffer[0].size();

    // set the number of channels
    samples.resize(newBuffer.size());

    for (int k = 0; k < channelCount(); k++)
    {
        assert(newBuffer[k].size() == numSamples);

        samples[k].resize(numSamples);

        for (size_t i = 0; i < numSamples; i++)
        {
            samples[k][i] = newBuffer[k][i];
        }
    }

    return true;
}


void AudioFile::setAudioBufferSize(int numChannels, int numSamples)
{
    samples.resize(numChannels);
    setNumSamplesPerChannel(numSamples);
}

void AudioFile::setNumSamplesPerChannel(int numSamples)
{
    int originalSize = sampleSize();

    for (int i = 0; i < channelCount(); i++)
    {
        samples[i].resize(numSamples);

        // set any new samples to zero
        if (numSamples > originalSize)
            std::fill(samples[i].begin() + originalSize, samples[i].end(), (float)0.);
    }
}

void AudioFile::setNumChannels(int numChannels)
{
    int originalNumChannels = channelCount();
    int originalNumSamplesPerChannel = sampleSize();

    samples.resize(numChannels);

    // make sure any new channels are set to the right size
    // and filled with zeros
    if (numChannels > originalNumChannels)
    {
        for (int i = originalNumChannels; i < numChannels; i++)
        {
            samples[i].resize(originalNumSamplesPerChannel);
            std::fill(samples[i].begin(), samples[i].end(), (float)0.);
        }
    }
    channels = numChannels;
}


void AudioFile::setBitDepth(int numBitsPerSample)
{
    bitDepth = numBitsPerSample;
}


void AudioFile::setSampleRate(uint32_t newSampleRate)
{
    sampleRate = newSampleRate;
}

void AudioFile::setSampleType(AudioFile::SampleType type)
{
    this->type = type;
}

AudioFile::SampleType AudioFile::getSampleType() const
{
    return this->type;
}

void AudioFile::setCodec(const std::string& codec)
{
    this->codec = codec;
}

std::string AudioFile::getCodec() const
{
    return this->codec;
}

AudioFile& AudioFile::operator=(const AudioFile& other)
{
    this->sampleRate = other.sampleRate;
    this->channels = other.channels;
    this->endianess = other.endianess;
    this->codec = other.codec;
    this->type = other.type;
    this->samples = other.samples;
    return *this;
}

bool AudioFile::operator==(const AudioFile& other) const
{
         return this->sampleRate == other.sampleRate &&
         this->channels == other.channels &&
             this->sampleSize() == other.sampleSize() &&
             this->endianess == other.endianess &&
             this->codec == other.codec &&
             this->type == other.type;
}

bool AudioFile::operator!=(const AudioFile& other) const
{
    return !(*this==other);
}

AudioFile::Endianness AudioFile::byteOrder()
{
    // Always assuming BigEndian.
    return AudioFile::Endianness::BigEndian;
}


bool AudioFile::load(std::string filePath)
{
    std::ifstream file(filePath, std::ios::binary);

    // check the file exists
    if (!file.good())
    {
        std::cout<<("ERROR: File doesn't exist or otherwise can't load file\n" + filePath);
        return false;
    }

    std::vector<uint8_t> fileData;

    file.unsetf(std::ios::skipws);

    file.seekg(0, std::ios::end);
    size_t length = file.tellg();
    file.seekg(0, std::ios::beg);

    // allocate
    fileData.resize(length);

    file.read(reinterpret_cast<char*> (fileData.data()), length);
    file.close();

    if (file.gcount() != length)
    {
        std::cout << ("ERROR: Couldn't read entire file\n" + filePath);
        return false;
    }
    codec = "audio/pcm";
    type = AudioFile::SampleType::Float;
    return loadFromMemory(fileData);
}


bool AudioFile::loadFromMemory(std::vector<uint8_t>& fileData)
{
    // get audio file format
    audioFileFormat = determineAudioFileFormat(fileData);

    if (audioFileFormat == AudioFileFormat::Wave)
    {
        return decodeWaveFile(fileData);
    }
    else if (audioFileFormat == AudioFileFormat::Aiff)
    {
        return decodeAiffFile(fileData);
    }
    else
    {
        std::cout << ("Audio File Type: Error");
        return false;
    }
}


bool AudioFile::decodeWaveFile(std::vector<uint8_t>& fileData)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    std::string headerChunkID(fileData.begin(), fileData.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileData, 4) + 8;
    std::string format(fileData.begin() + 8, fileData.begin() + 12);

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfDataChunk = getIndexOfChunk(fileData, "data", 12);
    int indexOfFormatChunk = getIndexOfChunk(fileData, "fmt ", 12);
    int indexOfXMLChunk = getIndexOfChunk(fileData, "iXML", 12);

    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfDataChunk == -1 || indexOfFormatChunk == -1 || headerChunkID != "RIFF" || format != "WAVE")
    {
        std::cout << ("ERROR: this doesn't seem to be a valid .WAV file");
        return false;
    }

    // -----------------------------------------------------------
    // FORMAT CHUNK
    int f = indexOfFormatChunk;
    std::string formatChunkID(fileData.begin() + f, fileData.begin() + f + 4);
    //int32_t formatChunkSize = fourBytesToInt (fileData, f + 4);
    uint16_t audioFormat = twoBytesToInt(fileData, f + 8);
    uint16_t numChannels = twoBytesToInt(fileData, f + 10);
    sampleRate = (uint32_t)fourBytesToInt(fileData, f + 12);
    uint32_t numBytesPerSecond = fourBytesToInt(fileData, f + 16);
    uint16_t numBytesPerBlock = twoBytesToInt(fileData, f + 20);
    bitDepth = (int)twoBytesToInt(fileData, f + 22);

    uint16_t numBytesPerSample = static_cast<uint16_t> (bitDepth) / 8;

    // check that the audio format is PCM or Float or extensible
    if (audioFormat != WavAudioFormat::PCM && audioFormat != WavAudioFormat::IEEEFloat && audioFormat != WavAudioFormat::Extensible)
    {
        std::cout << ("ERROR: this .WAV file is encoded in a format that this library does not support at present");
        return false;
    }

    // check the number of channels is mono or stereo
    if (numChannels < 1 || numChannels > 128)
    {
        std::cout << ("ERROR: this WAV file seems to be an invalid number of channels (or corrupted?)");
        return false;
    }

    // check header data is consistent
    if (numBytesPerSecond != static_cast<uint32_t> ((numChannels * sampleRate * bitDepth) / 8) || numBytesPerBlock != (numChannels * numBytesPerSample))
    {
        std::cout << ("ERROR: the header data in this WAV file seems to be inconsistent");
        return false;
    }

    // check bit depth is either 8, 16, 24 or 32 bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24 && bitDepth != 32)
    {
        std::cout << ("ERROR: this file has a bit depth that is not 8, 16, 24 or 32 bits");
        return false;
    }

    // -----------------------------------------------------------
    // DATA CHUNK
    int d = indexOfDataChunk;
    std::string dataChunkID(fileData.begin() + d, fileData.begin() + d + 4);
    int32_t dataChunkSize = fourBytesToInt(fileData, d + 4);

    int numSamples = dataChunkSize / (numChannels * bitDepth / 8);
    int samplesStartIndex = indexOfDataChunk + 8;

    clearAudioBuffer();
    samples.resize(numChannels);

    for (int i = 0; i < numSamples; i++)
    {
        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerBlock * i) + channel * numBytesPerSample;

            if ((sampleIndex + (bitDepth / 8) - 1) >= fileData.size())
            {
                std::cout << ("ERROR: read file error as the metadata indicates more samples than there are in the file data");
                return false;
            }

            if (bitDepth == 8)
            {
                float sample = singleByteToSample(fileData[sampleIndex]);
                samples[channel].push_back(sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt(fileData, sampleIndex);
                float sample = sixteenBitIntToSample(sampleAsInt);
                samples[channel].push_back(sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileData[sampleIndex + 2] << 16) | (fileData[sampleIndex + 1] << 8) | fileData[sampleIndex];

                if (sampleAsInt & 0x800000) //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF; // so make sure sign is extended to the 32 bit float

                float sample = (float)sampleAsInt / (float)8388608.;
                samples[channel].push_back(sample);
            }
            else if (bitDepth == 32)
            {
                int32_t sampleAsInt = fourBytesToInt(fileData, sampleIndex);
                float sample;

                if (audioFormat == WavAudioFormat::IEEEFloat)
                    sample = (float)reinterpret_cast<float&> (sampleAsInt);
                else // assume PCM
                    sample = (float)sampleAsInt / static_cast<float> (std::numeric_limits<std::int32_t>::max());

                samples[channel].push_back(sample);
            }
            else
            {
                assert(false);
            }
        }
    }

    // -----------------------------------------------------------
    // iXML CHUNK
    if (indexOfXMLChunk != -1)
    {
        int32_t chunkSize = fourBytesToInt(fileData, indexOfXMLChunk + 4);
        iXMLChunk = std::string((const char*)&fileData[indexOfXMLChunk + 8], chunkSize);
    }

    return true;
}


bool AudioFile::decodeAiffFile(std::vector<uint8_t>& fileData)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    std::string headerChunkID(fileData.begin(), fileData.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileData, 4, Endianness::BigEndian) + 8;
    std::string format(fileData.begin() + 8, fileData.begin() + 12);

    int audioFormat = format == "AIFF" ? AIFFAudioFormat::Uncompressed : format == "AIFC" ? AIFFAudioFormat::Compressed : AIFFAudioFormat::Error;

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfCommChunk = getIndexOfChunk(fileData, "COMM", 12, Endianness::BigEndian);
    int indexOfSoundDataChunk = getIndexOfChunk(fileData, "SSND", 12, Endianness::BigEndian);
    int indexOfXMLChunk = getIndexOfChunk(fileData, "iXML", 12, Endianness::BigEndian);

    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfSoundDataChunk == -1 || indexOfCommChunk == -1 || headerChunkID != "FORM" || audioFormat == AIFFAudioFormat::Error)
    {
        std::cout << ("ERROR: this doesn't seem to be a valid AIFF file");
        return false;
    }

    // -----------------------------------------------------------
    // COMM CHUNK
    int p = indexOfCommChunk;
    std::string commChunkID(fileData.begin() + p, fileData.begin() + p + 4);
    //int32_t commChunkSize = fourBytesToInt (fileData, p + 4, Endianness::BigEndian);
    int16_t numChannels = twoBytesToInt(fileData, p + 8, Endianness::BigEndian);
    int32_t numSamplesPerChannel = fourBytesToInt(fileData, p + 10, Endianness::BigEndian);
    bitDepth = (int)twoBytesToInt(fileData, p + 14, Endianness::BigEndian);
    sampleRate = getAiffSampleRate(fileData, p + 16);

    // check the sample rate was properly decoded
    if (sampleRate == 0)
    {
        std::cout << ("ERROR: this AIFF file has an unsupported sample rate");
        return false;
    }

    // check the number of channels is mono or stereo
    if (numChannels < 1 || numChannels > 2)
    {
        std::cout << ("ERROR: this AIFF file seems to be neither mono nor stereo (perhaps multi-track, or corrupted?)");
        return false;
    }

    // check bit depth is either 8, 16, 24 or 32-bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24 && bitDepth != 32)
    {
        std::cout << ("ERROR: this file has a bit depth that is not 8, 16, 24 or 32 bits");
        return false;
    }

    // -----------------------------------------------------------
    // SSND CHUNK
    int s = indexOfSoundDataChunk;
    std::string soundDataChunkID(fileData.begin() + s, fileData.begin() + s + 4);
    int32_t soundDataChunkSize = fourBytesToInt(fileData, s + 4, Endianness::BigEndian);
    int32_t offset = fourBytesToInt(fileData, s + 8, Endianness::BigEndian);
    //int32_t blockSize = fourBytesToInt (fileData, s + 12, Endianness::BigEndian);

    int numBytesPerSample = bitDepth / 8;
    int numBytesPerFrame = numBytesPerSample * numChannels;
    int totalNumAudioSampleBytes = numSamplesPerChannel * numBytesPerFrame;
    int samplesStartIndex = s + 16 + (int)offset;

    // sanity check the data
    if ((soundDataChunkSize - 8) != totalNumAudioSampleBytes || totalNumAudioSampleBytes > static_cast<long>(fileData.size() - samplesStartIndex))
    {
        std::cout << ("ERROR: the metadatafor this file doesn't seem right");
        return false;
    }

    clearAudioBuffer();
    samples.resize(numChannels);

    for (int i = 0; i < numSamplesPerChannel; i++)
    {
        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerFrame * i) + channel * numBytesPerSample;

            if ((sampleIndex + (bitDepth / 8) - 1) >= fileData.size())
            {
                std::cout << ("ERROR: read file error as the metadata indicates more samples than there are in the file data");
                return false;
            }

            if (bitDepth == 8)
            {
                int8_t sampleAsSigned8Bit = (int8_t)fileData[sampleIndex];
                float sample = (float)sampleAsSigned8Bit / (float)128.;
                samples[channel].push_back(sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt(fileData, sampleIndex, Endianness::BigEndian);
                float sample = sixteenBitIntToSample(sampleAsInt);
                samples[channel].push_back(sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileData[sampleIndex] << 16) | (fileData[sampleIndex + 1] << 8) | fileData[sampleIndex + 2];

                if (sampleAsInt & 0x800000) //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF; // so make sure sign is extended to the 32 bit float

                float sample = (float)sampleAsInt / (float)8388608.;
                samples[channel].push_back(sample);
            }
            else if (bitDepth == 32)
            {
                int32_t sampleAsInt = fourBytesToInt(fileData, sampleIndex, Endianness::BigEndian);
                float sample;

                if (audioFormat == AIFFAudioFormat::Compressed)
                    sample = (float)reinterpret_cast<float&> (sampleAsInt);
                else // assume uncompressed
                    sample = (float)sampleAsInt / static_cast<float> (std::numeric_limits<std::int32_t>::max());

                samples[channel].push_back(sample);
            }
            else
            {
                assert(false);
            }
        }
    }

    // -----------------------------------------------------------
    // iXML CHUNK
    if (indexOfXMLChunk != -1)
    {
        int32_t chunkSize = fourBytesToInt(fileData, indexOfXMLChunk + 4);
        iXMLChunk = std::string((const char*)&fileData[indexOfXMLChunk + 8], chunkSize);
    }

    return true;
}


uint32_t AudioFile::getAiffSampleRate(std::vector<uint8_t>& fileData, int sampleRateStartIndex)
{
    for (auto it : aiffSampleRateTable)
    {
        if (tenByteMatch(fileData, sampleRateStartIndex, it.second, 0))
            return it.first;
    }

    return 0;
}


bool AudioFile::tenByteMatch(std::vector<uint8_t>& v1, int startIndex1, std::vector<uint8_t>& v2, int startIndex2)
{
    for (int i = 0; i < 10; i++)
    {
        if (v1[startIndex1 + i] != v2[startIndex2 + i])
            return false;
    }

    return true;
}

void AudioFile::clearAudioBuffer()
{
    for (size_t i = 0; i < samples.size(); i++)
    {
        samples[i].clear();
    }

    samples.clear();
}


AudioFileFormat AudioFile::determineAudioFileFormat(std::vector<uint8_t>& fileData)
{
    std::string header(fileData.begin(), fileData.begin() + 4);

    if (header == "RIFF")
        return AudioFileFormat::Wave;
    else if (header == "FORM")
        return AudioFileFormat::Aiff;
    else
        return AudioFileFormat::Error;
}


int32_t AudioFile::fourBytesToInt(std::vector<uint8_t>& source, int startIndex, Endianness endianness)
{
    int32_t result;

    if (endianness == Endianness::LittleEndian)
        result = (source[startIndex + 3] << 24) | (source[startIndex + 2] << 16) | (source[startIndex + 1] << 8) | source[startIndex];
    else
        result = (source[startIndex] << 24) | (source[startIndex + 1] << 16) | (source[startIndex + 2] << 8) | source[startIndex + 3];

    return result;
}

int16_t AudioFile::twoBytesToInt(std::vector<uint8_t>& source, int startIndex, Endianness endianness)
{
    int16_t result;

    if (endianness == Endianness::LittleEndian)
        result = (source[startIndex + 1] << 8) | source[startIndex];
    else
        result = (source[startIndex] << 8) | source[startIndex + 1];

    return result;
}



int AudioFile::getIndexOfChunk(std::vector<uint8_t>& source, const std::string& chunkHeaderID, int startIndex, Endianness endianness)
{
    constexpr int dataLen = 4;
    if (chunkHeaderID.size() != dataLen)
    {
        assert(false && "Invalid chunk header ID string");
        return -1;
    }

    int i = startIndex;
    while (i < source.size() - dataLen)
    {
        if (memcmp(&source[i], chunkHeaderID.data(), dataLen) == 0)
        {
            return i;
        }

        i += dataLen;
        auto chunkSize = fourBytesToInt(source, i, endianness);
        i += (dataLen + chunkSize);
    }

    return -1;
}


float AudioFile::sixteenBitIntToSample(int16_t sample)
{
    return static_cast<float>(sample) / static_cast<float> (32768.);
}


float AudioFile::singleByteToSample(uint8_t sample)
{
    return static_cast<float> (sample - 128) / static_cast<float> (128.);
}