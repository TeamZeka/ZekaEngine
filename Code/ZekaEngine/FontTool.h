#ifndef _H_FONT_TOOL
#define _H_FONT_TOOL

#include "Font.h"

ZK_NAMESPACE_BEGIN

class FontTool
{
public:
  static Font* ImportFont(const char* filename, const FontOptions& options);
};

ZK_NAMESPACE_END

#endif
