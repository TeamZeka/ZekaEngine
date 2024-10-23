#include "FontTool.h"
#include "FileSystem.h"

ZK_NAMESPACE_BEGIN

Font* FontTool::ImportFont(const char* filename, const FontOptions& options)
{
  File* file = OpenFile(filename, FileAccess::Read);

  const uint32 size = file->GetSize();
  uint8* data = new uint8[size];
  file->Read(data, size);

  return new Font(data, size, options);
}

ZK_NAMESPACE_END