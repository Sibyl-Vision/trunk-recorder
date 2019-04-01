#ifndef MQTT_H
#define MQTT_H

#include <mosquittopp.h>
#include <cstring>
#include <cstdio>

#include "../config.h"
//#include "../systems/system.h"

class mqtt_client;
class Call;
class System;

#include "../call.h"

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60


class mqtt_client : public mosqpp::mosquittopp
{
public:
    mqtt_client (const char *id, const char *host, int port) ;
    ~mqtt_client() override;

    void on_publish(int mid) override;
    void on_connect(int rc) override;
    void on_message(const struct mosquitto_message *message) override;
    void on_subscribe(int mid, int qos_count, const int *granted_qos) override;
    void send_mqtt_call(Call *call, System *sys, Config config);
};

#endif //MQTT_H
