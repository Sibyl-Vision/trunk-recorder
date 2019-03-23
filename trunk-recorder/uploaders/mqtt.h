#ifndef MQTT_H
#define MQTT_H


#include <cstring>
#include <cstdio>

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp
{
public:
    mqtt_client (const char *id, const char *host, int port) ;
    ~mqtt_client() override;

    void on_connect(int rc) override;
    void on_message(const struct mosquitto_message *message) override;
    void on_subscribe(int mid, int qos_count, const int *granted_qos) override;
};

#endif //MQTT_H