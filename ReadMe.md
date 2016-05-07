Hey :)

To run: 
    1) Go into directory from terminal
    2) Run "make" command in terminal to compile the program
    3) run ./samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>] soundFile1 [soundFile2] 
		command from terminal (Descriptions for operations below)
	4) Result will be outputted to given outfile name or the default "out" name if no outpute file specified
		(RMS op just prints to screen)
	
To run unit tests:
	1) Go into test directory from terminal
	2) Run "make" command in terminal to compile unit test program
	3) run ./unitTests command from terminal
	4) Should execute all tests (takes time)
	
//Concatenates countdown sound and siren sound into one long audio object and outputs this to the default "out" file name
//Also 44100 sample rate, 8bit audio and mono all specified too 
eg: ./samp -r 44100 -b 8bit -c 1  -cat sample_input/countdown40sec_44100_signed_8bit_mono.raw sample_input/siren40sec_44100_signed_8bit_mono.raw

[-o outFileName] is optional - Defaults to an outfile named "out" if not specified

<ops> is ONE of the following:
• -add: add soundFile1 and soundFile2 (Amplitudes added)
• -cut r1 r2: remove samples over range [r1,r2] (inclusive) (assumes one sound file)
• -radd r1 r2 s1 s2 : add soundFile1 and soundFile2 over sub-ranges indicated (in seconds). The ranges must be equal in length
• -cat: concatenate soundFile1 and soundFile2 - One large audio file with both audios
• -v r1 [r2]: Audio increased by volume factor -r is a floating point number (one sound file assumed)
			- IF MONO THEN ONLY ONE VOLUME NEEDED, only if stereo provide two volume factors
• -rev: reverse sound file (assumes one sound file only)
• -rms: Prints out the RMS of the soundfile (assumes one sound file only).
• -norm r1 [r2]: normalize file for audio (assumes one sound file only and that r1 and r2 are floating point RMS values)
			- IF MONO THEN ONLY ONE normalized rms NEEDED, only if stereo provide two volume factors
• [EXTRA CREDIT] -fadein n: n is the number of seconds (floating point number) to slowly increase the volume (from 0) at 
the start of soundFile1 (assumes one sound file).
• [EXTRA CREDIT] -fadeout n: n is the number of seconds (floating point number) to slowly decrease the volume (from 1.0 to 0) 
at the end of soundFile1 (assumes one sound file). 


main.cpp:
	Driver class to run program

Audio.h:
	implementation of audio class - All in header as this is a limitation of using template classes
	
test\AudioUnitTests.cpp:
	Implementation of Unit tests to evaluate Audio object
	
All expected answers to test cases can be found in the tests\expectedOutputForTests folder
These output files were verified to be correct and then compared with whatever the audio class would output
	

	