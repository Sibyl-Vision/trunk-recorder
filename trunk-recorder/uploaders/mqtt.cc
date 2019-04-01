#include "mqtt.h"
#define PUBLISH_TOPIC "EXAMPLE_TOPIC"
#define DEBUG 1
#include <iostream>

mqtt_client::mqtt_client(const char *id, const char *host, int port) : mosquittopp("Hello")
{
    int keepalive = DEFAULT_KEEP_ALIVE;
    #ifdef DEBUG
        std::cout << "Trying to Connect - code " <<  std::endl;
    #endif

    connect(host, port, keepalive);
}

mqtt_client::~mqtt_client()
{
}

void mqtt_client::on_connect(int rc)
{

#ifdef DEBUG
        std::cout << "Connected - code " << rc << std::endl;
#endif

}

void mqtt_client::on_publish(int mid)
 {
 std::cout << ">> myMosq - Message (" << mid << ") succeed to be published " << std::endl;
 }

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
#ifdef DEBUG
    std::cout << "Subscription succeeded." << std::endl;
#endif
}

void mqtt_client::on_message(const struct mosquitto_message *message)
{
    int payload_size = MAX_PAYLOAD + 1;
    char buf[payload_size];

  //  if(!strcmp(message->topic, PUBLISH_TOPIC))
   // {
        memset(buf, 0, payload_size * sizeof(char));

        /* Copy N-1 bytes to ensure always 0 terminated. */
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));

#ifdef DEBUG
        std::cout << buf << std::endl;
#endif

        // Examples of messages for M2M communications...
        if (!strcmp(buf, "STATUS"))
        {
            snprintf(buf, payload_size, "This is a Status Message...");
            publish(NULL, PUBLISH_TOPIC, strlen(buf), buf);
#ifdef DEBUG
            std::cout << "Status Request Recieved." << std::endl;
#endif
        }

        if (!strcmp(buf, "ON"))
        {
            snprintf(buf, payload_size, "Turning on...");
            publish(NULL, PUBLISH_TOPIC, strlen(buf), buf);
#ifdef DEBUG
            std::cout << "Request to turn on." << std::endl;
#endif
        }

        if (!strcmp(buf, "OFF"))
        {
            snprintf(buf, payload_size, "Turning off...");
            publish(NULL, PUBLISH_TOPIC, strlen(buf), buf);
#ifdef DEBUG
            std::cout << "Request to turn off." << std:: endl;
#endif
        }
   // }
}

void mqtt_client::send_mqtt_call(Call *call, System *sys, Config config) {
    std::string msg = "pk";

    

    char buf[strlen(msg.c_str())];
    memset(buf, 0, 51*sizeof(char));
    /* Copy N-1 bytes to ensure always 0 terminated. */
    memcpy(buf, &msg, 50*sizeof(char));

    const char *topic = const_cast<char *>(("skyscraper/edge/trunkrecorder/" + sys->get_short_name()).c_str()); // + "/"; + call->get_talkgroup_tag()).c_str());
    int ret = publish(NULL, topic, strlen(buf), (u_int8_t *) buf,1,false);
    //int ret = publish(NULL, "hello/test", strlen(buf), (u_int8_t *) buf,1,false);
    
     std::cout << "Trying to send MQTT message. " << ret << std:: endl;
}
