//
// Created by Shaaheen on 4/29/2016.
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../Audio.h"

using namespace std;
using namespace SCRSHA001;

TEST_CASE("Type tests"){
    cout<<"Loading tests..."<<endl;


    ofstream output("Test.raw",std::ios::binary | std::ios::out);
    if (output.is_open()){
        //output.write(pair<int,int>(7,6), sizeof(pair<int,int>));
    }
}

TEST_CASE("Save and load"){
    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t> originalAudioLoaded = Audio<int8_t>(fileName,channel,rate); //Load function called here

        originalAudioLoaded.saveAudio("sampM"); //Save function
        string fileNameOfSavedFile = "sampM_44100_8_mono.raw";
        Audio<int8_t> audioFromSavedFile = Audio<int8_t>(fileNameOfSavedFile,channel,rate);

        REQUIRE(originalAudioLoaded== audioFromSavedFile); //Overloaded "==" operator to allow comparison of audio

    }
    SECTION("Stereo test"){
        string fileName = "sample_input/countdown40sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<pair<int16_t,int16_t>> originalAudioLoaded = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);

        originalAudioLoaded.saveAudio("sampS"); //Save function
        string fileNameOfSavedFile = "sampS_44100_16_stereo.raw";
        Audio<pair<int16_t,int16_t>> audioFromSavedFile = Audio<pair<int16_t,int16_t>>(fileNameOfSavedFile,channel,rate);

        REQUIRE(originalAudioLoaded== audioFromSavedFile); //Overloaded "==" operator to allow comparison of audio

        cout<<"Save and load test done"<<endl;
    }

}

TEST_CASE("Concatanate test"){

    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);

        string fileName2 = "sample_input/frogs18sec_44100_signed_8bit_mono.raw";
        int channe2 = 1;
        int rate2 = 44100;
        Audio<int8_t> audTest2 = Audio<int8_t>(fileName2,channe2,rate2);

        Audio<int8_t> resultAuds = audTest | audTest2;

        string testFile = "test/testCases/ConcatenTest_44100_8_mono.raw";
        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channe2,rate2);

        REQUIRE(resultAuds == expectedAudio);
    }
    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);

        string fileName2 = "sample_input/frogs18sec_44100_signed_16bit_stereo.raw";
        int channe2 = 2;
        int rate2 = 44100;
        Audio<pair<int16_t,int16_t>> audTest2 = Audio<pair<int16_t,int16_t>>(fileName2,channe2,rate2);

        Audio<pair<int16_t,int16_t>> resultAuds = audTest | audTest2;

        string testFile = "test/testCases/ConcatenTestS_44100_16_stereo.raw";
        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channe2,rate2);

        REQUIRE((expectedAudio == resultAuds) == true);
        cout<<"Concatanate test done"<<endl;
    }

}

TEST_CASE("Volume test"){
    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);
        pair<float,float> volumes = make_pair(5.0,0.0);
        //(audTest * volumes).saveAudio("VolumeTest");

        Audio<int8_t> resultAuds = audTest *volumes;

        string testFile = "test/testCases/VolumeTest_44100_8_mono.raw";
        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);

        REQUIRE((resultAuds == expectedAudio) == true);
    }

    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
        pair<float,float> volumes = make_pair(5.0,0.0);
        //(audTest * volumes).saveAudio("VolumeTestS");

        Audio<pair<int16_t,int16_t>> resultAuds = audTest *volumes;

        string testFile = "test/testCases/VolumeTestS_44100_16_stereo.raw";
        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);

        REQUIRE((expectedAudio == resultAuds) == true);
        cout<<"Volume test done"<<endl;
    }

}

TEST_CASE("Addition test"){
    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);

        string fileName2 = "sample_input/frogs18sec_44100_signed_8bit_mono.raw";
        int channe2 = 1;
        int rate2 = 44100;
        Audio<int8_t> audTest2 = Audio<int8_t>(fileName2,channe2,rate2);

        //(audTest + audTest2).saveAudio("AdditionTest");

        Audio<int8_t> resultAuds = audTest + audTest2;

        string testFile = "test/testCases/AdditionTest_44100_8_mono.raw";
        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);

        REQUIRE((resultAuds == expectedAudio) == true);
    }
    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);

        string fileName2 = "sample_input/frogs18sec_44100_signed_16bit_stereo.raw";
        int channe2 = 2;
        int rate2 = 44100;
        Audio<pair<int16_t,int16_t>> audTest2 = Audio<pair<int16_t,int16_t>>(fileName2,channe2,rate2);

        //(audTest + audTest2).saveAudio("AdditionTestS");

        Audio<pair<int16_t,int16_t>> resultAuds = audTest + audTest2;

        string testFile = "test/testCases/AdditionTestS_44100_16_stereo.raw";
        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channe2,rate2);

        REQUIRE((expectedAudio == resultAuds) == true);
        cout<<"Addition test done"<<endl;
    }

}

TEST_CASE("Cut out test"){
    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);
        pair<int,int> range = make_pair(0,200000);
        //(audTest ^ range).saveAudio("CutOutTest");

        Audio<int8_t> resultAuds = audTest ^ range;

        string testFile = "test/testCases/CutOutTest_44100_8_mono.raw";
        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);

        REQUIRE((resultAuds == expectedAudio) == true);
    }

    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
        pair<int,int> range = make_pair(0,300000);
        //(audTest ^ range).saveAudio("CutOutTestS");

        Audio<pair<int16_t,int16_t>> resultAuds = audTest ^ range;

        string testFile = "test/testCases/CutOutTestS_44100_16_stereo.raw";
        Audio< pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);

        REQUIRE((expectedAudio == resultAuds) == true);
        cout<<"Cut out test done"<<endl;
    }

}

TEST_CASE("Reverse test"){
    SECTION("Mono"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);
        (audTest.reverse());

        string testFile = "test/testCases/Reversed_44100_8_mono.raw";
        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);

        REQUIRE((expectedAudio == audTest) == true);

    }
    SECTION("Stereo"){
        //todo do this quick test case

        cout<<"Reverse test done"<<endl;
    }

}

TEST_CASE("Range added test"){
    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);

        string fileName2 = "sample_input/countdown40sec_44100_signed_8bit_mono.raw";
        int channe2 = 1;
        int rate2 = 44100;
        Audio<int8_t> audTest2 = Audio<int8_t>(fileName2,channe2,rate2);

        pair<int,int> range = make_pair(200000,400000);
        Audio<int8_t> rangeAddedResult = audTest.rangeAdd(audTest2,range);

        string testFile = "test/testCases/RangeAdded_44100_8_mono.raw";
        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);

        REQUIRE((expectedAudio == rangeAddedResult) == true);
    }
    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);

        string fileName2 = "sample_input/countdown40sec_44100_signed_16bit_stereo.raw";
        int channe2 = 2;
        int rate2 = 44100;
        Audio<pair<int16_t,int16_t>> audTest2 = Audio<pair<int16_t,int16_t>>(fileName2,channe2,rate2);

        pair<int,int> range = make_pair(200000,400000);
        Audio<pair<int16_t,int16_t>> rangeAddedResult = audTest.rangeAdd(audTest2,range);

        string testFile = "test/testCases/RangeAddedS_44100_16_stereo.raw";
        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);

        REQUIRE((expectedAudio == rangeAddedResult) == true);
        cout<<"Range added test done"<<endl;
    }

}

TEST_CASE("Compute RMS test"){
    SECTION("Mono test"){
        string fileName2 = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channe2 = 1;
        int rate2 = 44100;
        Audio<int8_t> audTest = Audio<int8_t>(fileName2,channe2,rate2);
        float calculatedRMS = audTest.computeRMS();

        float expectedRMS = 5.77678585;

        REQUIRE(expectedRMS == calculatedRMS);
    }
    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);

        pair<float,float> RMSresult = audTest.computeRMS();
        float expectedRMSLeft = 1642.01855;
        float expectedRMSRight = 1516.70569;

        REQUIRE(RMSresult.first == expectedRMSLeft);
        REQUIRE(RMSresult.second == expectedRMSRight);

        cout<<"Compute RMS test done"<<endl;
    }

}

TEST_CASE("Normalization test"){
    SECTION("Mono test"){
        string fileName2 = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channe2 = 1;
        int rate2 = 44100;
        Audio<int8_t> audTest = Audio<int8_t>(fileName2,channe2,rate2);

        Audio<int8_t> normalizedResult = audTest.normalize(10);

        string testFile = "test/testCases/NormalisedTest_44100_8_mono.raw";
        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channe2,rate2);

        REQUIRE((expectedAudio == normalizedResult) == true);
    }
    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);

        Audio<pair<int16_t,int16_t>> normalizedResult = audTest.normalize({5000.0,5000.0});

        string testFile = "test/testCases/NormalisedTestS_44100_16_stereo.raw";
        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);

        REQUIRE((expectedAudio == normalizedResult) == true);

        cout<<"Normalization test done"<<endl;
    }

}

TEST_CASE("Fading test - EXTRA CREDIT"){
    SECTION("Fade IN"){
        SECTION("Mono"){
            string fileName2 = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
            int channe2 = 1;
            int rate2 = 44100;
            Audio<int8_t> audTest = Audio<int8_t>(fileName2,channe2,rate2);
            Audio<int8_t> fadeInResult = audTest.fadeIn(10.0);

            string testFile = "test/testCases/FadeInTest_44100_8_mono.raw";
            Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channe2,rate2);

            REQUIRE((expectedAudio == fadeInResult) == true);
        }
        SECTION("Stereo"){
            string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
            int channel = 2;
            int rate = 44100;
            Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
            Audio<pair<int16_t,int16_t>> fadeInResult = audTest.fadeIn(5.0);


            string testFile = "test/testCases/FadeInTestS_44100_16_stereo.raw";
            Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);

            REQUIRE((expectedAudio == fadeInResult) == true);

            cout<<"Fade In test done"<<endl;
        }

    }
    SECTION("Fade Out"){
        SECTION("Mono"){
            string fileName2 = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
            int channe2 = 1;
            int rate2 = 44100;
            Audio<int8_t> audTest = Audio<int8_t>(fileName2,channe2,rate2);
            Audio<int8_t> fadeOutResult = audTest.fadeOut(10.0);

            string testFile = "test/testCases/FadeOutTest_44100_8_mono.raw";
            Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channe2,rate2);

            REQUIRE((expectedAudio == fadeOutResult) == true);
        }
        SECTION("Stereo"){
            string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
            int channel = 2;
            int rate = 44100;
            Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
            Audio<pair<int16_t,int16_t>> fadeOutResult = audTest.fadeOut(5.0);

            string testFile = "test/testCases/FadeOutTestS_44100_16_stereo.raw";
            Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);

            REQUIRE((expectedAudio == fadeOutResult) == true);

            cout<<"Fade Out test done"<<endl;
        }


    }
}