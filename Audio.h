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

namespace SCRSHA001{
    //Generic params BitType : int8_t or int16_t ChannelType: intN_t or pair<intN_t,intN_t>
    template <typename BitType,typename ChannelType>

    class Audio{
    private:
        std::vector<ChannelType> audioData;
        int channels;
        int sampleRateInHz;
        int numberOfSamples;
        int lengthOfAudioSeconds;

        void loadAudio(const std::string &fileName){
            std::ifstream input(fileName,std::ios::binary| std::ios::in); //get file in binary

            if (input.is_open()){
                long fileSize =  filesize(fileName);
                this->numberOfSamples = fileSize/( sizeof(BitType) * channels);
                this->lengthOfAudioSeconds = (int) (numberOfSamples / ((float) sampleRateInHz));

                audioData.resize(numberOfSamples);

                for (int i = 0; i < numberOfSamples; ++i) {
                    char buffer[sizeof(BitType)];
                    BitType sample;
                    input.read((char *) buffer, sizeof(BitType)); //read in sample
                    //sample =
                    if (channels == 2){
                        char buffer2[sizeof(BitType)];
                        BitType sampleR;
                        input.read((char *) buffer2, sizeof(BitType)); //read in sample right ear

                        //audioData[i] = (ChannelType) std::make_pair(buffer , buffer2); // will be pair<intN_t,intN_t>(sample,sampleR)
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

        long filesize(const std::string &filename){
            std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
            return (long) in.tellg();
        }

    public:
        Audio(const std::string &fileName, int &chan, int &rate)  : channels(chan), sampleRateInHz(rate){
            loadAudio(fileName);
        }

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
    };

    template <typename BitType> class Audio<BitType,std::pair<BitType,BitType>>{

    };
}

#endif //ASSIGNMENT_5_SCRSHA001_AUDIO_H
