using System;
using System.Collections.Generic;
using System.Text;

namespace example09march
{
    public class DhtMeasurements
    {
        public string DeviceId { get; set; }
        public string Name { get; set; }
        public string School { get; set; }
        public float Temperature { get; set; }
        public float Humidity { get; set; }
        public int UnixTime { get; set; }
        public string _ts { get; set; }
    }
}
