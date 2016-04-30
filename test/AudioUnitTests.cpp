//
// Created by Shaaheen on 4/29/2016.
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../Audio.h"

using namespace std;
using namespace SCRSHA001;

TEST_CASE("Type tests"){
    cout<< sizeof(pair<int16_t,int16_t>)<<endl;
    cout<< sizeof(int16_t)<<endl;


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
        Audio<int8_t,int8_t> audTest = Audio<int8_t,int8_t>(fileName,channel,rate);
        audTest.saveAudio("sampM");
    }
    SECTION("Stereo test"){
        string fileName = "sample_input/countdown40sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<int16_t, pair<int16_t,int16_t>> audTest = Audio<int16_t, pair<int16_t,int16_t>>(fileName,channel,rate);
        audTest.saveAudio("sampS");
    }
}
TEST_CASE("Concatanate test"){

    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t,int8_t> audTest = Audio<int8_t,int8_t>(fileName,channel,rate);

        string fileName2 = "sample_input/frogs18sec_44100_signed_8bit_mono.raw";
        int channe2 = 1;
        int rate2 = 44100;
        Audio<int8_t,int8_t> audTest2 = Audio<int8_t,int8_t>(fileName2,channe2,rate2);

        Audio<int8_t,int8_t> resultAuds = audTest | audTest2;

        string testFile = "test/testCases/ConcatenTest_44100_8_mono.raw";
        Audio<int8_t,int8_t> expectedAudio = Audio<int8_t,int8_t>(testFile,channe2,rate2);

        REQUIRE((resultAuds == expectedAudio) == true);
    }
    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<int16_t, pair<int16_t,int16_t>> audTest = Audio<int16_t, pair<int16_t,int16_t>>(fileName,channel,rate);

        string fileName2 = "sample_input/frogs18sec_44100_signed_16bit_stereo.raw";
        int channe2 = 2;
        int rate2 = 44100;
        Audio<int16_t, pair<int16_t,int16_t>> audTest2 = Audio<int16_t, pair<int16_t,int16_t>>(fileName2,channe2,rate2);

        Audio<int16_t, pair<int16_t,int16_t>> resultAuds = audTest | audTest2;

        string testFile = "test/testCases/ConcatenTestS_44100_16_stereo.raw";
        Audio<int16_t, pair<int16_t,int16_t>> expectedAudio = Audio<int16_t, pair<int16_t,int16_t>>(testFile,channe2,rate2);

        REQUIRE((expectedAudio == resultAuds) == true);
    }
}
TEST_CASE("Volume test"){
    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t,int8_t> audTest = Audio<int8_t,int8_t>(fileName,channel,rate);
        pair<float,float> volumes = make_pair(5.0,0.0);
        //(audTest * volumes).saveAudio("VolumeTest");

        Audio<int8_t,int8_t> resultAuds = audTest *volumes;

        string testFile = "test/testCases/VolumeTest_44100_8_mono.raw";
        Audio<int8_t,int8_t> expectedAudio = Audio<int8_t,int8_t>(testFile,channel,rate);

        REQUIRE((resultAuds == expectedAudio) == true);
    }

    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<int16_t, pair<int16_t,int16_t>> audTest = Audio<int16_t, pair<int16_t,int16_t>>(fileName,channel,rate);
        pair<float,float> volumes = make_pair(5.0,0.0);
        //(audTest * volumes).saveAudio("VolumeTestS");

        Audio<int16_t, pair<int16_t,int16_t>> resultAuds = audTest *volumes;

        string testFile = "test/testCases/VolumeTestS_44100_16_stereo.raw";
        Audio<int16_t, pair<int16_t,int16_t>> expectedAudio = Audio<int16_t, pair<int16_t,int16_t>>(testFile,channel,rate);

        REQUIRE((expectedAudio == resultAuds) == true);
    }
}
TEST_CASE("Addition test"){
    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t,int8_t> audTest = Audio<int8_t,int8_t>(fileName,channel,rate);

        string fileName2 = "sample_input/frogs18sec_44100_signed_8bit_mono.raw";
        int channe2 = 1;
        int rate2 = 44100;
        Audio<int8_t,int8_t> audTest2 = Audio<int8_t,int8_t>(fileName2,channe2,rate2);

        //(audTest + audTest2).saveAudio("AdditionTest");

        Audio<int8_t,int8_t> resultAuds = audTest + audTest2;

        string testFile = "test/testCases/AdditionTest_44100_8_mono.raw";
        Audio<int8_t,int8_t> expectedAudio = Audio<int8_t,int8_t>(testFile,channel,rate);

        REQUIRE((resultAuds == expectedAudio) == true);
    }


    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<int16_t, pair<int16_t,int16_t>> audTest = Audio<int16_t, pair<int16_t,int16_t>>(fileName,channel,rate);

        string fileName2 = "sample_input/frogs18sec_44100_signed_16bit_stereo.raw";
        int channe2 = 2;
        int rate2 = 44100;
        Audio<int16_t, pair<int16_t,int16_t>> audTest2 = Audio<int16_t, pair<int16_t,int16_t>>(fileName2,channe2,rate2);

        //(audTest + audTest2).saveAudio("AdditionTestS");

        Audio<int16_t, pair<int16_t,int16_t>> resultAuds = audTest + audTest2;

        string testFile = "test/testCases/AdditionTestS_44100_16_stereo.raw";
        Audio<int16_t, pair<int16_t,int16_t>> expectedAudio = Audio<int16_t, pair<int16_t,int16_t>>(testFile,channe2,rate2);

        REQUIRE((expectedAudio == resultAuds) == true);
    }
}
TEST_CASE("Cut out test"){
    SECTION("Mono test"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t,int8_t> audTest = Audio<int8_t,int8_t>(fileName,channel,rate);
        pair<int,int> range = make_pair(0,200000);
        //(audTest ^ range).saveAudio("CutOutTest");

        Audio<int8_t,int8_t> resultAuds = audTest ^ range;

        string testFile = "test/testCases/CutOutTest_44100_8_mono.raw";
        Audio<int8_t,int8_t> expectedAudio = Audio<int8_t,int8_t>(testFile,channel,rate);

        REQUIRE((resultAuds == expectedAudio) == true);
    }

    SECTION("Stereo test"){
        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
        int channel = 2;
        int rate = 44100;
        Audio<int16_t, pair<int16_t,int16_t>> audTest = Audio<int16_t, pair<int16_t,int16_t>>(fileName,channel,rate);
        pair<int,int> range = make_pair(0,300000);
        //(audTest ^ range).saveAudio("CutOutTestS");

        Audio<int16_t, pair<int16_t,int16_t>> resultAuds = audTest ^ range;

        string testFile = "test/testCases/CutOutTestS_44100_16_stereo.raw";
        Audio<int16_t, pair<int16_t,int16_t>> expectedAudio = Audio<int16_t, pair<int16_t,int16_t>>(testFile,channel,rate);

        REQUIRE((expectedAudio == resultAuds) == true);
    }
}
TEST_CASE("Reverse test"){
    SECTION("Mono"){
        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
        int channel = 1;
        int rate = 44100;
        Audio<int8_t,int8_t> audTest = Audio<int8_t,int8_t>(fileName,channel,rate);
        (audTest.reverse());
        audTest.saveAudio("Reversed");
    }
}