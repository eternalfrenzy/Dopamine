#include <fstream>
#include "WAVEData.h"

WAVEData::WAVEData()
{
	this->isValid = false;
	this->validCode = NO_PATH_PASSED_TO_CONSTRUCTOR;
	return;
}

WAVEData::WAVEData(std::string filePath)
{
	this->filepath = filePath;

	std::ifstream inWavFile = std::ifstream(filePath, std::ios::binary);
	if (!inWavFile || !inWavFile.is_open())
	{
		this->isValid = false;
		this->validCode = FILE_OPEN_FAILED;
		return;
	}

	WAVHeader* hdr = new WAVHeader();
	inWavFile.read((char*)hdr, sizeof(WAVHeader));

	if (!this->SigVerify(hdr->chunkID, "RIFF"))
	{
		this->isValid = false;
		this->validCode = RIFF_CHECK_FAILED;
		
		delete hdr;
		return;
	}

	if (!this->SigVerify(hdr->format, "WAVE"))
	{
		this->isValid = false;
		this->validCode = WAVE_CHECK_FAILED;

		delete hdr;
		return;
	}

	if (!this->SigVerify(hdr->subchunk1ID, "fmt "))
	{
		this->isValid = false;
		this->validCode = FMT_CHECK_FAILED;

		delete hdr;
		return;
	}

	if (!this->SigVerify(hdr->subchunk2ID, "data"))
	{
		this->isValid = false;
		this->validCode = DATA_CHECK_FAILED;

		delete hdr;
		return;
	}

	this->sampleRate = hdr->sampleRate;
	this->bitsPerSample = hdr->bitsPerSample;
	this->byteRate = hdr->byteRate;
	this->channelCount = hdr->numChannels;
	this->sampleCount = hdr->subchunk2Size / (hdr->bitsPerSample / 8) / hdr->numChannels;

	delete hdr;
}

bool WAVEData::SigVerify(char* sig, char* value)
{
	for (int i = 0; i < 4; i++)
	{
		if (sig[i] != value[i])
			return false;
	}

	return true;
}

short WAVEData::GetChannelCount()
{
	return this->channelCount;
}

int WAVEData::GetSampleRate()
{
	return this->sampleRate;
}

int WAVEData::GetSampleCount()
{
	return this->sampleCount;
}

int WAVEData::GetByteRate()
{
	return this->byteRate;
}

short WAVEData::GetBitsPerSample()
{
	return this->bitsPerSample;
}

int WAVEData::GetDurationMs()
{
	return (int)(this->GetDurationSeconds() * 1000.f);
}

float WAVEData::GetDurationSeconds()
{
	return (float)this->sampleCount / (float)this->sampleRate;
}

std::string WAVEData::GetFilePath()
{
	return this->filepath;
}

bool WAVEData::IsValid()
{
	return this->isValid;
}

int WAVEData::GetValidCode()
{
	return this->validCode;
}

std::string WAVEData::ValidCodeText(int code)
{
	if (this->isValid)
		return "No error";

	switch (code)
	{
		case(SUCCESS):
		{
			return "No error";
		}
		case(NO_PATH_PASSED_TO_CONSTRUCTOR):
		{
			return "No path was passed to WAVEData constructor";
		}
		case(FILE_OPEN_FAILED):
		{
			return "Failed to open source file";
		}
		case(RIFF_CHECK_FAILED):
		{
			return "Invalid RIFF file";
		}
		case(WAVE_CHECK_FAILED):
		{
			return "Invalid WAVE file";
		}
		case(FMT_CHECK_FAILED):
		{
			return "WAVE Format data not found";
		}
		case(DATA_CHECK_FAILED):
		{
			return "WAVE Sound data not found";
		}
	}

	return std::string(std::string("[!] Valid code ") + std::to_string(code) + std::string(" not found"));
}

std::string WAVEData::ToString(bool newline)
{
	std::string r = std::string(
		"WAVEData[" + this->filepath + "](" + this->ValidCodeText(this->validCode) + "){channelCount = " + std::to_string(this->channelCount) + "; sampleRate = " + std::to_string(this->sampleRate) + "; sampleCount = " + std::to_string(this->sampleCount) + "; byteRate = " + std::to_string(this->byteRate) + "; bitsPerSample = " + std::to_string(this->bitsPerSample) + ". Duration: " + std::to_string(this->GetDurationSeconds()) + "s (" + std::to_string(this->GetDurationMs()) + "ms)}"
	);

	if (newline)
	{
		r += std::string("\n");
	}

	return r;
}