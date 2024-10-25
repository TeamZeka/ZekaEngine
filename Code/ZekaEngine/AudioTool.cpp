#include "AudioTool.h"

ZK_NAMESPACE_BEGIN

AudioBuffer* AudioTool::ImportAudio(const char* filename)
{
  File* file = OpenFile(filename, FileAccess::Read);

  std::vector<uint8> bytes;
  
  // there is only wav support yet
  WavDecoder decoder;
  decoder.Read(file, bytes);
  file->Close();

  AudioData data;
  data.BytesPerSample = decoder.GetBytesPerSample();
  data.NumChannels = decoder.GetNumChannels();
  data.NumSamples = decoder.GetNumSamples();
  data.SampleRate = decoder.GetSampleRate();

  AudioBuffer* buffer = CreateAudioBuffer();
  buffer->Write(bytes.data(), bytes.size(), data);
  return buffer;
}

ZK_NAMESPACE_END
