//
// Created by Shaaheen on 4/29/2016.
//

#include "Audio.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

namespace SCRSHA001{
//    template <typename BitType,typename ChannelType>
//    std::vector<ChannelType> Audio<BitType,ChannelType>::loadAudio(const std::string &fileName) {
//        ifstream input(fileName,ios::binary| ios::in); //get file in binary
//
//        if (input.is_open()){
//            long fileSize =  filesize(fileName);
//            this->numberOfSamples = fileSize/( sizeof(BitType) * channels);
//            this->lengthOfAudioSeconds = (int) (numberOfSamples / ((float) sampleRateInHz));
//
//            audioData.resize(numberOfSamples);
//
//            for (int i = 0; i < numberOfSamples; ++i) {
//                BitType sample;
//                input.read(sample, sizeof(BitType)); //read in sample
//                if (channels == 2){
//                    BitType sampleR;
//                    input.read(sampleR, sizeof(BitType)); //read in sample right ear
//                    audioData[i] = BitType(sample,sampleR); // will be pair<intN_t,intN_t>(sample,sampleR)
//                }
//                else{
//                    audioData[i] = BitType(sample); //int(sample)
//                }
//            }
//            input.close();
//            return audioData;
//        }
//        else{
//            cout<<"Error: Can't open file"<<endl;
//            exit(0);
//        }
//
//    }

//    template <typename BitType,typename ChannelType>
//    void Audio<BitType,ChannelType>::saveAudio(const string & outFileName) const{
//        ofstream output(outFileName,std::ios::binary | std::ios::out);
//
//        if (output.is_open()){
//            output.write(&audioData[0],numberOfSamples*channels);
////            for (int i = 0; i < audioData.size(); ++i) {
////                if (channels)
////                //output.write(audioData[i])
////            }
//        }
//        else{
//            cout<<"Could not write to File"<<endl;
//            exit(0);
//        }
//
//    }

//    template <typename BitType,typename ChannelType>
//    long Audio<BitType,ChannelType>::filesize(const string & filename)
//    {
//        std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
//        return (long) in.tellg();
//    }
}
