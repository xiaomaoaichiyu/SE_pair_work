using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Intersect : Form
    {
        int length = 500;
        int n = 20;
        float k;
        public Intersect()
        {
            InitializeComponent();
        }

        void add(string line)
        {
            string[] points = line.Split(' ');       // 拆分当前行
            if (points[0].Equals("L") || points[0].Equals("R") || points[0].Equals("S"))
            {
                int.TryParse(points[1], out int x1);
                int.TryParse(points[2], out int y1);
                int.TryParse(points[3], out int x2);
                int.TryParse(points[4], out int y2);
                if (points[0].Equals("L"))
                {
                    Class1.AddLine( x1, y1, x2, y2);
                }
                else if (points[0].Equals("R"))
                {
                    Class1.AddRay( x1, y1, x2, y2);
                }
                else if (points[0].Equals("S"))
                {
                    Class1.AddSection(x1, y1, x2, y2);
                }
            }
            else if (points[0].Equals("C"))
            {
                int.TryParse(points[1], out int x);
                int.TryParse(points[2], out int y);
                int.TryParse(points[3], out int r);
                Class1.AddCircle(x, y, r);
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult dr = openFileDialog1.ShowDialog();
            //获取所打开文件的文件名
            string filename = openFileDialog1.FileName;
            if (dr == DialogResult.OK && !string.IsNullOrEmpty(filename))
            {
                StreamReader sr = new StreamReader(filename);
                string line = sr.ReadLine();
                while (!sr.EndOfStream)
                {
                    line = sr.ReadLine();
                    comboBox1.Items.Add(line);//将信息加入到删除左侧的复选框(comboBox)中
                    add(line);
                }
                sr.Close();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "")
            {
                //判断文本框中的值是否与组合框中的的值重复
                if (comboBox1.Items.Contains(textBox1.Text))
                {
                    MessageBox.Show("该几何对象已存在！", "提示");
                }
                else
                {
                    comboBox1.Items.Add(textBox1.Text);
                    string[] points = textBox1.Text.Split(' ');       // 拆分当前行
                    add(textBox1.Text);
                    MessageBox.Show("添加成功！", "提示");
                }
            }
            else
            {
                MessageBox.Show("请输入几何对象！", "提示");
            }
        }

        private void del(string line)
        {
            string[] points = line.Split(' ');
            if (points[0].Equals("L") || points[0].Equals("R") || points[0].Equals("S"))
            {
                int.TryParse(points[1], out int x1);
                int.TryParse(points[2], out int y1);
                int.TryParse(points[3], out int x2);
                int.TryParse(points[4], out int y2);
                if (points.Equals("L"))
                {
                    Class1.RemoveLine(x1, y1, x2, y2);
                }
                else if (points.Equals("R"))
                {
                    Class1.RemoveRay(x1, y1, x2, y2);
                }
                else if (points.Equals("S"))
                {
                    Class1.RemoveSection(x1, y1, x2, y2);
                }
            }
            else if (points[0].Equals("C"))
            {
                int.TryParse(points[1], out int x);
                int.TryParse(points[2], out int y);
                int.TryParse(points[3], out int r);
                Class1.RemoveCircle(x, y, r);
            }
        }
        private void button3_Click(object sender, EventArgs e)
        {
            if (comboBox1.Text != "")
            {
                if (comboBox1.Items.Contains(comboBox1.Text))
                {
                    comboBox1.Items.Remove(comboBox1.Text);
                    del(comboBox1.Text);
                    MessageBox.Show("删除成功！", "提示");
                }
                else
                {
                    MessageBox.Show("请重新选择!", "提示");
                }
            }
            else
            {
                MessageBox.Show("请选择要删除的几何对象", "提示");
            }
        }

        private new void Paint(Bitmap b, Graphics g)
        {
            ArrayList nums = new ArrayList();
            for (int i = 0; i < comboBox1.Items.Count; i++)
            {
                string line = (string)comboBox1.Items[i];

                string[] points = line.Split(' ');       // 拆分当前行
                if (points[0].Equals("L") || points[0].Equals("R") || points[0].Equals("S"))
                {
                    int.TryParse(points[1], out int x1);
                    int.TryParse(points[2], out int y1);
                    int.TryParse(points[3], out int x2);
                    int.TryParse(points[4], out int y2);
                    nums.Add(Math.Abs(x1));
                    nums.Add(Math.Abs(y1));
                    nums.Add(Math.Abs(x2));
                    nums.Add(Math.Abs(y2));
                }
                else if (points[0].Equals("C"))
                {
                    int.TryParse(points[1], out int _x);
                    int.TryParse(points[2], out int _y);
                    int.TryParse(points[3], out int r);
                    nums.Add(Math.Abs(_x));
                    nums.Add(Math.Abs(_y));
                    nums.Add(Math.Abs(r));
                }
            }
            int[] num = (int[])nums.ToArray(typeof(int));
            int max = num.Max();
            paint(max, b, g);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Bitmap b = new Bitmap(length, length);
            Graphics g = Graphics.FromImage(b);
            Paint(b, g);//画出坐标系
            
            for (int i = 0; i < comboBox1.Items.Count; i++)
            {
                string line = (string)comboBox1.Items[i];
                string[] points = line.Split(' ');
                Draw(points, g);
            }//画出每一个几何对象

            try
            {
                int size = Class1.GetIntersectionsSize();
                double[] x = new double[size];
                double[] y = new double[size];
                int[] size1 = new int[1];
                label4.Text = "交点数目:" + size.ToString();
                Class1.GetIntersections(x, y, size);
                comboBox2.Items.Clear();


                for (int i = 0; i < size; i++)
                {
                    comboBox2.Items.Add("(" + x[i].ToString() + "," + y[i].ToString() + ")");//填写交点坐标
                    MarkPoint(g, (float)x[i], (float)y[i]);//标记交点
                }
            }
            catch
            {
                MessageBox.Show("有重合的几何图形,请结束程序", "提示");
                return;
            }
            
                
        }


        public void MarkPoint(Graphics g, float x, float y)
        {
            int X = length / 2, Y = length / 2;
            int l = length;
            g.DrawEllipse(Pens.Red, X + l / n / k * x, Y - l / n / k * y, 4, 4);
            g.FillEllipse(new SolidBrush(Color.Red), X + l / n / k * x, Y - l / n / k * y, 4, 4);
            //g.DrawString("(" + x.ToString() + "," + y.ToString() + ")", SystemFonts.DefaultFont, new SolidBrush(Color.Red), new PointF(X + l / n / k * x, Y - l / n / k * y));
        }

        public void Draw(String[] points, Graphics g)
        {
            if (points[0].Equals("L") || points[0].Equals("R") || points[0].Equals("S"))
            {
                int.TryParse(points[1], out int x1);
                int.TryParse(points[2], out int y1);
                int.TryParse(points[3], out int x2);
                int.TryParse(points[4], out int y2);

                if (points[0].Equals("S"))
                {
                    g.DrawLine(Pens.Black, change(x1, y1), change(x2, y2));
                }
                else if (points[0].Equals("R"))
                {
                    if (x2 - x1 == 0)
                    {
                        int y3 = y2 + (y2 - y1);
                        g.DrawLine(Pens.Black, change(x1, y1), change(x1, y3));
                    }
                    else
                    {
                        int x3 = x2 + (x2 - x1);
                        int y3 = y2 + (y2 - y1);
                        g.DrawLine(Pens.Black, change(x1, y1), change(x3, y3));
                    }
                }
                else if (points[0].Equals("L"))
                {
                    if (x2 - x1 == 0)
                    {
                        int y3 = y2 + (y2 - y1);
                        int y4 = y1 + (y1 - y2);
                        g.DrawLine(Pens.Black, change(x1, y4), change(x1, y3));
                    }
                    else
                    {

                        int x3 = x2 + (x2 - x1);
                        int x4 = x1 + (x1 - x2);
                        int y3 = y2 + (y2 - y1);
                        int y4 = y1 + (y1 - y2);
                        g.DrawLine(Pens.Black, change(x4, y4), change(x3, y3));
                    }
                }
            }
            else if (points[0].Equals("C"))
            {
                int.TryParse(points[1], out int x);
                int.TryParse(points[2], out int y);
                int.TryParse(points[3], out int r);
                DrawYuan(g, x, y, r);
            }
        }

        public void DrawYuan(Graphics g, int x, int y, int r)
        {
            g.DrawEllipse(Pens.Black, length / 2 + length / n / k * (x - r), length / 2 - length / n / k * (y + r), length / n / k * r * 2, length / n / k * r * 2);
        }

        private PointF change(int x, int y)
        {
            return new PointF(length / 2 + length / n / k * x, length / 2 - length / n / k * y);
        }

        private PointF change(float x, float y)
        {
            return new PointF(length / 2 + length / n / k * x, length / 2 - length / n / k * y);
        }

        private void paint(int max, Bitmap b, Graphics g)
        {

            int x = length / 2, y = length / 2;
            int l = length;
            k = (max / 5) + 1;

            pictureBox1.Image = b;
            g.DrawLine(Pens.Blue, new Point(0, length / 2), new Point(length, length / 2));
            g.DrawLine(Pens.Blue, new Point(length / 2, 0), new Point(length / 2, length));
            for (int i = 1; i <= n; i++)
            {
                g.DrawLine(Pens.Red, new Point(i * l / n, y - 2), new Point(i * l / n, y));
                if (i != n / 2)
                    g.DrawString(((i - n / 2) * k).ToString(), SystemFonts.DefaultFont, new SolidBrush(Color.Red), new Point(i * l / n, x));

                g.DrawLine(Pens.Red, new Point(x, i * l / n), new Point(x + 2, i * l / n));
                g.DrawString(((n / 2 - i) * k).ToString(), SystemFonts.DefaultFont, new SolidBrush(Color.Red), new Point(x + 2, i * l / n));
            }
        }

        private void Form5_Load(object sender, EventArgs e)
        {

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
