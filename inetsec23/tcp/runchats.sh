#!/bin/bash

gnome-terminal -- python3 tcp_chat.py 9876 --window --hold
gnome-terminal -- python3 tcp_chat.py 127.0.0.1 9876 --window --hold

gnome-terminal -- python3 udp_chat_server.py 9877 --window --hold
gnome-terminal -- python3 udp_chat_client.py 127.0.0.1 9877 testuser --window --hold

gnome-terminal -- python3 udp_multicast_chat_server.py 9999 --window --hold
gnome-terminal -- python3 udp_multicast_chat_client.py 127.0.0.1 9999 multicast --window --hold
