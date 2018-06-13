using System;
using System.Runtime.CompilerServices;

namespace Igneous
{
    struct Version
    {
        public const int Major = 0;
        public const int Minor = 0;
        public const int Patch = 2;
    }

    public static class Test
    {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void Run();
    }
}
