/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include<cassert>
#include "utils.h"
#include"AudioFile.h"

long long int audioDuration( AudioFile &format, long long int bytes)
{
    return (bytes * 1000000) /
        (static_cast<long long>(format.getSampleRate()) * format.channelCount() * (format.sampleSize() / 8));
}

long long int audioLength( AudioFile &format, long long int microSeconds)
{
    long long int result = (static_cast<long long>(format.getSampleRate()) * format.channelCount() * (format.sampleSize() / 8))
       * microSeconds / 1000000;
   result -= result % (static_cast<long long>(format.channelCount()) * format.sampleSize());
   return result;
}

double nyquistFrequency(const AudioFile &format)
{
    return format.getSampleRate() / 2;
}

std::string formatToString( AudioFile &format)
{
    std::string result;

    if (AudioFile() != format) {
        if (format.getCodec() == "audio/pcm") {

            const std::string formatEndian = (format.byteOrder() == AudioFile::Endianness::LittleEndian)
                ?   std::string("LE") : std::string("BE");

            std::string formatType;
            switch (format.getSampleType()) {
            case AudioFile::SampleType::SignedInt:
                formatType = "signed";
                break;
            case AudioFile::SampleType::UnSignedInt:
                formatType = "unsigned";
                break;
            case AudioFile::SampleType::Float:
                formatType = "float";
                break;
            case AudioFile::SampleType::Unknown:
                formatType = "unknown";
                break;
            }

            std::string formatChannels = std::to_string(format.channelCount()) + std::string(" channels");
            switch (format.channelCount()) {
            case 1:
                formatChannels = "mono";
                break;
            case 2:
                formatChannels = "stereo";
                break;
            }

            result =std::to_string(format.getSampleRate()) + " Hz " +
                    std::to_string(format.sampleSize()) + " bit " +
                    formatType + formatEndian + formatChannels;
        } else {
            result = format.getCodec();
        }
    }

    return result;
}

bool isPCM(const AudioFile &format)
{
    return (format.getCodec() == "audio/pcm");
}

bool isPCMS16LE( AudioFile &format)
{
    return isPCM(format) &&
           format.getSampleType() == AudioFile::SampleType::SignedInt &&
           format.sampleSize() == 16 &&
           format.byteOrder() == AudioFile::Endianness::LittleEndian;
}

const short  PCMS16MaxValue     =  32767;
const unsigned short PCMS16MaxAmplitude =  32768; // because minimum is -32768

double pcmToReal(short pcm)
{
    return double(pcm) / PCMS16MaxAmplitude;
}

short realToPcm(double real)
{
    return real * PCMS16MaxValue;
}