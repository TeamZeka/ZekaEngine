#ifndef _H_ENCRYPTION
#define _H_ENCRYPTION

#include "HelperDefines.h"

ZK_NAMESPACE_BEGIN

class Encryption
{
public:
  static void EncryptBytes(uint8* data, uint64 size);
  static void DecryptBytes(uint8* data, uint64 size);
};

ZK_NAMESPACE_END

#endif
