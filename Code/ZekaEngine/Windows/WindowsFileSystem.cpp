#include "WindowsFileSystem.h"

ZK_NAMESPACE_BEGIN

WindowsFile::WindowsFile(const char* name, FileAccess access)
  : File(name, access)
{
  if (access == FileAccess::Write) 
  {
    m_Handle = ::CreateFileA(name, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  }
  if (access == FileAccess::Read)
  {
    m_Handle = ::CreateFileA(name, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
  }
}

WindowsFile::~WindowsFile()
{
}

uint32 WindowsFile::Read(void* dst, uint64 size)
{
  DWORD readed = 0;
  ::ReadFile(m_Handle, dst, (DWORD)size, (LPDWORD)&readed, nullptr);
  return (uint32)readed;
}

uint32 WindowsFile::Write(const void* src, uint64 size)
{
  uint64 written = 0;
  ::WriteFile(m_Handle, src, (DWORD)size, (LPDWORD)&written, nullptr);
  return (uint32)written;
}

void WindowsFile::Close()
{
  if (m_Handle)
  {
    CloseHandle(m_Handle);
    m_Handle = NULL;
  }
}

uint32 WindowsFile::GetSize() const
{
  return ::GetFileSize(m_Handle, 0);
}

uint32 WindowsFile::GetPosition() const
{
  return ::SetFilePointer(m_Handle, 0, nullptr, FILE_CURRENT);
}

void WindowsFile::SetPosition(uint32 seek)
{
  LARGE_INTEGER dist;
  dist.QuadPart = seek;
  ::SetFilePointer(m_Handle, dist.u.LowPart, &dist.u.HighPart, FILE_BEGIN);
}

bool WindowsFile::IsOpened() const
{
  return m_Handle != INVALID_HANDLE_VALUE;
}

File* OpenFile(const char* name, FileAccess access)
{
  return new WindowsFile(name, access);
}

ZK_NAMESPACE_END
