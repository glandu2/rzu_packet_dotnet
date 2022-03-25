using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace TestCli
{
    class Program
    {
        static void Main(string[] args)
        {
            MemoryStream stream = new MemoryStream();

            RappelzPackets.Test t = new RappelzPackets.Test();
            t.PacketIterator_iterator();
            t.PacketIterator_process();
            t.PacketIterator_serialize_deserialize();

            RappelzPackets.TS_AC_RESULT result = new RappelzPackets.TS_AC_RESULT();
            result.request_msg_id = 0x1234;
            result.result = 0xAA55;
            result.login_flag = 0x44556677;

            result.serialize(stream, RappelzPackets.Epics.EPIC_7_1, Encoding.UTF8);

            byte[] data = stream.GetBuffer();

            for (int i = 0; i < stream.Length; i++)
            {
                
                Console.Write(data[i].ToString("X2") + " ");
                if (i > 0 && (i % 16) == 0)
                {
                    Console.Write("\n");
                }
            }
            Console.Write("\n");
        }
    }
}
