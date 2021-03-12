using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;

using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;

namespace example09march
{
    public static class SaveToCosmosDB
    {
        private static HttpClient client = new HttpClient();

        [FunctionName("SaveToCosmosDB")]
        public static void Run(
            [IoTHubTrigger("messages/events", Connection = "IotHub", ConsumerGroup = "cosmos2")]EventData message,
            [CosmosDB(databaseName: "Inlupp1", collectionName: "Measurement", CreateIfNotExists = true, ConnectionStringSetting = "CosmosDB")] out dynamic cosmos,
            ILogger log)
        {
            try
            {
                var msg = JsonConvert.DeserializeObject<DhtMeasurements>(Encoding.UTF8.GetString(message.Body.Array));
                msg.DeviceId = message.SystemProperties["iothub-connection-device-id"].ToString();
                msg.Name = message.Properties["Name"].ToString();
                msg.School = message.Properties["School"].ToString();

                var json = JsonConvert.SerializeObject(msg);
                cosmos = json;

                log.LogInformation("Message saved to Cosmos");
            }
            catch
            {
                log.LogInformation("Catch triggered");
                cosmos = null;
            }

            
        }
    }
}