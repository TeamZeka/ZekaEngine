#include "AudioDecoder.h"

#define MINIMP3_IMPLEMENTATION
#include <minimp3.h>

ZK_NAMESPACE_BEGIN

uint32 AudioDecoder::GetBitDepth() const 
{ 
  return m_BitDepth; 
}

uint32 AudioDecoder::GetNumSamples() const 
{ 
  return m_NumSamples; 
}

uint32 AudioDecoder::GetSampleRate() const 
{ 
  return m_SampleRate; 
}

uint32 AudioDecoder::GetNumChannels() const 
{ 
  return m_NumChannels; 
}

uint32 AudioDecoder::GetBytesPerSample() const 
{ 
  return m_BitDepth / 8;
}

uint32 AudioDecoder::GetDataSize() const
{
  return m_NumSamples * m_NumChannels * GetBytesPerSample();
}

WavDecoder::WavDecoder()
{
}

WavDecoder::~WavDecoder()
{
}

bool WavDecoder::Read(File* stream, std::vector<uint8>& bytes)
{
  WavHeader header;
  stream->Read(&header, sizeof(WavHeader));
  
  m_BitDepth = header.BitDepth;
  m_NumChannels = header.NumChannels;
  m_SampleRate = header.SampleRate;
  m_NumSamples = header.DataBytes / (m_NumChannels * GetBytesPerSample());

  uint32 size = header.DataBytes;
  
  bytes.resize(size);
  stream->Read(bytes.data(), size);
  return true;
}

MP3Decoder::MP3Decoder()
{
  mp3dec_init(&mp3d);
}

MP3Decoder::~MP3Decoder()
{
}

bool MP3Decoder::Read(File* stream, std::vector<uint8>& bytes)
{
  uint32 dataSize = stream->GetSize();
  std::vector<uint8> dataBytes;
  dataBytes.resize(dataSize);
  uint8* data = dataBytes.data();
  stream->Read(data, dataSize);

  m_NumChannels = 0;
  m_NumSamples = 0;
  m_SampleRate = 0;
  m_BitDepth = 16;

  mp3dec_frame_info_t mp3Info;
  short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];
  do
  {
    const int32 samples = mp3dec_decode_frame(&mp3d, data, dataSize, pcm, &mp3Info);
    if (samples)
    {
      m_NumSamples += samples * mp3Info.channels;

      bytes.insert(bytes.end(), pcm, pcm + samples * 2 * mp3Info.channels);

      if (!m_SampleRate)
      {
        m_SampleRate = mp3Info.hz;
      }
      if (!m_NumChannels)
      {
        m_NumChannels = mp3Info.channels;
      }
      if (m_SampleRate != mp3Info.hz || m_NumChannels != mp3Info.channels)
      {
        break;
      }
    }
    data += mp3Info.frame_bytes;
    dataSize -= mp3Info.frame_bytes;
  } while (mp3Info.frame_bytes);

  return true;
}

ZK_NAMESPACE_END
