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
    [DllImport("lzma", EntryPoint = "LzmaUncompress")]
    internal static extern int LzmaUncompress(IntPtr source, int sourceLen, IntPtr dest, int destLen);

    public static byte[] Decode(byte[] inBuffer)
    {
        GCHandle cbuf = GCHandle.Alloc(inBuffer, GCHandleType.Pinned);

        int uncompressedSize = (int)BitConverter.ToUInt64(inBuffer, 5);
        byte[] outbuffer = new byte[uncompressedSize];

        GCHandle obuf = GCHandle.Alloc(outbuffer, GCHandleType.Pinned);

        LzmaUncompress(cbuf.AddrOfPinnedObject(), inBuffer.Length, obuf.AddrOfPinnedObject(), uncompressedSize);

        cbuf.Free();
        obuf.Free();

        return outbuffer;
    }
}
```
