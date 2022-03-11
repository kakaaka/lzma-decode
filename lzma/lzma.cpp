#include "7zip\LzmaDec.h"
#include "7zip\Alloc.h"

#ifdef  _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API 
#endif

#define LZMA_PROPS_SIZE 5

extern "C"
{
	EXPORT_API int LzmaUncompress(Byte* src, SizeT srcLen, Byte* dest, SizeT destLen, Decode_Callback cb)
	{
		ELzmaStatus status;
		return LzmaDecode(dest, &destLen, src + LZMA_PROPS_SIZE + 8, &srcLen, src, LZMA_PROPS_SIZE, LZMA_FINISH_ANY, &status, &g_Alloc, cb);
	}
}