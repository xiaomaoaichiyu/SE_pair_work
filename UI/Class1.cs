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

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void AddLine(int x1, int y1, int x2, int y2);

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveLine(int x1, int y1, int x2, int y2);

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void AddRay(int x1, int y1, int x2, int y2);

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveRay(int x1, int y1, int x2, int y2);

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void AddSection(int x1, int y1, int x2, int y2);

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveSection(int x1, int y1, int x2, int y2);

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void AddCircle(int x, int y, int r);

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveCircle(int x, int y, int r);

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetIntersectionsSize();

        [DllImport("_core.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetIntersections(double[] xs, double[] ys, int size);



    }
}
