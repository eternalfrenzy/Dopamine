#pragma once

#include <string>

class WAVEData
{
private:
	std::string filepath = "";
private:
	short channelCount = 0;
	int sampleRate = 0;
	int sampleCount = 0;
	int byteRate = 0;
	short bitsPerSample = 0;
private:
	bool isValid = true;
	enum
	{
		SUCCESS,
		NO_PATH_PASSED_TO_CONSTRUCTOR,
		FILE_OPEN_FAILED,
		RIFF_CHECK_FAILED,
		WAVE_CHECK_FAILED,
		FMT_CHECK_FAILED,
		DATA_CHECK_FAILED
	} validCode = SUCCESS;
private:
	struct WAVHeader
	{
		char chunkID[4];
		unsigned int chunkSize;
		char format[4];
		char subchunk1ID[4];
		unsigned int subchunk1Size;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned int sampleRate;
		unsigned int byteRate;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char subchunk2ID[4];
		unsigned int subchunk2Size;
	};
private:
	bool SigVerify(char* sig, char* value);
public:
	WAVEData();
	WAVEData(std::string filePath);
public:
	short GetChannelCount();
	int GetSampleRate();
	int GetSampleCount();
	int GetByteRate();
	short GetBitsPerSample();
public:
	int GetDurationMs();
	float GetDurationSeconds();
public:
	std::string GetFilePath();
public:
	bool IsValid();
	int GetValidCode();
	std::string ValidCodeText(int code);
public:
	std::string ToString(bool newline);
};