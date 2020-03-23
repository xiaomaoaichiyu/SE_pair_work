using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace WindowsFormsApp1
{
    class Class1
    {
        [DllImport("core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void getPoint(double[] x, double[] y, int[] size);

        [DllImport("core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void addLine(char l, int x1, int y1, int x2, int y2);

        [DllImport("core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void delLine(char l, int x1, int y1, int x2, int y2);

        [DllImport("core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void addCircle(int x, int y, int r);


        [DllImport("core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void delCircle(int x, int y, int r);

        [DllImport("core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getResultOfIntersect();

    }
}
