#ifndef _H_WINDOWS_FILE_SYSTEM
#define _H_WINDOWS_FILE_SYSTEM

#include "ZekaEngine/FileSystem.h"
#include "IncludeWindowsHeaders.h"

ZK_NAMESPACE_BEGIN

class WindowsFile : public File
{
public:
  WindowsFile(const char* name, FileAccess access);
  ~WindowsFile();

  uint32 Read(void* dst, uint64 size) override;
  uint32 Write(const void* src, uint64 size) override;
  void Close() override;
  uint32 GetSize() const override;
  uint32 GetPosition() const override;
  void SetPosition(uint32 seek) override;
  bool IsOpened() const override;
private:
  HANDLE m_Handle;
};

ZK_NAMESPACE_END

#endif
