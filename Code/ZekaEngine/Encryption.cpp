#include "Encryption.h"

ZK_NAMESPACE_BEGIN

void Encryption::EncryptBytes(uint8* data, uint64 size)
{
  uint8 offset = 71;
  for (uint64 i = 0; i < size; i++)
  {
    data[i] = (data[i] ^ (uint8)i) + offset;
    offset += 13;
  }
}

void Encryption::DecryptBytes(uint8* data, uint64 size)
{
  uint8 offset = 71;
  for (uint64 i = 0; i < size; i++)
  {
    data[i] = data[i] - offset ^ (uint8)i;
    offset += 13;
  }
}

ZK_NAMESPACE_END
