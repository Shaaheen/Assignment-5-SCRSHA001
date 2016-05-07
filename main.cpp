#include <iostream>
#include "Audio.h"

int getIntFromArgs(char * arg); //Predeclaring function

float getFloatFromArgs(char * arg);

using namespace std;
using namespace SCRSHA001;

int main(int argc,char* argv[]) {
    //Check if right amount of arguments
    if (argc > 16 ||argc < 9){
        cout << "Incorrect arguments passed (Not enough or too little found) " <<endl;
    }
    else {
        cout << "| Audio manipulation program |" << endl;
        int sampleRate = getIntFromArgs(argv[3]);
        cout<<"|Sample Rate: "<<sampleRate<<" |";
        bool bit8 = (string(argv[5]) == "8bit"); //True if 8bit, False if not
        cout<<"Bits: "<<argv[5]<<" |";
        int channel = getIntFromArgs(argv[7]);
        cout<<"Channel: "<<channel<<" |";
        string outFileName = "out"; //default out file name
        int indexAtArgs = 8; //ops index here if no outfile chosen
        if (string(argv[8]) == "-o") {
            outFileName = argv[9];
            indexAtArgs = 10; //Move index forward to choose ops
        }
        cout<<"Output Filename: "<<outFileName<<endl;
        string opChosen = argv[indexAtArgs];
        cout<<"Operation chosen: "<<opChosen<<endl;

        if (opChosen == "-add"){
            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName 1: "<<inFileName<<endl;

            indexAtArgs++; //soundfile at next index
            string inFileName2 = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName 2: "<<inFileName2<<endl;

            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                Audio<int8_t> audioLoadedIn2 = Audio<int8_t>(inFileName2,channel,sampleRate);

                Audio<int8_t> addedAudio = audioLoadedIn + audioLoadedIn2;
                addedAudio.saveAudio(outFileName);
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                Audio<int16_t> audioLoadedIn2 = Audio<int16_t>(inFileName2,channel,sampleRate);

                Audio<int16_t> addedAudio = audioLoadedIn + audioLoadedIn2;
                addedAudio.saveAudio(outFileName);
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                Audio<pair<int8_t,int8_t>> audioLoadedIn2 = Audio<pair<int8_t,int8_t>>(inFileName2,channel,sampleRate);

                Audio<pair<int8_t,int8_t>> addedAudio = audioLoadedIn + audioLoadedIn2;
                addedAudio.saveAudio(outFileName);
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                Audio<pair<int16_t,int16_t>> audioLoadedIn2 = Audio<pair<int16_t,int16_t>>(inFileName2,channel,sampleRate);

                Audio<pair<int16_t,int16_t>> addedAudio = audioLoadedIn + audioLoadedIn2;
                addedAudio.saveAudio(outFileName);
            }else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }

        else if (opChosen == "-cut"){
            indexAtArgs++; //to get to first range bound
            int r1  = getIntFromArgs(argv[indexAtArgs]);

            indexAtArgs++;//to get to second range bound
            int r2 = getIntFromArgs(argv[indexAtArgs]);

            pair<int,int> cutOutRange = make_pair(r1,r2);

            cout<<"r1 and r2: "<<r1<<" "<<r2<<endl;

            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName "<<inFileName<<endl;

            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                Audio<int8_t> cutOutAudio = audioLoadedIn^cutOutRange;
                cutOutAudio.saveAudio(outFileName);
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                Audio<int16_t> cutOutAudio = audioLoadedIn^cutOutRange;
                cutOutAudio.saveAudio(outFileName);
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                Audio<pair<int8_t,int8_t>> cutOutAudio = audioLoadedIn^cutOutRange;
                cutOutAudio.saveAudio(outFileName);
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                Audio<pair<int16_t,int16_t>> cutOutAudio = audioLoadedIn^cutOutRange;
                cutOutAudio.saveAudio(outFileName);
            }
            else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }

        else if (opChosen == "-radd"){
            indexAtArgs++; //to get to first range bound
            int r1  = getIntFromArgs(argv[indexAtArgs]);

            indexAtArgs++;//to get to second range bound
            int r2 = getIntFromArgs(argv[indexAtArgs]);

            pair<int,int> cutOutRange = make_pair(r1,r2);

            cout<<"r1 and r2: "<<r1<<" "<<r2<<endl;

            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName 1: "<<inFileName<<endl;

            indexAtArgs++; //soundfile at next index
            string inFileName2 = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName 2: "<<inFileName2<<endl;

            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                Audio<int8_t> audioLoadedIn2 = Audio<int8_t>(inFileName2,channel,sampleRate);

                Audio<int8_t> addedAudio = audioLoadedIn.rangeAdd(audioLoadedIn2,cutOutRange);
                addedAudio.saveAudio(outFileName);
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                Audio<int16_t> audioLoadedIn2 = Audio<int16_t>(inFileName2,channel,sampleRate);

                Audio<int16_t> addedAudio = audioLoadedIn.rangeAdd(audioLoadedIn2,cutOutRange);
                addedAudio.saveAudio(outFileName);
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                Audio<pair<int8_t,int8_t>> audioLoadedIn2 = Audio<pair<int8_t,int8_t>>(inFileName2,channel,sampleRate);

                Audio<pair<int8_t,int8_t>> addedAudio = audioLoadedIn.rangeAdd(audioLoadedIn2,cutOutRange);
                addedAudio.saveAudio(outFileName);
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                Audio<pair<int16_t,int16_t>> audioLoadedIn2 = Audio<pair<int16_t,int16_t>>(inFileName2,channel,sampleRate);

                Audio<pair<int16_t,int16_t>> addedAudio = audioLoadedIn.rangeAdd(audioLoadedIn2,cutOutRange);
                addedAudio.saveAudio(outFileName);
            }
            else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }

        else if (opChosen == "-cat"){
            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName 1: "<<inFileName<<endl;

            indexAtArgs++; //soundfile at next index
            string inFileName2 = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName 2: "<<inFileName2<<endl;

            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                Audio<int8_t> audioLoadedIn2 = Audio<int8_t>(inFileName2,channel,sampleRate);

                Audio<int8_t> addedAudio = audioLoadedIn | audioLoadedIn2;
                addedAudio.saveAudio(outFileName);
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                Audio<int16_t> audioLoadedIn2 = Audio<int16_t>(inFileName2,channel,sampleRate);

                Audio<int16_t> addedAudio = audioLoadedIn | audioLoadedIn2;
                addedAudio.saveAudio(outFileName);
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                Audio<pair<int8_t,int8_t>> audioLoadedIn2 = Audio<pair<int8_t,int8_t>>(inFileName2,channel,sampleRate);

                Audio<pair<int8_t,int8_t>> addedAudio = audioLoadedIn | audioLoadedIn2;
                addedAudio.saveAudio(outFileName);
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                Audio<pair<int16_t,int16_t>> audioLoadedIn2 = Audio<pair<int16_t,int16_t>>(inFileName2,channel,sampleRate);

                Audio<pair<int16_t,int16_t>> addedAudio = audioLoadedIn | audioLoadedIn2;
                addedAudio.saveAudio(outFileName);
            }
            else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }
        else if (opChosen == "-v"){
            indexAtArgs++; //to get to first volumefactor
            float v1  = getFloatFromArgs(argv[indexAtArgs]);

            pair<int,int> volumeFactorPair; //ONLY PAIR IF STEREO CHANNEL
            if (channel ==2){
                indexAtArgs++;
                float v2 = getFloatFromArgs(argv[indexAtArgs]);
                volumeFactorPair = make_pair(v1,v2);
            }

            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName "<<inFileName<<endl;

            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                Audio<int8_t> cutOutAudio = audioLoadedIn * v1;
                cutOutAudio.saveAudio(outFileName);
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                Audio<int16_t> cutOutAudio = audioLoadedIn * v1;
                cutOutAudio.saveAudio(outFileName);
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                Audio<pair<int8_t,int8_t>> cutOutAudio = audioLoadedIn * volumeFactorPair;
                cutOutAudio.saveAudio(outFileName);
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                Audio<pair<int16_t,int16_t>> cutOutAudio = audioLoadedIn * volumeFactorPair;
                cutOutAudio.saveAudio(outFileName);
            }
            else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }
        else if (opChosen == "-rms"){
            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName "<<inFileName<<endl;
            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                float rms = audioLoadedIn.computeRMS();
                cout<<"RMS is: "<< rms<<endl;
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                cout<<"RMS is: "<<audioLoadedIn.computeRMS()<<endl;
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                cout<<"RMS for Left side audio is: "<<audioLoadedIn.computeRMS().first<<endl;
                cout<<"RMS for Right side audio is: "<<audioLoadedIn.computeRMS().second<<endl;
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                cout<<"RMS for Left side audio is: "<<audioLoadedIn.computeRMS().first<<endl;
                cout<<"RMS for Right side audio is: "<<audioLoadedIn.computeRMS().second<<endl;
            }
            else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }

        else if (opChosen == "-rev"){
            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName "<<inFileName<<endl;
            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                audioLoadedIn.reverse();
                audioLoadedIn.saveAudio(outFileName);
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                audioLoadedIn.reverse();
                audioLoadedIn.saveAudio(outFileName);
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                audioLoadedIn.reverse();
                audioLoadedIn.saveAudio(outFileName);
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                audioLoadedIn.reverse();
                audioLoadedIn.saveAudio(outFileName);
            }
            else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }

        else if (opChosen == "-norm"){
            indexAtArgs++; //to get to first normalization rms
            float r1  = getFloatFromArgs(argv[indexAtArgs]);

            pair<int,int> normalizationRMPair ; //ONLY PAIR IF STEREO CHANNEL
            if (channel ==2){
                indexAtArgs++;
                float r2 = getFloatFromArgs(argv[indexAtArgs]);
                normalizationRMPair = make_pair(r1,r2);
            }

            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName "<<inFileName<<endl;

            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                Audio<int8_t> cutOutAudio = audioLoadedIn.normalize(r1);
                cutOutAudio.saveAudio(outFileName);
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                Audio<int16_t> cutOutAudio = audioLoadedIn.normalize(r1);
                cutOutAudio.saveAudio(outFileName);
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                Audio<pair<int8_t,int8_t>> cutOutAudio = audioLoadedIn.normalize(normalizationRMPair);
                cutOutAudio.saveAudio(outFileName);
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                Audio<pair<int16_t,int16_t>> cutOutAudio = audioLoadedIn.normalize(normalizationRMPair);
                cutOutAudio.saveAudio(outFileName);
            }
            else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }

        else if (opChosen == "-fadein"){
            indexAtArgs++; //to get to first normalization rms
            int n  = getIntFromArgs(argv[indexAtArgs]);

            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName "<<inFileName<<endl;

            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                Audio<int8_t> cutOutAudio = audioLoadedIn.fadeIn(n);
                cutOutAudio.saveAudio(outFileName);
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                Audio<int16_t> cutOutAudio = audioLoadedIn.fadeIn(n);
                cutOutAudio.saveAudio(outFileName);
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                Audio<pair<int8_t,int8_t>> cutOutAudio = audioLoadedIn.fadeIn(n);
                cutOutAudio.saveAudio(outFileName);
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                Audio<pair<int16_t,int16_t>> cutOutAudio = audioLoadedIn.fadeIn(n);
                cutOutAudio.saveAudio(outFileName);
            }
            else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }
        else if (opChosen == "-fadeout"){
            indexAtArgs++; //to get to first normalization rms
            int n  = getIntFromArgs(argv[indexAtArgs]);

            indexAtArgs++; //soundfile at next index
            string inFileName = argv[indexAtArgs]; //get input sound file
            cout<<"inFileName "<<inFileName<<endl;

            if (bit8 && (channel==1)){ //8bit and Mono
                Audio<int8_t> audioLoadedIn = Audio<int8_t>(inFileName,channel,sampleRate);
                Audio<int8_t> cutOutAudio = audioLoadedIn.fadeOut(n);
                cutOutAudio.saveAudio(outFileName);
            }else if (!bit8 && (channel == 1)){ //16bit and Mono
                Audio<int16_t> audioLoadedIn = Audio<int16_t>(inFileName,channel,sampleRate);
                Audio<int16_t> cutOutAudio = audioLoadedIn.fadeOut(n);
                cutOutAudio.saveAudio(outFileName);
            }
            else if(bit8 && (channel==2)){ //8bit and Stereo
                Audio<pair<int8_t,int8_t>> audioLoadedIn = Audio<pair<int8_t,int8_t>>(inFileName,channel,sampleRate);
                Audio<pair<int8_t,int8_t>> cutOutAudio = audioLoadedIn.fadeOut(n);
                cutOutAudio.saveAudio(outFileName);
            }
            else if(!bit8 && (channel==2)){ //16bit and Stereo
                Audio<pair<int16_t,int16_t>> audioLoadedIn = Audio<pair<int16_t,int16_t>>(inFileName,channel,sampleRate);
                Audio<pair<int16_t,int16_t>> cutOutAudio = audioLoadedIn.fadeOut(n);
                cutOutAudio.saveAudio(outFileName);
            }
            else{
                cout<<"Incorrect bit or channel input"<<endl;
                exit(0);
            }
        }
        else{
            cout<<"Operation chosen does not exist"<<endl; //exits straight away if incorrect op chosen
            exit(0);
        }
        cout<<"Operation complete."<<endl;
    }
    return 0;
}

int getIntFromArgs(char * arg){
    stringstream argString(arg);
    int threshold;
    argString >>threshold;
    return threshold;
}
float getFloatFromArgs(char * arg){
    stringstream argString(arg);
    float threshold;
    argString >>threshold;
    return threshold;
}