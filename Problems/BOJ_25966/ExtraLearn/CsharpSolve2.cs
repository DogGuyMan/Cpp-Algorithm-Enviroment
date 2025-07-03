// cs25966 - rby
// 2023-03-18 13:35:11
using System;
using System.Text;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace cs25966
{
    class Program
    {
        static StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
        static StreamWriter sw = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
        static StringBuilder sb = new StringBuilder();
        static int N;
        static int M;
        static int Q;
        static void Main(string[] args)
        {
            int[] line = Array.ConvertAll(sr.ReadLine().Split(), int.Parse);
            (N, M, Q) = (line[0], line[1], line[2]);

            Row[] row = new Row[N];

            for (int i = 0; i < N; i++)
            {
                row[i] = new Row();
                row[i].col = Array.ConvertAll(sr.ReadLine().Split(), int.Parse);
            }

            for(int q = 0; q < Q; q++)
            {
                line = Array.ConvertAll(sr.ReadLine().Split(), int.Parse);
                switch(line[0])
                {
                    case 0:
                        row[line[1]].col[line[2]] = line[3];
                        break;
                    case 1:
                        (row[line[1]], row[line[2]]) = (row[line[2]], row[line[1]]);
                        break;
                }
            }

            for(int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                    sb.Append(row[i].col[j]).Append(' ');
                sb.AppendLine();
            }

            sw.Write(sb);

            sw.Close();
            sr.Close();
        }
    }

    class Row
    {
        public int[] col;
        public Row() { }
    }
}