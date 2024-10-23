#ifndef _H_AUDIO_DECODER
#define _H_AUDIO_DECODER

#include "FileSystem.h"
#include "Audio.h"

#include <minimp3.h>

ZK_NAMESPACE_BEGIN

class AudioDecoder
{
public:
  AudioDecoder() {}
  ~AudioDecoder() {}

  virtual bool Read(File* file, std::vector<uint8>& bytes) = 0;
  
  uint32 GetBitDepth() const;
  uint32 GetNumSamples() const;
  uint32 GetSampleRate() const;
  uint32 GetNumChannels() const;
  uint32 GetBytesPerSample() const;
  uint32 GetDataSize() const;
protected:
  uint32 m_BitDepth;
  uint32 m_NumSamples;
  uint32 m_NumChannels;
  uint32 m_SampleRate;
};

struct WavHeader 
{
  uint8 RiffHeader[4]; // Contains "RIFF"
  uint32 WavSize; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
  uint8 WaveHeader[4]; // Contains "WAVE"

  uint8 FmtHeader[4]; // Contains "fmt " (includes trailing space)
  uint32 FmtChunkSize; // Should be 16 for PCM
  uint16 AudioFormat; // Should be 1 for PCM. 3 for IEEE Float
  uint16 NumChannels;
  uint32 SampleRate;
  uint32 ByteRate; // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
  uint16 SampleAlignment; // num_channels * Bytes Per Sample
  uint16 BitDepth; // Number of bits per sample

  uint8 DataHeader[4]; // Contains "data"
  uint32 DataBytes; // Number of bytes in data. Number of samples * num_channels * sample byte size
};

class WavDecoder : public AudioDecoder
{
public:
  WavDecoder();
  ~WavDecoder();

  bool Read(File* stream, std::vector<uint8>& bytes) override;
};

class MP3Decoder : public AudioDecoder
{
public:
  MP3Decoder();
  ~MP3Decoder();

  bool Read(File* stream, std::vector<uint8>& bytes) override;
private:
  mp3dec_t mp3d;
};

ZK_NAMESPACE_END

#endif
