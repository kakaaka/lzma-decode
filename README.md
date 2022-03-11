# lzma-decode
lzma decode part of LZMA SDK
 
Used for Unity Plugin.<br>
The C# implementation of LZMA SDK is too slow. 


In Unity use like this:
 
```c#
using System;
using System.Runtime.InteropServices;

public class Lzma
{
   public delegate void CallbackDelegate(int insize, int size);
#if (UNITY_IOS || UNITY_IPHONE)
    [DllImport("__Internal")]
#else
    [DllImport("lzma", EntryPoint = "LzmaUncompress")]
#endif
    internal static extern int LzmaUncompress(IntPtr source, int sourceLen, IntPtr dest, int destLen, CallbackDelegate uprogress);

    public static byte[] Decode(byte[] inBuffer,CallbackDelegate uprogress = null)
    {
        GCHandle cbuf = GCHandle.Alloc(inBuffer, GCHandleType.Pinned);

        int uncompressedSize = (int)BitConverter.ToUInt64(inBuffer, 5);
        byte[] outbuffer = new byte[uncompressedSize];

        GCHandle obuf = GCHandle.Alloc(outbuffer, GCHandleType.Pinned);

        LzmaUncompress(cbuf.AddrOfPinnedObject(), inBuffer.Length, obuf.AddrOfPinnedObject(), uncompressedSize, uprogress);

        cbuf.Free();
        obuf.Free();

        return outbuffer;
    }
}
```
