#ifndef _H_FILE_SYSTEM
#define _H_FILE_SYSTEM

#include "HelperDefines.h"

ZK_NAMESPACE_BEGIN

enum class FileAccess : uint32
{
  Read = 0,
  Write
};

class File
{
public:
  File(const char* name, FileAccess access) {}
  ~File() {}

  virtual uint32 Read(void* dst, uint64 size) { return false; }
  virtual uint32 Write(const void* src, uint64 size) { return false; }
  virtual void Close() {}
  virtual uint32 GetSize() const { return 0; }
  virtual uint32 GetPosition() const { return 0; }
  virtual void SetPosition(uint32 seek) {}
  virtual bool IsOpened() const { return false; }
};

File* OpenFile(const char* name, FileAccess access);

ZK_NAMESPACE_END

#endif
