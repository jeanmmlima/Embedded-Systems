#!/bin/bash

echo -n "Digite o MAC da Galileo: "
read MAC

#No lugar de "192.168.110-113.1-255" infome a faixa de ips no qual a galileo está conectada
ip=$(sudo nmap -sn 192.168.110-113.1-255 | grep "$MAC" -B 2 | cut -f2 -d'(' | cut -f1 -d')' | sed -n '1p')

sudo ssh-keygen -f "/home/$USER/.ssh/known_hosts" -R $ip

sudo ssh -p22 root@$ip