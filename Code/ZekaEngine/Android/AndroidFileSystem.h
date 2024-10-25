#ifndef _H_ANDROID_FILE_SYSTEM
#define _H_ANDROID_FILE_SYSTEM

#include "ZekaEngine/FileSystem.h"

#include <android/asset_manager.h>

ZK_NAMESPACE_BEGIN

class AndroidFile : public File
{
public:
  AndroidFile(const char* name, FileAccess access);
  ~AndroidFile();

  uint32 Read(void* dst, uint64 size) override;
  uint32 Write(const void* src, uint64 size) override;
  void Close() override;
  uint32 GetSize() const override;
  uint32 GetPosition() const override;
  void SetPosition(uint32 seek) override;
  bool IsOpened() const override;
private:
  AAsset* m_Asset;
};

ZK_NAMESPACE_END

#endif
