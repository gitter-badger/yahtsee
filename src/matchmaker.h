#ifndef _MATCHMAKER_H_
#define _MATCHMAKER_H_

#include "config.h"

#include <arg3net/socket_server.h>
#include <arg3net/http_client.h>
#include <string>
#include "client.h"
#include <arg3dice/yaht/player.h>

class game;
class player;

class matchmaker
{
public:

    matchmaker(game *game);
    matchmaker(const matchmaker &) = delete;
    matchmaker(matchmaker  &&other);
    matchmaker &operator=(const matchmaker &) = delete;
    matchmaker &operator=(matchmaker && );
    virtual ~matchmaker();
    void stop();
    bool is_valid() const;
    bool host(bool register_online, std::string *error = NULL, int port = INVALID);
    bool join_best_game(std::string *error = NULL);
    bool join_game(const std::string &host, int port, std::string *error = NULL);
    void notify_player_joined(const shared_ptr<player> &p);
    void notify_player_left(const shared_ptr<player> &p);
    void notify_game_start();
    void notify_player_roll();
    void notify_player_turn_finished();
    int server_port() const;
    void set_api_keys(const std::string &appId, const std::string &appToken);

private:

    bool r3gister(std::string *error, int port);

    void unregister();

    void port_forward(int port) const;

    void send_network_message(const string &value);

    constexpr static const char *GAME_TYPE = "yahtsee";

    static const char *GAME_API_URL;

    static const int INVALID = -1;

    std::string gameId_;
    arg3::net::http_client api_;
    client client_;
    connection_factory client_factory_;
    arg3::net::socket_server server_;
    game *game_;
    int server_port_;
};

#endif
