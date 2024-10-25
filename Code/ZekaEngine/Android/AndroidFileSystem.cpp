#include "AndroidFileSystem.h"
#include "AndroidEngine.h"

ZK_NAMESPACE_BEGIN

AndroidFile::AndroidFile(const char* name, FileAccess access)
  : File(name, access)
{
  AndroidEngine* engine = static_cast<AndroidEngine*>(Engine::Get());

  m_Asset = AAssetManager_open(engine->GetAssetManager(), name, AASSET_MODE_RANDOM);
}

AndroidFile::~AndroidFile()
{
}

uint32 AndroidFile::Read(void* dst, uint64 size)
{
  const uint64 tmp = AAsset_read(m_Asset, dst, size);
  return tmp;
}

uint32 AndroidFile::Write(const void* src, uint64 size)
{
  return 0;
}

void AndroidFile::Close()
{
  if (m_Asset)
  {
    AAsset_close(m_Asset);
    m_Asset = nullptr;
  }
}

uint32 AndroidFile::GetSize() const
{
  return AAsset_getLength(m_Asset);
}

uint32 AndroidFile::GetPosition() const
{
  return AAsset_seek(m_Asset, 0, SEEK_CUR);
}

void AndroidFile::SetPosition(uint32 seek)
{
  AAsset_seek(m_Asset, (off_t)seek, SEEK_SET);
}

bool AndroidFile::IsOpened() const
{
  return m_Asset != nullptr;
}

File* OpenFile(const char* filename, FileAccess access)
{
  return new AndroidFile(filename, access);
}

ZK_NAMESPACE_END
