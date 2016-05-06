//
// Created by Shaaheen on 4/29/2016.
//

#ifndef ASSIGNMENT_5_SCRSHA001_AUDIO_H
#define ASSIGNMENT_5_SCRSHA001_AUDIO_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>

namespace SCRSHA001{
    //Generic params BitType : int8_t or int16_t BitType: intN_t or pair<intN_t,intN_t>
    template <typename BitType>
    class Audio{
    private:
        std::vector<BitType> audioData;
        int channels;
        int sampleRateInHz;
        int numberOfSamples;
        int lengthOfAudioSeconds;

        /*
         * Loads audio file using binary reading
         */
        void loadAudio(const std::string &fileName){
            std::ifstream input(fileName,std::ios::binary| std::ios::in); //get file in binary

            if (input.is_open()){
                long fileSize =  filesize(fileName);
                this->numberOfSamples = fileSize/( sizeof(BitType) * channels);
                this->lengthOfAudioSeconds = (int) (numberOfSamples / ((float) sampleRateInHz));

                audioData.resize(numberOfSamples); //Reserve space for samples

                for (int i = 0; i < numberOfSamples; ++i) {
                    char buffer[sizeof(BitType)];
                    BitType sample;
                    input.read((char *) buffer, sizeof(BitType)); //read in sample
                    //sample =
                    if (channels == 2){
                        char buffer2[sizeof(BitType)];
                        BitType sampleR;
                        input.read((char *) buffer2, sizeof(BitType)); //read in sample right ear

                        //audioData[i] = (BitType) (std::make_pair(buffer , buffer2)); // will be pair<intN_t,intN_t>(sample,sampleR)
                    }
                    else{
                        audioData[i] = (*(BitType*) buffer); //int(sample)
                    }
                }
                input.close();
                //return audioData;
            }
            else{
                std::cout<<"Error: Can't open file"<<std::endl;
                exit(0);
            }

        }

    public:
        //Main constructor
        Audio(const std::string &fileName, int &chan, int &rate)  : channels(chan), sampleRateInHz(rate){
            loadAudio(fileName);
        }

        //constructor
        Audio(int samples,int length, std::vector<BitType> vec, int &chan, int &rate)
                : channels(chan), sampleRateInHz(rate), numberOfSamples(samples),lengthOfAudioSeconds(length),audioData(vec){
        }

        //Copy constructor
        Audio(const Audio &rhs): channels(rhs.channels),sampleRateInHz(rhs.sampleRateInHz)
                ,numberOfSamples(rhs.numberOfSamples),lengthOfAudioSeconds(rhs.lengthOfAudioSeconds),audioData(rhs.audioData){ }

        /*
         * Saves the audio data into file
         */
        void saveAudio(const std::string &outFileName) {
            std::string fullName = outFileName + "_"  + std::to_string(sampleRateInHz) + "_" + std::to_string(sizeof(BitType)*8) + "_mono.raw";
            std::ofstream output(fullName,std::ios::binary | std::ios::out);

            if (output.is_open()){
                for (int i = 0; i < audioData.size(); ++i) {
                    output.write(reinterpret_cast<const char *>(&audioData[i]), sizeof(BitType)); //sizeof(BitType));
                }
            }
            else{
                std::cout<<"Could not write to File"<<std::endl;
                exit(0);
            }
        }

        /*
         * Returns the size of the file
         */
        long filesize(const std::string &filename){
            std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
            return (long) in.tellg();
        }

        /*
         * Conatanates two audio data vectors together to make one large audio vector
         */
        Audio operator|(const Audio &rhs) {
            Audio concatenated(*this);
            //Add right hand audio onto end of first audio
            concatenated.audioData.insert(concatenated.audioData.end(),rhs.audioData.begin(),rhs.audioData.end());
            //Adjust lengths
            concatenated.lengthOfAudioSeconds = concatenated.lengthOfAudioSeconds + rhs.lengthOfAudioSeconds;
            concatenated.numberOfSamples = concatenated.numberOfSamples + rhs.numberOfSamples;
            return concatenated;
        }

        /*
         * Increases audio by a volume factor
         */
        Audio operator*(std::pair<float, float> volumeFactor) {
            Audio concatenated(*this);
            //Lambda function to increase audio data
            std::transform(this->audioData.begin(),this->audioData.end(),concatenated.audioData.begin(),
                [volumeFactor](BitType value){ return value*volumeFactor.first;}
            );
            //concatenated.audioData.insert(concatenated.audioData.end(),rhs.audioData.begin(),rhs.audioData.end());
            return concatenated;
        }

        /*
         * Adds sound aplitudes together
         * - adds two audio vectors together and clamps on maximum
         */
        Audio operator+(const Audio &rhs) {
            Audio concatenated(*this);
            for (int i = 0; i < audioData.size(); ++i) {
                BitType sumOfSound = audioData[i] + rhs.audioData[i]; //add data samples
                if (sumOfSound > std::numeric_limits<BitType>::max()){
                    sumOfSound = std::numeric_limits<BitType>::max(); //clamp to max if too large
                }
                concatenated.audioData[i] = sumOfSound;
            }
            return concatenated;
        }

        /*
         * Cuts out a range of samples from audio
         */
        Audio operator^(std::pair<int, int> rangeToBeCut) {
            //Create all new variables as will be a diff number of samples and length - Can't just copy as diff vals
            int numSamplesWithCutOuts = numberOfSamples - (rangeToBeCut.second - rangeToBeCut.first) - 1;
            int cutLength = (int) (numSamplesWithCutOuts / ((float) sampleRateInHz));
            std::vector<BitType> cutAudioData;
            for (int i = 0; i < audioData.size(); ++i) {
                if ( i < rangeToBeCut.first || i>rangeToBeCut.second){
                    cutAudioData.push_back(audioData[i]); //don't know index so use push back
                }
            }

            //Create cut out audio object
            Audio<BitType> audioWithCutOut(numSamplesWithCutOuts,cutLength,cutAudioData,channels,sampleRateInHz);
            return audioWithCutOut;
        }

        /*
         * Function to select two (same length) sample ranges from two signals and add them together
         */
        Audio rangeAdd(const Audio &rhs,std::pair<int, int> rangeToBeCut){
            Audio finalRangeAdded(*this);

            //Extracted so can use "+" operator to add whole ranges at once

            //Extract range from lhs audio object
            Audio audioWithRangeExtract1(*this);
            audioWithRangeExtract1.audioData.clear();
            audioWithRangeExtract1.audioData.resize(rangeToBeCut.second - rangeToBeCut.first);
            std::copy(audioData.begin()+rangeToBeCut.first,audioData.begin() + rangeToBeCut.second,audioWithRangeExtract1.audioData.begin());

            //Extract range from rhs audio object
            Audio audioWithRangeExtract2(rhs);
            audioWithRangeExtract2.audioData.clear();
            audioWithRangeExtract2.audioData.resize(rangeToBeCut.second - rangeToBeCut.first);
            std::copy(rhs.audioData.begin()+rangeToBeCut.first,rhs.audioData.begin() + rangeToBeCut.second,audioWithRangeExtract2.audioData.begin());

            //Add the ranges together
            Audio rangesAdded = audioWithRangeExtract1 + audioWithRangeExtract2;
            //Copy new range into original copy
            std::copy(rangesAdded.audioData.begin(),rangesAdded.audioData.end(),finalRangeAdded.audioData.begin()+rangeToBeCut.first);

            return finalRangeAdded;
        }

        /*
         * For test class - Checks if two Audio classes are exactly the same
         */
        bool operator==(const Audio &rhs){
            return (audioData == rhs.audioData)
                   && (channels == rhs.channels)
                   && (sampleRateInHz == rhs.sampleRateInHz)
                   && (numberOfSamples == rhs.numberOfSamples)
                   && (lengthOfAudioSeconds == rhs.lengthOfAudioSeconds);
        }

        /*
         * Function to reverse the order which the alements are ordered in audio data
         */
        void reverse(){
            std::reverse(audioData.begin(),audioData.end());
        }

        /*
         * Compute RMS for each channel - average volume of the sound clip
         */
        float computeRMS(){
            float init =0.0; //Using all floats so as not incur loss of accuracy
            float accumSum = std::accumulate(audioData.begin(), audioData.end(), init,
                            [](float sumOf,const BitType& audioElement){
                                return (sumOf + ( pow(audioElement,2) )); //Increment sum by square of audioElement
                            }
            );
            accumSum = (float) sqrt(accumSum / ((float) numberOfSamples) );
            return accumSum;
        }

        /*
         * Function to normalize the volume of audio data
         */
        Audio &normalize(float desiredRMS){
            float currentRMS = computeRMS();
            std::transform(audioData.begin(),audioData.end(),audioData.begin(),Normalize(desiredRMS,currentRMS) );
            return *this;
        }

        //Normalize functor for mono
        class Normalize{
        private:
            float desired;
            float current;
        public:
            Normalize(float d, float c): desired(d),current(c){ }
            BitType operator()(BitType inputAmp){
                BitType outputAmp = (BitType) (inputAmp * (desired/current));
                if ( outputAmp > std::numeric_limits<BitType>::max()){ //Clamps to max of int8 or int16
                    outputAmp = std::numeric_limits<BitType>::max();
                }
                return outputAmp;
            }
        };

        /*
         * Extra credit
         * Function to fade in to class audio smoothly
         */
        Audio &fadeIn(float numSecondsForFade){
            float rampLength = numSecondsForFade * sampleRateInHz;
            float FadeInSampleNo = 0.0; // To know what current sample index on in transform method
            std::transform(audioData.begin(),audioData.end(),audioData.begin(), //Changes values of audioData array
                          [rampLength,&FadeInSampleNo](BitType inputAmp){
                              BitType outputAmp = ( ( FadeInSampleNo/rampLength) *((float)inputAmp) ); //Apply fade
                              if (FadeInSampleNo< rampLength){ // Only apply fade if in fade in region
                                  FadeInSampleNo++;
                              }
                              else{
                                  FadeInSampleNo = rampLength; //ensures doesn't apply fade  i.e 1/1 *inputAmp occurs
                              }
                              return outputAmp;
                          }
            );
            return *this;
        }

        /*
         * Extra credit
         * Function to fade out to class audio smoothly
         */
        Audio &fadeOut(float numSecondsForFade){
            float rampLength = numSecondsForFade * sampleRateInHz;
            float startSample = numberOfSamples - rampLength;
            int i = 0;

            float FadeInSampleNo = 0.0; // To know what current sample index on in transform method
            std::transform(audioData.begin(),audioData.end(),audioData.begin(), //Changes values of audioData array
                           [rampLength,&FadeInSampleNo,&i,&startSample](BitType inputAmp){
                               BitType outputAmp = ( (1.0 - ( FadeInSampleNo/rampLength) ) *((float)inputAmp) ); //Apply fade
                               if( i > startSample){ //apply fade only at end of sample
                                   FadeInSampleNo++;
                               }
                               i++;
                               return outputAmp;
                           }
            );
            return *this;
        }

    };

    template <typename BitType>
    class Audio<std::pair<BitType,BitType>>{
    private:
        std::vector<std::pair<BitType,BitType>> audioData;
        int channels;
        int sampleRateInHz;
        int numberOfSamples;
        int lengthOfAudioSeconds;

        /*
         * Loads audio file using binary reading
         */
        void loadAudio(const std::string &fileName){
            std::ifstream input(fileName,std::ios::binary| std::ios::in); //get file in binary

            if (input.is_open()){
                long fileSize =  filesize(fileName);
                this->numberOfSamples = fileSize/( sizeof(BitType) * channels);
                this->lengthOfAudioSeconds = (int) (numberOfSamples / ((float) sampleRateInHz));

                audioData.resize(numberOfSamples); //Reserve space for samples

                for (int i = 0; i < numberOfSamples; ++i) {
                    char buffer[sizeof(BitType)];
                    BitType sample;
                    input.read((char *) &sample, sizeof(BitType)); //read in sample

                    char buffer2[sizeof(BitType)];
                    BitType sampleR;
                    input.read((char *) &sampleR, sizeof(BitType)); //read in sample right ear

                    audioData[i] = (std::make_pair(sample, sampleR)); // will be pair<intN_t,intN_t>(sample,sampleR);
                }
                input.close();
                //return audioData;
            }
            else{
                std::cout<<"Error: Can't open file"<<std::endl;
                exit(0);
            }

        }

    public:
        //Main constructor
        Audio(const std::string &fileName, int &chan, int &rate)  : channels(chan), sampleRateInHz(rate){
            loadAudio(fileName);
        }

        //constructor
        Audio(int samples,int length, std::vector<std::pair<BitType,BitType>> vec, int &chan, int &rate)
                : channels(chan), sampleRateInHz(rate), numberOfSamples(samples),lengthOfAudioSeconds(length),audioData(vec){
        }

        //Copy constructor
        Audio(const Audio &rhs): channels(rhs.channels),sampleRateInHz(rhs.sampleRateInHz)
                ,numberOfSamples(rhs.numberOfSamples),lengthOfAudioSeconds(rhs.lengthOfAudioSeconds),audioData(rhs.audioData){ }

        /*
         * Saves the audio data into file
         */
        void saveAudio(const std::string &outFileName) {
            std::string fullName = outFileName + "_"  + std::to_string(sampleRateInHz) + "_" + std::to_string(sizeof(BitType)*8) + "_stereo.raw";
            std::ofstream output(fullName,std::ios::binary | std::ios::out);

            if (output.is_open()){
                for (int i = 0; i < audioData.size(); ++i) {
                    output.write(reinterpret_cast<const char *>(&audioData[i].first), sizeof(BitType)); //sizeof(BitType));
                    output.write(reinterpret_cast<const char *>(&audioData[i].second), sizeof(BitType));
                }
            }
            else{
                std::cout<<"Could not write to File"<<std::endl;
                exit(0);
            }
        }

        /*
         * Returns the size of the file
         */
        long filesize(const std::string &filename){
            std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
            return (long) in.tellg();
        }

        /*
         * Concatenates two audio's together
         * -Joins audio vectors together - rhs added onto end of lhs
         */
        Audio operator|(const Audio &rhs) {
            Audio concatenated(*this);
            //add elements starting from the beginning of rhs data to end of concatanet audio
            concatenated.audioData.insert(concatenated.audioData.end(),rhs.audioData.begin(),rhs.audioData.end());
            //Adjust lengths
            concatenated.lengthOfAudioSeconds = concatenated.lengthOfAudioSeconds + rhs.lengthOfAudioSeconds;
            concatenated.numberOfSamples = concatenated.numberOfSamples + rhs.numberOfSamples;
            return concatenated;
        }

        /*
         * Increases audio by a volume factor - Can be diff for L/R (Stereo)
         */
        Audio operator*(std::pair<float, float> volumeFactor) {
            Audio concatenated(*this);
            //Lambda function to increase audio data by pairs
            std::transform(this->audioData.begin(),this->audioData.end(),concatenated.audioData.begin(),
                           [volumeFactor](std::pair<BitType,BitType> value){
                               return std::make_pair(value.first*volumeFactor.first,value.second*volumeFactor.second);
                           }
            );
            return concatenated;
        }

        /*
         * Adds sound aplitudes together
         * - adds two audio vectors together and clamps on maximum
         */
        Audio operator+(const Audio &rhs) {
            Audio concatenated(*this);
            //Lambda function to increase audio data
            for (int i = 0; i < audioData.size(); ++i) {
                BitType sumOfSoundLeft = audioData[i].first + rhs.audioData[i].first; //adds em up
                if (sumOfSoundLeft > std::numeric_limits<BitType>::max()){ //clamp on left
                    sumOfSoundLeft = std::numeric_limits<BitType>::max();
                }

                BitType sumOfSoundRight = audioData[i].second + rhs.audioData[i].second;
                if (sumOfSoundRight > std::numeric_limits<BitType>::max()){ //clamp on right
                    sumOfSoundRight = std::numeric_limits<BitType>::max();
                }
                concatenated.audioData[i].first = sumOfSoundLeft;
                concatenated.audioData[i].second = sumOfSoundRight;
            }
            //concatenated.audioData.insert(concatenated.audioData.end(),rhs.audioData.begin(),rhs.audioData.end());
            return concatenated;
        }

        /*
         * Cuts out a range of samples from audio
         */
        Audio operator^(std::pair<int, int> rangeToBeCut) {
            //Create all new variables as will be a diff number of samples and length - Can't just copy as diff vals
            int numSamplesWithCutOuts = numberOfSamples - (rangeToBeCut.second - rangeToBeCut.first) -1;
            int cutLength = (int) (numSamplesWithCutOuts / ((float) sampleRateInHz));
            std::vector<std::pair<BitType,BitType>> cutAudioData;
            for (int i = 0; i < audioData.size(); ++i) {
                if ( i < rangeToBeCut.first || i>rangeToBeCut.second){
                    cutAudioData.push_back(audioData[i]); //don't know index so use push back
                }
            }

            //Create cut out audio object
            Audio<std::pair<BitType,BitType>> audioWithCutOut(numSamplesWithCutOuts,cutLength,cutAudioData,channels,sampleRateInHz);
            return audioWithCutOut;
        }

        /*
         * Function to reverse the order which the alements are ordered in audio data
         */
        void reverse(){
            std::reverse(audioData.begin(),audioData.end());
        }

        /*
         * For test class - Checks if two Audio classes are exactly the same
         */
        bool operator==(const Audio &rhs){
            return (audioData == rhs.audioData)
                   && (channels == rhs.channels)
                   && (sampleRateInHz == rhs.sampleRateInHz)
                   && (numberOfSamples == rhs.numberOfSamples)
                   && (lengthOfAudioSeconds == rhs.lengthOfAudioSeconds);
        }

        /*
         * Function to select two (same length) sample ranges from two signals and add them together
         */
        Audio rangeAdd(const Audio &rhs,std::pair<int, int> rangeToBeCut){
            Audio finalRangeAdded(*this);

            //Extracted so can use "+" operator to add whole ranges at once

            //Extract range from lhs audio object
            Audio audioWithRangeExtract1(*this);
            audioWithRangeExtract1.audioData.clear();
            audioWithRangeExtract1.audioData.resize(rangeToBeCut.second - rangeToBeCut.first);
            std::copy(audioData.begin()+rangeToBeCut.first,audioData.begin() + rangeToBeCut.second,audioWithRangeExtract1.audioData.begin());

            //Extract range from rhs audio object
            Audio audioWithRangeExtract2(rhs);
            audioWithRangeExtract2.audioData.clear();
            audioWithRangeExtract2.audioData.resize(rangeToBeCut.second - rangeToBeCut.first);
            std::copy(rhs.audioData.begin()+rangeToBeCut.first,rhs.audioData.begin() + rangeToBeCut.second,audioWithRangeExtract2.audioData.begin());

            //Add the ranges together
            Audio rangesAdded = audioWithRangeExtract1 + audioWithRangeExtract2;
            //Copy new range into original copy
            std::copy(rangesAdded.audioData.begin(),rangesAdded.audioData.end(),finalRangeAdded.audioData.begin()+rangeToBeCut.first);

            return finalRangeAdded;
        }

        /*
         * Compute RMS for each channel - average volume of the sound clip
         */
        std::pair<float,float> computeRMS(){
            //Using all floats so as not incur loss of accuracy
            std::pair<float,float> init = {0.0,0.0};
            std::pair<float,float> accumSum = std::accumulate(audioData.begin(), audioData.end(), init,
                                             [](std::pair<float,float> sumOf,std::pair<BitType,BitType> audioElement){
                                                 sumOf.first = sumOf.first + pow(audioElement.first,2);
                                                 sumOf.second = sumOf.second + pow(audioElement.second,2);
                                                 return sumOf; //Increment sum by square of audioElement
                                             }
            );
            accumSum.first = (float) sqrt(accumSum.first / ((float) numberOfSamples) );
            accumSum.second = (float) sqrt(accumSum.second / ((float) numberOfSamples) );
            return accumSum;
        }

        /*
         * Function to normalize the volume of audio data
         */
        Audio &normalize(std::pair<float, float> desiredRMS){
            std::pair<float,float> currentRMS = computeRMS();
            std::transform(audioData.begin(),audioData.end(),audioData.begin(),Normalize(desiredRMS,currentRMS) );
            return *this;
        }

        //Normalize functor for stereo
        class Normalize{
        private:
            std::pair<float,float> desired;
            std::pair<float,float> current;
        public:
            Normalize(std::pair<float,float> d, std::pair<float,float> c): desired(d),current(c){ }
            std::pair<BitType,BitType> operator()(std::pair<BitType,BitType> inputAmp){
                BitType outputAmpL = (BitType) (inputAmp.first * (desired.first/current.first)); //normalized amp
                BitType outputAmpR = (BitType) (inputAmp.second * (desired.second/current.second));

                if ( outputAmpL > std::numeric_limits<BitType>::max()){ //Clamps to max of int8 or int16
                    outputAmpL = std::numeric_limits<BitType>::max();
                }
                if ( outputAmpR > std::numeric_limits<BitType>::max()){ //Clamps to max of int8 or int16
                    outputAmpR = std::numeric_limits<BitType>::max();
                }
                return {outputAmpL,outputAmpR}; //return pair ouput amps
            }
        };

        /*
         * Extra credit
         * Function to fade in to class audio smoothly
         */
        Audio &fadeIn(float numSecondsForFade){
            float rampLength = numSecondsForFade * sampleRateInHz;
            float FadeInSampleNo = 0.0; // To know what current sample index on in transform method
            std::transform(audioData.begin(),audioData.end(),audioData.begin(), //Changes values of audioData array
                           [rampLength,&FadeInSampleNo](std::pair<BitType,BitType> inputAmp){
                               BitType outputAmpL = ( ( FadeInSampleNo/rampLength) *((float)inputAmp.first) ); //Apply fade
                               BitType outputAmpR = ( ( FadeInSampleNo/rampLength) *((float)inputAmp.second) ); //Apply fade
                               if (FadeInSampleNo< rampLength){ // Only apply fade if in fade in region
                                   FadeInSampleNo++;
                               }
                               else{
                                   FadeInSampleNo = rampLength; //ensures doesn't apply fade  i.e 1/1 *inputAmp occurs
                               }
                               std::pair<BitType,BitType> toReturn = std::make_pair(outputAmpL,outputAmpR);
                               return toReturn;
                           }
            );
            return *this;
        }

        /*
         * Extra credit
         * Function to fade out to class audio smoothly
         */
        Audio &fadeOut(float numSecondsForFade){
            float rampLength = numSecondsForFade * sampleRateInHz;
            float startSample = numberOfSamples - rampLength;
            int i = 0;

            float FadeInSampleNo = 0.0; // To know what current sample index on in transform method
            std::transform(audioData.begin(),audioData.end(),audioData.begin(), //Changes values of audioData array
                           [rampLength,&FadeInSampleNo,&i,&startSample](std::pair<BitType,BitType> inputAmp){
                               BitType outputAmpL = ( (1.0 - ( FadeInSampleNo/rampLength) ) *((float)inputAmp.first) ); //Apply fade
                               BitType outputAmpR = ( (1.0 - ( FadeInSampleNo/rampLength) ) *((float)inputAmp.second) ); //Apply fade
                               if( i > startSample){ //apply fade only at end of sample
                                   FadeInSampleNo++;
                               }
                               i++;
                               std::pair<BitType,BitType> toReturn = std::make_pair(outputAmpL,outputAmpR);
                               return toReturn;
                           }
            );
            return *this;
        }


    };

}


#endif //ASSIGNMENT_5_SCRSHA001_AUDIO_H
