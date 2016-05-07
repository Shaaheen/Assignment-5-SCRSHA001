//
// Created by Shaaheen on 4/29/2016.
//
//
//#define CATCH_CONFIG_MAIN
//#include "../catch.hpp"
//#include "../Audio.h"
//
//using namespace std;
//using namespace SCRSHA001;

//
//TEST_CASE("Special Member test"){
//    SECTION("Constructor"){
//        cout<<"Loading test..."<<endl;
//
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> originalAudioLoaded = Audio<int8_t>(fileName,channel,rate); //Load function called here
//
//        //Check if have properties as ones given
//        REQUIRE((originalAudioLoaded.getChannel() ==channel));
//        REQUIRE((originalAudioLoaded.getLengthInSecond() ==18));
//        REQUIRE((originalAudioLoaded.getNumberOfSamples() ==793800));
//        REQUIRE((originalAudioLoaded.getSampleRate() ==rate));
//
//    }
//    SECTION("Destructor"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//
//        Audio<int8_t> *originalAudioLoaded = new Audio<int8_t>(fileName,channel,rate); //Load function called here
//        delete originalAudioLoaded; //call destructor
//
//        //Check if data cleared
//        REQUIRE((originalAudioLoaded->getChannel() ==0));
//        REQUIRE((originalAudioLoaded->getLengthInSecond() ==0));
//        REQUIRE((originalAudioLoaded->getNumberOfSamples() ==0));
//        REQUIRE((originalAudioLoaded->getSampleRate() ==0));
//        REQUIRE(originalAudioLoaded->checkIfAudioEmpty());
//    }
//    SECTION("Copy/Move Constructors"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> originalAudioLoaded = Audio<int8_t>(fileName,channel,rate); //Load function called here
//
//        Audio<int8_t> copyOfAudio(originalAudioLoaded);
//        //"==" operator overloaded to compare audio classes
//        REQUIRE(originalAudioLoaded == copyOfAudio); // Check if audio's equal
//
//        Audio<int8_t> movedAudio(move(originalAudioLoaded));
//        REQUIRE(copyOfAudio == movedAudio); //Checks if moved audio equal to orig data(which stored in copy)
//
//        //Check if data cleared
//        REQUIRE((originalAudioLoaded.getChannel() ==0));
//        REQUIRE((originalAudioLoaded.getLengthInSecond() ==0));
//        REQUIRE((originalAudioLoaded.getNumberOfSamples() ==0));
//        REQUIRE((originalAudioLoaded.getSampleRate() ==0));
//        REQUIRE(originalAudioLoaded.checkIfAudioEmpty());
//    }
//    SECTION("Copy/Move Assignment operators"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> originalAudioLoaded = Audio<int8_t>(fileName,channel,rate); //Load function called here
//
//        Audio<int8_t> copyOfAudio = originalAudioLoaded;
//        //"==" operator overloaded to compare audio classes
//        REQUIRE(originalAudioLoaded == copyOfAudio); // Check if audio's equal
//
//        Audio<int8_t> movedAudio = move(originalAudioLoaded) ;
//        REQUIRE(copyOfAudio == movedAudio); //Checks if moved audio equal to orig data(which stored in copy)
//
//        //Check if data cleared
//        REQUIRE((originalAudioLoaded.getChannel() ==0));
//        REQUIRE((originalAudioLoaded.getLengthInSecond() ==0));
//        REQUIRE((originalAudioLoaded.getNumberOfSamples() ==0));
//        REQUIRE((originalAudioLoaded.getSampleRate() ==0));
//        REQUIRE(originalAudioLoaded.checkIfAudioEmpty());
//    }
//}
//
//TEST_CASE("Save and load"){
//    SECTION("Mono test"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> originalAudioLoaded = Audio<int8_t>(fileName,channel,rate); //Load function called here
//
//        originalAudioLoaded.saveAudio("sampM"); //Save function
//        string fileNameOfSavedFile = "sampM_44100_8_mono.raw";
//        Audio<int8_t> audioFromSavedFile = Audio<int8_t>(fileNameOfSavedFile,channel,rate);
//
//        REQUIRE(originalAudioLoaded== audioFromSavedFile); //Overloaded "==" operator to allow comparison of audio
//
//    }
//    SECTION("Stereo test"){
//        string fileName = "sample_input/countdown40sec_44100_signed_16bit_stereo.raw";
//        int channel = 2;
//        int rate = 44100;
//        Audio<pair<int16_t,int16_t>> originalAudioLoaded = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//
//        originalAudioLoaded.saveAudio("sampS"); //Save function
//        string fileNameOfSavedFile = "sampS_44100_16_stereo.raw";
//        Audio<pair<int16_t,int16_t>> audioFromSavedFile = Audio<pair<int16_t,int16_t>>(fileNameOfSavedFile,channel,rate);
//
//        REQUIRE(originalAudioLoaded== audioFromSavedFile); //Overloaded "==" operator to allow comparison of audio
//
//        cout<<"Save and load test done"<<endl;
//    }
//
//}
//
//TEST_CASE("Concatanate test"){
//
//    SECTION("Mono test"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);
//
//        string fileName2 = "sample_input/frogs18sec_44100_signed_8bit_mono.raw";
//        int channe2 = 1;
//        int rate2 = 44100;
//        Audio<int8_t> audTest2 = Audio<int8_t>(fileName2,channe2,rate2);
//
//        Audio<int8_t> resultAuds = audTest | audTest2; //concatanate here
//
//        //Get expected audio of a concatenated file from test case files
//        string testFile = "test/expectedOutputForTests/ConcatenTest_44100_8_mono.raw";
//        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channe2,rate2);
//
//        REQUIRE(resultAuds == expectedAudio); //compare expected concatenated audio with result
//    }
//    SECTION("Stereo test"){
//        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//        int channel = 2;
//        int rate = 44100;
//        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//
//        string fileName2 = "sample_input/frogs18sec_44100_signed_16bit_stereo.raw";
//        int channe2 = 2;
//        int rate2 = 44100;
//        Audio<pair<int16_t,int16_t>> audTest2 = Audio<pair<int16_t,int16_t>>(fileName2,channe2,rate2);
//
//        Audio<pair<int16_t,int16_t>> resultAuds = audTest | audTest2;
//
//        string testFile = "test/expectedOutputForTests/ConcatenTestS_44100_16_stereo.raw";
//        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channe2,rate2);
//
//        REQUIRE(expectedAudio == resultAuds);
//        cout<<"Concatanate test done"<<endl;
//    }
//
//}
//
//TEST_CASE("Volume test"){
//    SECTION("Mono test"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);
//        float volumes = 5.0; //Up volume by 5 times
//
//        Audio<int8_t> resultAuds = audTest *volumes; //apply volume up
//
//        //Get expected higher volume
//        string testFile = "test/expectedOutputForTests/VolumeTest_44100_8_mono.raw";
//        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);
//
//        REQUIRE(resultAuds == expectedAudio);
//    }
//
//    SECTION("Stereo test"){
//        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//        int channel = 2;
//        int rate = 44100;
//        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//        pair<float,float> volumes = make_pair(5.0,0.0);
//        //(audTest * volumes).saveAudio("VolumeTestS");
//
//        Audio<pair<int16_t,int16_t>> resultAuds = audTest *volumes;
//
//        string testFile = "test/expectedOutputForTests/VolumeTestS_44100_16_stereo.raw";
//        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);
//
//        REQUIRE((expectedAudio == resultAuds) == true);
//        cout<<"Volume test done"<<endl;
//    }
//
//}
//
//TEST_CASE("Addition test"){
//    SECTION("Mono test"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);
//
//        string fileName2 = "sample_input/frogs18sec_44100_signed_8bit_mono.raw";
//        int channe2 = 1;
//        int rate2 = 44100;
//        Audio<int8_t> audTest2 = Audio<int8_t>(fileName2,channe2,rate2);
//
//        Audio<int8_t> resultAuds = audTest + audTest2; //Add audios
//
//        //Get expected addition output
//        string testFile = "test/expectedOutputForTests/AdditionTest_44100_8_mono.raw";
//        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);
//
//        REQUIRE(resultAuds == expectedAudio);
//    }
//    SECTION("Stereo test"){
//        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//        int channel = 2;
//        int rate = 44100;
//        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//
//        string fileName2 = "sample_input/frogs18sec_44100_signed_16bit_stereo.raw";
//        int channe2 = 2;
//        int rate2 = 44100;
//        Audio<pair<int16_t,int16_t>> audTest2 = Audio<pair<int16_t,int16_t>>(fileName2,channe2,rate2);
//
//        //(audTest + audTest2).saveAudio("AdditionTestS");
//
//        Audio<pair<int16_t,int16_t>> resultAuds = audTest + audTest2;
//
//        string testFile = "test/expectedOutputForTests/AdditionTestS_44100_16_stereo.raw";
//        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channe2,rate2);
//
//        REQUIRE(expectedAudio == resultAuds);
//        cout<<"Addition test done"<<endl;
//    }
//
//}
//
//TEST_CASE("Cut out test"){
//    SECTION("Mono test"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);
//        pair<int,int> range = make_pair(0,200000); //Range to be cut is between 0 and 200 000
//
//        Audio<int8_t> resultAuds = audTest ^ range; //Cut out range
//
//        //Get expected cut audio
//        string testFile = "test/expectedOutputForTests/CutOutTest_44100_8_mono.raw";
//        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);
//
//        REQUIRE(resultAuds == expectedAudio);
//    }
//
//    SECTION("Stereo test"){
//        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//        int channel = 2;
//        int rate = 44100;
//        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//        pair<int,int> range = make_pair(0,300000);
//
//        Audio<pair<int16_t,int16_t>> resultAuds = audTest ^ range;
//
//        string testFile = "test/expectedOutputForTests/CutOutTestS_44100_16_stereo.raw";
//        Audio< pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);
//
//        REQUIRE(expectedAudio == resultAuds);
//        cout<<"Cut out test done"<<endl;
//    }
//
//}
//
//TEST_CASE("Reverse test"){
//    SECTION("Mono"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);
//        (audTest.reverse()); //Reverse audio
//
//        //Get expected reversed audio
//        string testFile = "test/expectedOutputForTests/Reversed_44100_8_mono.raw";
//        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);
//
//        REQUIRE(expectedAudio == audTest);
//
//    }
//    SECTION("Stereo"){
//        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//        int channel = 2;
//        int rate = 44100;
//        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//        (audTest.reverse());
//
//        string testFile = "test/expectedOutputForTests/ReversedS_44100_16_stereo.raw";
//        Audio< pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);
//
//        REQUIRE(expectedAudio == audTest);
//
//        cout<<"Reverse test done"<<endl;
//    }
//
//}
//
//TEST_CASE("Range added test"){
//    SECTION("Mono test"){
//        string fileName = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channel = 1;
//        int rate = 44100;
//        Audio<int8_t> audTest = Audio<int8_t>(fileName,channel,rate);
//
//        string fileName2 = "sample_input/countdown40sec_44100_signed_8bit_mono.raw";
//        int channe2 = 1;
//        int rate2 = 44100;
//        Audio<int8_t> audTest2 = Audio<int8_t>(fileName2,channe2,rate2);
//
//        pair<int,int> range = make_pair(200000,400000); //Range to add two audios together
//        Audio<int8_t> rangeAddedResult = audTest.rangeAdd(audTest2,range); //add ranges
//
//        //Get expected range added output
//        string testFile = "test/expectedOutputForTests/RangeAdded_44100_8_mono.raw";
//        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channel,rate);
//
//        REQUIRE(expectedAudio == rangeAddedResult);
//    }
//    SECTION("Stereo test"){
//        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//        int channel = 2;
//        int rate = 44100;
//        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//
//        string fileName2 = "sample_input/countdown40sec_44100_signed_16bit_stereo.raw";
//        int channe2 = 2;
//        int rate2 = 44100;
//        Audio<pair<int16_t,int16_t>> audTest2 = Audio<pair<int16_t,int16_t>>(fileName2,channe2,rate2);
//
//        pair<int,int> range = make_pair(200000,400000);
//        Audio<pair<int16_t,int16_t>> rangeAddedResult = audTest.rangeAdd(audTest2,range);
//
//        string testFile = "test/expectedOutputForTests/RangeAddedS_44100_16_stereo.raw";
//        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);
//
//        REQUIRE(expectedAudio == rangeAddedResult);
//        cout<<"Range added test done"<<endl;
//    }
//
//}
//
//TEST_CASE("Compute RMS test"){
//    SECTION("Mono test"){
//        string fileName2 = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channe2 = 1;
//        int rate2 = 44100;
//        Audio<int8_t> audTest = Audio<int8_t>(fileName2,channe2,rate2);
//        float calculatedRMS = audTest.computeRMS();
//
//        float expectedRMS = 5.77678585;
//
//        REQUIRE(expectedRMS == calculatedRMS);
//    }
//    SECTION("Stereo test"){
//        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//        int channel = 2;
//        int rate = 44100;
//        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//
//        pair<float,float> RMSresult = audTest.computeRMS();
//        float expectedRMSLeft = 1642.01855;
//        float expectedRMSRight = 1516.70569;
//
//        REQUIRE(RMSresult.first == expectedRMSLeft);
//        REQUIRE(RMSresult.second == expectedRMSRight);
//
//        cout<<"Compute RMS test done"<<endl;
//    }
//
//}
//
//TEST_CASE("Normalization test"){
//    SECTION("Mono test"){
//        string fileName2 = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//        int channe2 = 1;
//        int rate2 = 44100;
//        Audio<int8_t> audTest = Audio<int8_t>(fileName2,channe2,rate2);
//
//        Audio<int8_t> normalizedResult = audTest.normalize(10); //Normalize around 10
//
//        //Get expected normalized audio
//        string testFile = "test/expectedOutputForTests/NormalisedTest_44100_8_mono.raw";
//        Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channe2,rate2);
//
//        REQUIRE(expectedAudio == normalizedResult);
//    }
//    SECTION("Stereo test"){
//        string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//        int channel = 2;
//        int rate = 44100;
//        Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//
//        Audio<pair<int16_t,int16_t>> normalizedResult = audTest.normalize({5000.0,5000.0});
//
//        string testFile = "test/expectedOutputForTests/NormalisedTestS_44100_16_stereo.raw";
//        Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);
//
//        REQUIRE(expectedAudio == normalizedResult);
//
//        cout<<"Normalization test done"<<endl;
//    }
//
//}
//
//TEST_CASE("Fading test - EXTRA CREDIT"){
//    SECTION("Fade IN"){
//        SECTION("Mono"){
//            string fileName2 = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//            int channe2 = 1;
//            int rate2 = 44100;
//            Audio<int8_t> audTest = Audio<int8_t>(fileName2,channe2,rate2);
//            Audio<int8_t> fadeInResult = audTest.fadeIn(10.0); //Fade in for first 10 seconds
//
//            //Get expected fade in input
//            string testFile = "test/expectedOutputForTests/FadeInTest_44100_8_mono.raw";
//            Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channe2,rate2);
//
//            REQUIRE(expectedAudio == fadeInResult);
//        }
//        SECTION("Stereo"){
//            string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//            int channel = 2;
//            int rate = 44100;
//            Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//            Audio<pair<int16_t,int16_t>> fadeInResult = audTest.fadeIn(5.0); //Fade in till 5 second mark
//
//            string testFile = "test/expectedOutputForTests/FadeInTestS_44100_16_stereo.raw";
//            Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);
//
//            REQUIRE(expectedAudio == fadeInResult);
//
//            cout<<"Fade In test done"<<endl;
//        }
//
//    }
//    SECTION("Fade Out"){
//        SECTION("Mono"){
//            string fileName2 = "sample_input/beez18sec_44100_signed_8bit_mono.raw";
//            int channe2 = 1;
//            int rate2 = 44100;
//            Audio<int8_t> audTest = Audio<int8_t>(fileName2,channe2,rate2);
//            Audio<int8_t> fadeOutResult = audTest.fadeOut(10.0); //fade out from last 10 seconds
//
//            string testFile = "test/expectedOutputForTests/FadeOutTest_44100_8_mono.raw";
//            Audio<int8_t> expectedAudio = Audio<int8_t>(testFile,channe2,rate2);
//
//            REQUIRE(expectedAudio == fadeOutResult);
//        }
//        SECTION("Stereo"){
//            string fileName = "sample_input/beez18sec_44100_signed_16bit_stereo.raw";
//            int channel = 2;
//            int rate = 44100;
//            Audio<pair<int16_t,int16_t>> audTest = Audio<pair<int16_t,int16_t>>(fileName,channel,rate);
//            Audio<pair<int16_t,int16_t>> fadeOutResult = audTest.fadeOut(5.0); //fade out from last 5 seconds
//
//            string testFile = "test/expectedOutputForTests/FadeOutTestS_44100_16_stereo.raw";
//            Audio<pair<int16_t,int16_t>> expectedAudio = Audio<pair<int16_t,int16_t>>(testFile,channel,rate);
//
//            REQUIRE(expectedAudio == fadeOutResult);
//
//            cout<<"Fade Out test done"<<endl;
//        }
//
//
//    }
//}